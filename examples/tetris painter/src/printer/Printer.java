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

package printer;

import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import java.util.*;
import java.util.List;

public class Printer {
  
  public static final int PLAYFIELD_WIDTH = 21;
  public static final int PLAYFIELD_HEIGHT = 42;
  
  private void processLines(
      List<Square[][]> squaresList, List<int[]> tetriminos, 
      List<String> lines) {
    
    final int width = lines.get(0).length();
    final int height = lines.size();
    
    String topLine = lines.get(0);
    boolean platformPattern = false;
    for(int x = 0; x < width; x++) {
      if (topLine.charAt(x) == '.') {
        platformPattern = true;
        break;
      }
    }
    String bottomLine = lines.get(height - 1);
    char maxBottomChar = '.';
    for(int x = 0; x < width; x++) {
      char c = bottomLine.charAt(x);
      if (c > maxBottomChar) {
        maxBottomChar = c;
      }
    }
    int[] pieces = new int[platformPattern ? 0 : (maxBottomChar - 'A' + 1)];
    
    Map<Character, List<Square>> map = new HashMap<>();
    for(int y = 0; y < height; y++) {
      for(int x = 0; x < width; x++) {
        char c = lines.get(y).charAt(x);
        if (c >= 'A') {
          List<Square> squares = map.get(c);
          if (squares == null) {
            squares = new ArrayList<>();
            map.put(c, squares);
          }
          squares.add(new Square(x, y));
        }
      }
    }
    Square[][] result = new Square[map.size()][4];
    for(int i = 0; i < map.size(); i++) {
      List<Square> squares = map.get((char)('A' + i));      
      
      int minY = Integer.MAX_VALUE;
      for(int j = 0; j < squares.size(); j++) {
        Square square = squares.get(j);
        minY = Math.min(minY, square.y);        
      }
      for(int j = 0; j < squares.size(); j++) {
        Square square = squares.get(j);
        square.y -= minY;
      }
      
      squares.toArray(result[i]);
      if (squares.size() == 3) {
        result[i][3] = new Square();
      }
    }
    
    for(int i = 0; i < pieces.length; i++) {
      Square[] tetrimino = result[i];
      if (tetrimino[1].y == 1) {
        pieces[i] = tetrimino[0].x - tetrimino[1].x;
      } else {
        pieces[i] = 2 - (tetrimino[3].x - tetrimino[0].x);
      }    
    }
    
    squaresList.add(result);
    tetriminos.add(pieces);
  }
  
