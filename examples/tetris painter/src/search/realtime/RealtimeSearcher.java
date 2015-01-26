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

public class RealtimeSearcher implements ISearchListener {
  
  public static final int MATRIX_WIDTH = 21;
  public static final int RANDOM_SETS = 100000;
  public static final int MAX_ATTEMPTS = 1000;
  public static final int MAX_RETRIES = 100;
  
  private final Object MONITOR = new Object();  
  private DroppedTetrimino[][] randomSets;
  private Random random = new Random();
  private Result result;
  private Matrix solution;
  private int runningThreads;
  
  public RealtimeSearcher() {
    initializeRandomSets();
  }
  
  private void initializeRandomSets() {
    int total = 0;
    for(int i = 0; i < Tetrimino.TETRIMINOS.length; i++) {
      total += MATRIX_WIDTH - Tetrimino.TETRIMINOS[i].width + 1;
    }
    randomSets = new DroppedTetrimino[RANDOM_SETS][total];
    for(int i = 0; i < RANDOM_SETS; i++) {
      generateRandomSet(randomSets[i]);
    }
  }
  
  private void generateRandomSet(DroppedTetrimino[] randomSet) {
    ArrayList<DroppedTetrimino> droppedTetriminos = new ArrayList<>();
    for(int i = 0; i < Tetrimino.TETRIMINOS.length; i++) {
      for(int j = MATRIX_WIDTH - Tetrimino.TETRIMINOS[i].width; 
          j >= 0; j--) {
        droppedTetriminos.add(new DroppedTetrimino(Tetrimino.TETRIMINOS[i], j));
      }
    }
    for(int i = 0; i < randomSet.length; i++) {
      randomSet[i] = droppedTetriminos.remove(
          random.nextInt(droppedTetriminos.size()));
    }
  }

  @Override
  public void searchCompleted(Result result, Matrix solution) {
    synchronized(MONITOR) {
      runningThreads--;
      if (this.result == null && result == Result.SOLUTION) {        
        this.result = result;
        this.solution = solution;
      }
      MONITOR.notifyAll();
    }
  }
  
  public Result search(Matrix matrix) throws Throwable {
    
    final int processors = Runtime.getRuntime().availableProcessors();
    final SearchThread[] threads = new SearchThread[processors];
       
    this.result = null;
    this.solution = null;    
    final long nanoTime = System.nanoTime();
    runningThreads = processors;
    for(int i = 0; i < processors; i++) {
      threads[i] = new SearchThread(matrix, randomSets, this, nanoTime + i * 7);      
    }    
    for(int i = 0; i < processors; i++) {
      threads[i].start();
    }    
    synchronized(MONITOR) {      
      while(result != Result.SOLUTION && runningThreads > 0) {
        MONITOR.wait();
      }
    }
    for(int i = 0; i < processors; i++) {
      threads[i].halt();
    }    
    for(int i = 0; i < processors; i++) {
      threads[i].join();
    }    

    if (solution != null) {
      matrix.set(solution);
    } else {
      return Result.TIMEOUT;
    }
    
    return result;
  }
}
