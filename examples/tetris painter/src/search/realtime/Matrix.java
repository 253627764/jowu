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

package search.realtime;

import search.*;

public class Matrix {
  
  private static final int MAX_TETRIMINOS = 50;
  
  private int width;
  private int height;
  private int[] stacks;
  private int[] rows;    
  private LockedTetrimino[] lockedTetriminos 
      = new LockedTetrimino[MAX_TETRIMINOS];
  private int lockedTetriminosCount;
  private char[][] base;  
  
  public Matrix(Matrix matrix) {
    set(matrix);
  }
  
  public Matrix(Matrix matrix, int initialY) {
    this(matrix.base, initialY);
  }  
  
  public Matrix(char[][] base) {
    this(base, 1);
  }
  
  public Matrix(char[][] base, int initialY) {
    
    this.base = base;
    this.width = base[0].length;
    
    stacks = new int[width];

    int squares = 0;
    for(int x = 0; x < width; x++) {
      if (base[0][x] >= 'A') {
        squares++;
        stacks[x] = 1;        
      }
    }
    height = initialY + 5 - ((width * (initialY + 1) - squares) & 3);
    if (height > 7) {
      height -= 4;
    }
    
    rows = new int[height];
    rows[0] = squares;
    
    for(int i = 0; i < lockedTetriminos.length; i++) {
      lockedTetriminos[i] = new LockedTetrimino();
    }
  }  
  
  public void set(Matrix matrix) {
    this.base = matrix.base;
    this.width = matrix.width;
    this.height = matrix.height;
    
    if (stacks == null || stacks.length != width) {
      stacks = new int[width];
    }
    if (rows == null || rows.length != height) {
      rows = new int[height];
    }
    
    System.arraycopy(matrix.stacks, 0, stacks, 0, width);
    System.arraycopy(matrix.rows, 0, rows, 0, height);
    
    this.lockedTetriminosCount = matrix.lockedTetriminosCount;
    
    if (lockedTetriminos[0] == null) {
      for(int i = 0; i < lockedTetriminos.length; i++) {
        lockedTetriminos[i] = new LockedTetrimino();
      }
    }
    
    for(int i = 0; i < matrix.lockedTetriminosCount; i++) {
      lockedTetriminos[i].set(matrix.lockedTetriminos[i]);
    }
  }
  
  public int getRemainingTetriminoCount() {
    int emptySquares = 0;
    for(int i = stacks.length - 1; i >= 0; i--) {
      emptySquares += height - stacks[i];
    }
    return emptySquares / 4;
  }
  
  public Matrix copy() {
    return new Matrix(this);
  }  
  
  public Matrix expand() {
    return new Matrix(this, 5);
  }
  
  public char[][] toChars() {
    char[][] matrix = new char[height + 1][width];
    for(int y = 0; y < height + 1; y++) {
      for(int x = 0; x < width; x++) {
        matrix[y][x] = '.';
      }
    }
    
    char ch = 'A';
    for(int y = 0; y < 2; y++) {
      for(int x = 0; x < width; x++) {
        if (base[y][x] != '~') {
          matrix[height - 1 + y][x] = base[y][x];
        }
        if (y == 0 && base[y][x] > ch) {
          ch = base[y][x];
        }
      }
    }
    ch++;
    for(int i = 0; i < lockedTetriminosCount; i++) {
      LockedTetrimino lockedTetrimino = lockedTetriminos[i];
      for(int j = 0; j < 4; j++) {
        Square square = lockedTetrimino.tetrimino.squares[j];
        matrix[height - 1 - square.y - lockedTetrimino.y]
            [square.x + lockedTetrimino.x] = ch;
      }
      ch++;
    } 
    
    return matrix;
  }

  @Override
  public String toString() {
    char[][] chars = toChars();
    StringBuilder sb = new StringBuilder();
    for(int y = 0; y < chars.length; y++) {
      sb.append(chars[y], 0, width).append(System.lineSeparator());
    } 
    return sb.toString();
  }
  
