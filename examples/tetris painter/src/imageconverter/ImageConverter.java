/*
 * Tetris Printer Algorithm
 * Copyright (C) 2013 meatfighter.com
 *
 * This file is part of Tetris Printer Algorithm.
 *
 * Tetris Printer Algorithm is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public License as 
 * published by the Free Software Foundation; either version 3 of the License, 
 * or (at your option) any later version.
 *
 * Tetris Printer Algorithm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

package imageconverter;

import search.*;
import search.realtime.*;
import java.awt.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import java.util.*;
import java.util.List;

public class ImageConverter {
  
  public static final int PLAYFIELD_WIDTH = 21;
  public static final int TRANSPARENT = -1;
  
  private char findMaxChar(String[] pattern) {
    char maxChar = 0;
    for(int y = 0; y < pattern.length; y++) {
      for(int x = 0; x < pattern[y].length(); x++) {
        char ch = pattern[y].charAt(x);
        if (ch > maxChar) {
          maxChar = ch;
        }
      }
    }  
    return maxChar;
  }
  
  private String replaceChars(String line, char maxChar) {
    StringBuilder sb = new StringBuilder();
    for(int i = 0; i < line.length(); i++) {
      if (line.charAt(i) != maxChar) {
        sb.append('.');
      } else {
        sb.append('A');
      }
    }
    return sb.toString();
  }
  
  private String[][] readPattern(String name, boolean platforms) 
      throws Throwable {   
    List<String[]> patterns = new ArrayList<>();
    try (BufferedReader br = new BufferedReader(new InputStreamReader(
        ImageConverter.class.getResourceAsStream(
            "/patterns/" + name + ".txt")))) {
      List<String> lines = new ArrayList<>();      
      while(true) {
        String input = br.readLine();
        if (input != null) {
          input = input.trim();
        }
        if (input == null || input.length() == 0) {
          if (lines.size() > 0) {
            String[] pattern = new String[lines.size()];
            lines.toArray(pattern);
            patterns.add(pattern);
            lines.clear();
          }
          if (input == null) {
            break;
          }
        } else {
          lines.add(input);
        }
      }
    }
    if (platforms) {
      char maxChar = findMaxChar(patterns.get(0));
      List<String[]> platformAdds = new ArrayList<>();
      List<String[]> platformRemoves = new ArrayList<>();
      for(String[] pattern : patterns) {
        String[] add = new String[pattern.length];
        String[] remove = new String[pattern.length];
        String addPattern = Character.toString(maxChar);        
        for(int y = 0; y < pattern.length; y++) {
          add[y] = pattern[y].replaceAll(addPattern, ".");
          remove[y] = replaceChars(pattern[y], maxChar);
        }
        platformAdds.add(add);
        platformRemoves.add(remove);
      }
      patterns.clear();
      patterns.addAll(platformAdds);
      patterns.addAll(platformRemoves);
    }
    String[][] result = new String[patterns.size()][];
    patterns.toArray(result);
    return result;
  }
  
  private String[][][] readPatterns() throws Throwable {
    
    List<String[][]> patterns = new ArrayList<>();
    patterns.add(readPattern("platforms", true));
    for(int i = 0; i < 7; i++) {
      patterns.add(readPattern("emitters" + (i + 1), false));
    }
    String[][][] result = new String[patterns.size()][][];
    patterns.toArray(result);
    return result;
  }  
  
  private void computePatternHashes(List<Integer> patternHashes, 
       int startIndex, int remaining, int hash) {
    
    if (remaining == 0) {
      patternHashes.add(hash);
    } else if (PLAYFIELD_WIDTH - startIndex >= remaining * 3) {
      for(int i = startIndex; i < PLAYFIELD_WIDTH - 2; i++) {
        computePatternHashes(patternHashes, i + 3, remaining - 1,
            PLAYFIELD_WIDTH * hash + i);
      }      
    }
  }
  
  private Map<Integer, Integer>[] computePatternHashes() {
    Map<Integer, Integer>[] maps = new HashMap[7];
    for(int i = 0; i < maps.length; i++) { 
      maps[i] = new HashMap<>();
      List<Integer> patternHashes = new ArrayList<>();
      computePatternHashes(patternHashes, 0, i + 1, 0);
      for(int j = 0; j < patternHashes.size(); j++) {
        maps[i].put(patternHashes.get(j), j);
      }
    }
    return maps;
  }  
  
  private BufferedImage loadImage(String fileName) throws Throwable {  
    return loadImage(new File(fileName));
  }
  
  private BufferedImage loadImage(File file) throws Throwable {
    BufferedImage image = ImageIO.read(file);
    
    BufferedImage temp = new BufferedImage(
        image.getWidth(), image.getHeight(), BufferedImage.TYPE_INT_ARGB);
    Graphics g = temp.getGraphics();    
    g.drawImage(image, 0, 0, null);    
    g.dispose();
    
    return temp;
  }
  
  private int[][] loadImagePixels(String fileName) throws Throwable {
    return loadImagePixels(new File(fileName));
  }  
  
  private int[][] loadImagePixels(File imageFile) throws Throwable {
    BufferedImage image = loadImage(imageFile);
    return convertExtractedPixels(extractPixels(image),
          image.getWidth(), image.getHeight());
  }
  
  private int[][] convertExtractedPixels(int[] pixels, int width, int height) {
    int[][] pixels2 = new int[height][PLAYFIELD_WIDTH];
    
    if (width > 17) {
      throw new RuntimeException(
         "Image width exceeds printer width: " + width);
    }
    
    for(int y = 0; y < height; y++) {
      System.arraycopy(pixels, y * width, pixels2[y], 2, width);
    }
    
    return pixels2;
  } 
  
  public static int[] extractPixels(BufferedImage image) {
    return ((DataBufferInt)image.getRaster().getDataBuffer()).getData();
  } 
  
  private boolean isOpaque(int color) {
    return ((color >> 24) & 0xFF) == 0xFF;    
  }
  
  private void remapColors(int[][] image) {
    Map<Integer, Integer> colors = new HashMap<>();
    int colorIndex = 0;
    for(int y = 0; y < image.length; y++) {
      for(int x = 0; x < image[y].length; x++) {
        if (isOpaque(image[y][x]) && !colors.containsKey(image[y][x])) {
          if (colorIndex > 0) {
            System.out.print(" ");
          }
          System.out.format("%06x", (0xFFFFFF & image[y][x]));
          colors.put(image[y][x], colorIndex++);          
          if (colors.size() > 3) {
            throw new RuntimeException("Image contains more than 3 colors.");
          }
        }
      }
    }
    System.out.println();
    System.out.println();
    for(int y = 0; y < image.length; y++) {
      for(int x = 0; x < image[y].length; x++) {
        if (isOpaque(image[y][x])) {
          image[y][x] = colors.get(image[y][x]);
        } else {
          image[y][x] = TRANSPARENT;
        }
      }
    }
  }
  
  private boolean isRowFullySupported(int[][] image, int y) {
    if (y == image.length - 1) {
      return true;
    }
    for(int x = 0; x < PLAYFIELD_WIDTH; x++) {
      if (image[y][x] != TRANSPARENT && image[y + 1][x] == TRANSPARENT) {
        return false;
      }
    }
    return true;
  }
  
  private int pickPlatformPattern(int[][] image, int y) {
    for (int x = 0; x < PLAYFIELD_WIDTH; x++) {
      if (image[y + 1][x] != TRANSPARENT) {
        return x >> 1;
      }
    }
    throw new RuntimeException("Row completely empty: " + y);
  }
  
  private boolean isCompleted(boolean[] completed) {
    for(int x = 0; x < PLAYFIELD_WIDTH; x++) {
      if (!completed[x]) {
        return false;
      }
    }
    return true;
  }
  
  private void findEmitterPattern(int[] imageRow, boolean[] triples,
      boolean[] completed, Map<Integer, Integer>[] patternHashes, 
          String[][][] patterns) {
        
    for(int i = 0; i < triples.length; i++) {
      triples[i] = false;
    }
    StringBuilder sb = new StringBuilder();
    
    int hash = 0;
    int count = 0;
    for(int x = 0; x < PLAYFIELD_WIDTH; x++) {
      if (!completed[x] && !triples[x + imageRow[x] - 2] 
          && !triples[x + imageRow[x] - 1] && !triples[x + imageRow[x]]) {
        for(int i = 0; i < 3; i++) {
          triples[x + imageRow[x] - 2 + i] = true;
        }
        sb.append((char)('A' + count));
        count++;
        hash = (PLAYFIELD_WIDTH * hash) + x + imageRow[x] - 2;        
        completed[x] = true;                 
      } else {
        sb.append('.');
      }
    }
    
    int patternIndex = patternHashes[count - 1].get(hash);
    String[] pattern = patterns[count][patternIndex];
    printPattern(pattern, false); 
    System.out.println(sb);
    System.out.println();
  }  
  
  private void findPattern(RealtimeSearcher searcher, int[] imageRow,
      boolean[] completed, char[][] base, 
      boolean[] triples, Map<Integer, Integer>[] patternHashes, 
      String[][][] patterns) throws Throwable {
    
    for(int x = 0; x < PLAYFIELD_WIDTH; x++) {
      base[0][x] = '.';
      base[1][x] = (completed[x] && imageRow[x] != TRANSPARENT) ? '~' : '.';
    }
    
    char ch = 'A';
    for(int x = 2; x < PLAYFIELD_WIDTH - 5; x++) {
      if (!completed[x] && !completed[x + 1] && !completed[x + 2]
          && imageRow[x] != TRANSPARENT
          && imageRow[x] == imageRow[x + 1] && imageRow[x] == imageRow[x + 2]
          && base[1][x] == '.' && base[1][x + 1] == '.' 
          && base[1][x + 2] == '.' && base[0][x + imageRow[x]] == '.') {
        base[1][x] = base[1][x + 1] = base[1][x + 2] 
            = base[0][x + imageRow[x]] = ch++;        
      }
    }
    for(int x = 2; x < PLAYFIELD_WIDTH - 2; x++) {
      if (!completed[x] && imageRow[x] != TRANSPARENT 
          && base[1][x] == '.' 
          && base[0][x + imageRow[x] - 2] == '.'
          && base[0][x + imageRow[x] - 1] == '.'
          && base[0][x + imageRow[x]] == '.') {
        base[1][x] = base[0][x + imageRow[x] - 2] 
            = base[0][x + imageRow[x] - 1] = base[0][x + imageRow[x]] = ch++;
      }
    }
    
    Matrix matrix = new Matrix(base);
    Result result = searcher.search(matrix);
    
    if (result == Result.SOLUTION) {
      char[][] chars = matrix.toChars();
      StringBuilder sb = new StringBuilder();
      for(int y = 0; y < chars.length; y++) {
        sb.append(chars[y], 0, PLAYFIELD_WIDTH).append(System.lineSeparator());
      }      
      System.out.println(sb);
      for(int x = 2; x < PLAYFIELD_WIDTH - 2; x++) {
        if (chars[chars.length - 1][x] != '.') {
          completed[x] = true;
        }
      }      
    } else {
      findEmitterPattern(imageRow, triples, completed, patternHashes, patterns);
    }
  }
  
  private void printPattern(String[] pattern, boolean emptyLine) {
    for(String s : pattern) {
      System.out.println(s);
    }
    if (emptyLine) {
      System.out.println();
    }
  }
  
  private void computePlan(RealtimeSearcher searcher, int[][] image, 
      Map<Integer, Integer>[] patternHashes, String[][][] patterns) 
          throws Throwable {
        
    char[][] base = new char[2][PLAYFIELD_WIDTH];
    boolean[] completed = new boolean[PLAYFIELD_WIDTH];
    boolean[] triples = new boolean[PLAYFIELD_WIDTH];
    
    for(int y = image.length - 1; y >= 0; y--) {
      int platform = -1;
      if (y != image.length - 1 && !isRowFullySupported(image, y)) {
        platform = pickPlatformPattern(image, y);
        printPattern(patterns[0][platform], true);        
      }
      for(int x = 0; x < PLAYFIELD_WIDTH; x++) {
        completed[x] = image[y][x] == TRANSPARENT;
      }            
      do {
        findPattern(searcher, image[y], completed, base, 
            triples, patternHashes, patterns);
      } while(!isCompleted(completed));
      if (platform != -1) {
        printPattern(patterns[0][platform + (patterns[0].length >> 1)], true);
      }
    }
  }
  
  public void launch(String imageFileName) throws Throwable {
    RealtimeSearcher searcher = new RealtimeSearcher();
    String[][][] patterns = readPatterns();
    Map<Integer, Integer>[] patternHashes = computePatternHashes();
    int[][] image = loadImagePixels(imageFileName);
    remapColors(image);
    computePlan(searcher, image, patternHashes, patterns);
  }
  
  public static void main(String... args) throws Throwable {
    
    if (args.length != 1) {
      System.out.println("args: [image file name]");
      return;
    }
    
    new ImageConverter().launch(args[0]);
  }  
}
