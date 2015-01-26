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

package search.precomputed;

import search.*;

public class Matrix implements Comparable<Matrix> {
  
  private static final int MAX_TRIPLES = 10;
  private static final int MAX_TETRIMINOS = 50;
  
  private int width;
  private int height;
  private int[] stacks;
  private int[] rows;    
  private int[] triples = new int[MAX_TRIPLES];
  private int triplesCount;
  private LockedTetrimino[] lockedTetriminos 
      = new LockedTetrimino[MAX_TETRIMINOS];
  private int lockedTetriminosCount;  
  private int hash;
  
  public Matrix(int width, int height) {
    this.width = width;
    this.height = height;
    
    stacks = new int[width];
    rows = new int[height];
    
    for(int i = 0; i < lockedTetriminos.length; i++) {
      lockedTetriminos[i] = new LockedTetrimino();
    }
  }
  
  public Matrix copyTriples() {
    Matrix matrix = new Matrix(width, height);
    for(int i = 0; i < triplesCount; i++) {
      matrix.pushTriple(triples[i]);
    }
    return matrix;
  }
  
  public char[][] toChars() {
    char[][] matrix = new char[height][width];
    for(int y = 0; y < height; y++) {
      for(int x = 0; x < width; x++) {
        matrix[y][x] = '.';
      }
    }
    
    char ch = 'A';
    for(int i = 0; i < triplesCount; i++) {
      for(int j = 0; j < 3; j++) {
        matrix[height - 1][triples[i] + j] = ch;
      }
      ch++;
    }
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
    for(int y = 0; y < height; y++) {
      sb.append(chars[y], 0, width).append(System.lineSeparator());
    } 
    return sb.toString();
  }
  
  public void pushTriple(int x) {
    for(int i = 0; i < 3; i++) {
      stacks[i + x] = 1;
    }
    
    triples[triplesCount++] = x;
    rows[0] += 3;
    
    computeHash();
  }
  
  private void computeHash() {
    hash = 0;
    for(int i = triplesCount - 1, j = 1; i >= 0; i--, j *= width) {
      hash += triples[i] * j;
    }
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
      if (stackHeight - completedRows > 0) {          
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
  
  public void popTriple() {
    int x = triples[--triplesCount];
    
    for(int i = 0; i < 3; i++) {
      stacks[i + x] = 0;
    }
    
    rows[0] -= 3;
    
    computeHash();
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
    for(int i = height - 1; i > 0; i--) {
      rows[i] = 0;
    }
    rows[0] = 3 * triplesCount;
    for(int i = triplesCount - 1; i >= 0; i--) {
      int x = triples[i];
      for(int j = 0; j < 3; j++) {
        stacks[j + x] = 1;
      }
    }    
  }
  
  public void clearTriples() {
    triplesCount = 0;
  }

  @Override
  public int hashCode() {    
    return hash;
  }

  @Override
  public boolean equals(Object obj) {
    Matrix matrix = (Matrix)obj;
    return matrix.width == width && matrix.height == height
        && matrix.triplesCount == triplesCount
        && matrix.hash == hash;
  }

  @Override
  public int compareTo(Matrix matrix) {
    return Integer.compare(hash, matrix.hash);
  }
}