  public boolean pushTetrimino(DroppedTetrimino droppedTetrimino) {
    return pushTetrimino(droppedTetrimino.tetrimino, droppedTetrimino.x);
  }
  
  public boolean pushBottomS() {
        
    if (rows[0] > width - 2) {
      return false;
    }
    
    for(int i = width - 3; i >= 0; i--) {
      if (stacks[i] == 0 && stacks[i + 1] == 0 && stacks[i + 2] == 1) {
        return pushTetrimino(Tetrimino.TETRIMINOS[11], i);
      }
    }
    
    return false;
  }
  
  public boolean pushBottomZ() {
        
    if (rows[0] > width - 2) {
      return false;
    }
    
    for(int i = width - 3; i >= 0; i--) {
      if (stacks[i] == 1 && stacks[i + 1] == 0 && stacks[i + 2] == 0) {
        return pushTetrimino(Tetrimino.TETRIMINOS[17], i);
      }
    }
    
    return false;
  }  
  
  public boolean pushTetrimino(Tetrimino tetrimino, int x) {
    
    // count completed rows
    int completedRows = 0;
    for(int i = height - 1; i >= 0; i--) {
      if (rows[i] == width) {
        completedRows++;
      }
    }        
    
    // verify that the Tetrimino will be supported
    int y = -1;
    boolean supported = false;
    for(int i = tetrimino.width - 1; i >= 0; i--) {     
      int stackHeight = stacks[x + i];  
      int difference = stackHeight - completedRows;
      if (difference > 0 || (difference == 0 && base[1][x + i] >= 'A')) {        
        supported = true;
      }
      if (y < 0) {
        y = stackHeight - tetrimino.bottomYs[i];          
        if (y < 0 || y + tetrimino.height > height) {
          return false;
        }
      } else if (stackHeight != y + tetrimino.bottomYs[i]) {
        return false;
      } 
    }
    if (!supported) {
      return false;
    }
    
    // update the stack heights
    for(int i = tetrimino.width - 1; i >= 0; i--) {
      stacks[i + x] += tetrimino.heights[i];   
    }
    
    // disjoint empty region must be divisible by 4    
    int emptyRegionSize = 0;
    for(int i = width - 1; i >= -1; i--) {
      if (i == -1 || stacks[i] == height) {
        if ((emptyRegionSize & 3) != 0) {   
          for(int j = tetrimino.width - 1; j >= 0; j--) {
            stacks[j + x] -= tetrimino.heights[j];   
          }          
          return false;
        }
        emptyRegionSize = 0;
      } else {
        emptyRegionSize += height - stacks[i];
      }
    }    
    
    // record the added piece
    LockedTetrimino lockedTetrimino = lockedTetriminos[lockedTetriminosCount++];
    lockedTetrimino.tetrimino = tetrimino;
    lockedTetrimino.x = x;
    lockedTetrimino.y = y;   
    
    // update the row counts
    for(int i = tetrimino.height - 1; i >= 0; i--) {
      rows[i + y] += tetrimino.widths[i];
    }   
    
    return true;
  }
  
  public void popTetrimino() {
    LockedTetrimino lockedTetrimino = lockedTetriminos[--lockedTetriminosCount];
    Tetrimino tetrimino = lockedTetrimino.tetrimino;
    int x = lockedTetrimino.x;
    int y = lockedTetrimino.y;
    
    for(int i = tetrimino.width - 1; i >= 0; i--) {
      stacks[i + x] -= tetrimino.heights[i];   
    }
    for(int i = tetrimino.height - 1; i >= 0; i--) {
      rows[i + y] -= tetrimino.widths[i];
    }    
  }
  
  public void clearTetriminos() {
    lockedTetriminosCount = 0;
    for(int i = width - 1; i >= 0; i--) {
      stacks[i] = 0;
    }
    for(int i = height - 1; i >= 0; i--) {
      rows[i] = 0;
    }   
    
    int squares = 0;
    for(int x = 0; x < width; x++) {
      if (base[0][x] >= 'A') {
        squares++;
        stacks[x] = 1;        
      }
    }
    rows[0] = squares;    
  }
}
