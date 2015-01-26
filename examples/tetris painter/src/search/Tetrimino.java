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

package search;

public final class Tetrimino {

  private static final String[][] PATTERNS = {
    { "....",
      "....",
      "XXXX",
      "....", },
        
    { "..X.",
      "..X.",
      "..X.",
      "..X.", },    
    
    { "....",
      ".XX.",
      ".XX.",
      "....", },
    
    { "....",
      "XXX.",
      "..X.",
      "....", },
    
    { ".X..",
      ".X..",
      "XX..",
      "....", },
    
    { "X...",
      "XXX.",
      "....",
      "....", },    
    
    { ".XX.",
      ".X..",
      ".X..",
      "....", },
    
    { "....",
      "XXX.",
      "X...",
      "....", },
    
    { "XX..",
      ".X..",
      ".X..",
      "....", }, 
    
    { "..X.",
      "XXX.",
      "....",
      "....", },    
    
    { ".X..",
      ".X..",
      ".XX.",
      "....", },
    
    { "....",
      ".XX.",
      "XX..",
      "....", },
    
    { ".X..",
      ".XX.",
      "..X.",
      "....", },     
    
    { "....",
      "XXX.",
      ".X..",
      "....", }, 
    
    { ".X..",
      "XX..",
      ".X..",
      "....", }, 
    
    { ".X..",
      "XXX.",
      "....",
      "....", }, 
    
    { ".X..",
      ".XX.",
      ".X..",
      "....", },   
    
    { "....",
      "XX..",
      ".XX.",
      "....", }, 
    
    { "..X.",
      ".XX.",
      ".X..",
      "....", },     
  };
  
  public static final Tetrimino[] TETRIMINOS = new Tetrimino[PATTERNS.length];
  
  static {
    for(int i = 0; i < TETRIMINOS.length; i++) {
      TETRIMINOS[i] = new Tetrimino(i);
    }
  }
  
  public Square[] squares = new Square[4];
  public int width;
  public int height;
  public int[] bottomYs;
  public int[] heights;
  public int[] widths;
  
  private Tetrimino(int index) {
    
    final String[] pattern = PATTERNS[index];    
    int minX = Integer.MAX_VALUE;
    int minY = Integer.MAX_VALUE;
    int maxX = Integer.MIN_VALUE;
    int maxY = Integer.MIN_VALUE;
    outer: for(int y = 0, i = 0; y < 4; y++) {
      int Y = 3 - y;
      for(int x = 0; x < 4; x++) {
        if (pattern[y].charAt(x) == 'X') {
          squares[i] = new Square(x, Y);
          minX = Math.min(x, minX);
          minY = Math.min(Y, minY);
          maxX = Math.max(x, maxX);
          maxY = Math.max(Y, maxY);
          if (++i == 4) {
            break outer;
          }
        }
      }
    }
    for(Square square : squares) {
      square.x -= minX;
      square.y -= minY;
    }
    width = maxX - minX + 1;
    height = maxY - minY + 1;
   
    bottomYs = new int[width];   
    heights = new int[width];
    for(int x = 0, i = 0; x < 4; x++) {
      int min = Integer.MAX_VALUE;
      int max = Integer.MIN_VALUE;
      boolean found = false;
      for(int y = 3; y >= 0; y--) {
        int Y = (3 - y) - minY;
        if (pattern[y].charAt(x) == 'X') {
          found = true;
          min = Math.min(Y, min);
          max = Math.max(Y, max);
        }
      }
      if (found) {
        bottomYs[i] = min;
        heights[i] = max - min + 1;
        i++;
      }
    }
    
    widths = new int[height];
    for(int y = 3, i = 0; y >= 0; y--) {      
      int min = Integer.MAX_VALUE;
      int max = Integer.MIN_VALUE;
      boolean found = false;      
      for(int x = 0; x < 4; x++) {
        if (pattern[y].charAt(x) == 'X') {
          found = true;
          min = Math.min(x, min);
          max = Math.max(x, max);
        }
      }
      if (found) {
        widths[i++] = max - min + 1;
      }
    }
  }
}