  private FileData readFileData(String fileName) throws Throwable { 
    FileData fileData = new FileData();
    List<Square[][]> squares = new ArrayList<>();
    List<int[]> tetriminos = new ArrayList<>();
    try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {      
      List<String> lines = new ArrayList<>();
      String input = null;
      while(true) {
        input = br.readLine();
        if (input != null) {
          input = input.trim();
          if (input.length() > 0) {            
            String[] tokens = input.split("\\s+");
            fileData.colors = new int[tokens.length];
            for(int i = 0; i < tokens.length; i++) {              
              fileData.colors[i] = 0xFF000000 | Integer.parseInt(tokens[i], 16);
            }            
            break;
          }
        } else {
          break;
        }
      }
      while(true) {
        input = br.readLine();
        if (input != null) {
          input = input.trim();
        }
        if (input == null || input.length() == 0) {          
          if (lines.size() > 0) {
            processLines(squares, tetriminos, lines);
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
    fileData.squares = new Square[squares.size()][][];
    squares.toArray(fileData.squares);
    fileData.tetriminos = new int[tetriminos.size()][];
    tetriminos.toArray(fileData.tetriminos);
    return fileData;
  }
  
  private void dropPiece(
      int[][] playfield, int[] stacks, int[] rows, Square[] piece) {
    dropPiece(playfield, stacks, rows, piece, 6);
  }
  
  private void dropPiece(
      int[][] playfield, int[] stacks, int[] rows, Square[] piece, int color) {
    
    int minX = Integer.MAX_VALUE;
    int maxX = Integer.MIN_VALUE;
    for(int i = 0; i < 4; i++) {
      minX = Math.min(minX, piece[i].x);
      maxX = Math.max(maxX, piece[i].x);
    }
    
    int minY = Integer.MAX_VALUE;
    for(int x = minX; x <= maxX; x++) {
      minY = Math.min(minY, stacks[x]);
    }    
    
    int y = minY - 4;
    if (y < 0) {
      y = 0;
    }
    outer: while(true) {      
      for(int i = 0; i < 4; i++) {
        Square square = piece[i];              
        if (y + square.y + 1 == PLAYFIELD_HEIGHT 
            || playfield[y + square.y + 1][square.x] != -1) {
          break outer;
        }
      }
      y++;
    }
    
    int maxY = Integer.MIN_VALUE;
    for(int i = 0; i < 4; i++) {
      Square square = piece[i]; 
      int pieceY = y + square.y;
      maxY = Math.max(maxY, pieceY);
      playfield[pieceY][square.x] = color;
      stacks[square.x] = Math.min(stacks[square.x], pieceY);
      rows[pieceY]++;
    }
    
    for(int i = maxY; i >= maxY - 4; ) {
      if (rows[i] == PLAYFIELD_WIDTH) {
        for(int j = i; j > 0; j--) {
          rows[j] = rows[j - 1];
        }
        rows[0] = 0;
        
        for(int x = 0; x < PLAYFIELD_WIDTH; x++) {
          if (stacks[x] <= i) {
            stacks[x]--;
            for(int j = i; j > 0; j--) {
              playfield[j][x] = playfield[j - 1][x];
            }        
            playfield[0][x] = -1;
          }
        }        
      } else {
        i--;
      }
    }
  }  
  
  private void saveImage(
      int[][] playfield, int[] colors, String outputImageFile) 
          throws Throwable {
    BufferedImage image = new BufferedImage(playfield[0].length, 
        playfield.length, BufferedImage.TYPE_INT_ARGB);
    int[] pixels = ((DataBufferInt)image.getRaster().getDataBuffer()).getData();
    for(int y = 0, i = 0; y < playfield.length; y++) {
      for(int x = 0; x < playfield[0].length; x++, i++) {
        if (playfield[y][x] == -1) {
          pixels[i] = 0xFF000000;
        } else {
          pixels[i] = colors[playfield[y][x]];          
        }
      }
    }
    String type = outputImageFile.substring(
        outputImageFile.lastIndexOf(".") + 1);    
    ImageIO.write(image, type, new File(outputImageFile));
  }
  
  private void processFile(FileData fileData, 
      String outputImageFile) throws Throwable {
    
    int[][] playfield = new int[PLAYFIELD_HEIGHT][PLAYFIELD_WIDTH];
    int[] stacks = new int[PLAYFIELD_WIDTH];
    int[] rows = new int[PLAYFIELD_HEIGHT];

    for(int y = 0; y < PLAYFIELD_HEIGHT; y++) {
      for(int x = 0; x < PLAYFIELD_WIDTH; x++) {
        playfield[y][x] = -1;
      }
    }
    for(int x = 0; x < PLAYFIELD_WIDTH; x++) {
      stacks[x] = PLAYFIELD_HEIGHT;
    }
    
    for(int i = 0; i < fileData.squares.length; i++) {
      for(int j = 0; j < fileData.squares[i].length; j++) {        
        if (j < fileData.tetriminos[i].length) {
          dropPiece(playfield, stacks, rows, fileData.squares[i][j], 
              fileData.tetriminos[i][j]);
        } else {
          dropPiece(playfield, stacks, rows, fileData.squares[i][j]);
        }
      }
    }

    saveImage(playfield, fileData.colors, outputImageFile);
  }

  public void launch(String inputTextFile, String outputImageFile) 
      throws Throwable {     
    processFile(readFileData(inputTextFile), outputImageFile);
  }
  
  public static void main(String... args) throws Throwable {
    if (args.length != 2) {
      System.out.println("args: [ input text file ] [ output image file ]");
      return;
    }
    new Printer().launch(args[0], args[1]);
  }
}
