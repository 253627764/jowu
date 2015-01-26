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
import java.util.*;

public class SearchThread extends Thread {
    
  private Matrix matrix;
  private final DroppedTetrimino[][] randomSets;
  private final Random random;
  private int attempts;
  private int retries;
  private volatile boolean running;
  private ISearchListener searchListener;
  
  public SearchThread(
      Matrix matrix,
      DroppedTetrimino[][] randomSets,
      ISearchListener searchListener,
      long randomSeed) {
    this.matrix = matrix.copy();
    this.randomSets = randomSets;
    this.searchListener = searchListener;
    this.random = new Random(randomSeed);
    this.running = true;
  }
  
  private Result search(Matrix matrix, int remaining) {
    
    if (remaining == 0) {
      return Result.SOLUTION;
    }
    
    if (++attempts >= RealtimeSearcher.MAX_ATTEMPTS || !running) { 
      retries++;
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
    
    DroppedTetrimino[] randomSet = randomSets[
        random.nextInt(RealtimeSearcher.RANDOM_SETS)];
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
  
  @Override
  public void run() {    
    
    boolean expanded = false;
    int remainingCount = matrix.getRemainingTetriminoCount();
    Result result = null;  
    do {      
      matrix.clearTetriminos();
      attempts = 0;
      result = search(matrix, remainingCount);
      if (!expanded && (result == Result.NO_SOLUTION 
          || (retries > RealtimeSearcher.MAX_RETRIES 
              && result == Result.TIMEOUT))) {          
        expanded = true;
        retries = 0;
        matrix = matrix.expand();
        remainingCount = matrix.getRemainingTetriminoCount();
      }
    } while(running && result != Result.SOLUTION 
        && retries <= RealtimeSearcher.MAX_RETRIES);
    
    if (running) {
      searchListener.searchCompleted(result, matrix);
    }
  }
  
  public void halt() {
    running = false;
  }
}
