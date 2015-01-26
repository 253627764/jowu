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
import java.util.*;

public class SearchThread extends Thread {
    
  private final List<Matrix> matrices;
  private final List<Matrix> solutions;
  private final List<Matrix> noSolutions;
  private final DroppedTetrimino[][] randomSets;
  private final Random random = new Random();
  private int attempts;
  
  public SearchThread(
      List<Matrix> matrices,
      List<Matrix> solutions,
      List<Matrix> noSolutions,
      DroppedTetrimino[][] randomSets) {
    this.matrices = matrices;
    this.solutions = solutions;
    this.noSolutions = noSolutions;
    this.randomSets = randomSets;
  }
  
  private Result search(Matrix matrix, int remaining) {
    
    if (remaining == 0) {
      return Result.SOLUTION;
    }
    
    if (++attempts >= PatternSearcher.MAX_ATTEMPTS) {      
      return Result.TIMEOUT;
    }
    
    if (random.nextBoolean() 
        ? matrix.pushBottomS() : matrix.pushBottomZ()) {
      Result result = search(matrix, remaining - 1);
      if (result == Result.SOLUTION) {
        return Result.SOLUTION;
      } 
      matrix.popTetrimino();
      if (result == Result.TIMEOUT) {
        return Result.TIMEOUT;
      }
    }
    
    DroppedTetrimino[] randomSet = randomSets[random.nextInt(PatternSearcher.RANDOM_SETS)];
    for(int i = randomSet.length - 1; i >= 0; i--) {
      if (matrix.pushTetrimino(randomSet[i])) {        
        Result result = search(matrix, remaining - 1);
        if (result == Result.SOLUTION) {
          return Result.SOLUTION;
        } 
        matrix.popTetrimino();
        if (result == Result.TIMEOUT) {
          return Result.TIMEOUT;
        }
      }
    }
    
    return Result.NO_SOLUTION;
  }   
  
  private void search(Matrix matrix) { 
    Result result;
    do {
      matrix.clearTetriminos();
      attempts = 0;
      result = search(matrix, (PatternSearcher.MATRIX_WIDTH * PatternSearcher.MATRIX_HEIGHT 
          - 3 * PatternSearcher.EMITTED_SQUARES) / 4); 
      if (result == Result.SOLUTION) {
        solutions.add(matrix);
      } else if (result == Result.NO_SOLUTION) {
        noSolutions.add(matrix);
      }
    } while(result == Result.TIMEOUT);
  }  
  
  @Override
  public void run() {    
    while(true) {
      Matrix matrix = null;
      synchronized(matrices) {
        if (matrices.isEmpty()) {
          return;
        }
        matrix = matrices.remove(0);
      }
      search(matrix);
    }
  }
}
