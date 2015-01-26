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

public class PatternSearcher {
  
  public static final int MATRIX_WIDTH = 21;
  public static final int MATRIX_HEIGHT = 4;
  public static final int EMITTED_SQUARES = 4;
  public static final int RANDOM_SETS = 100000;
  public static final int MAX_ATTEMPTS = 1000;
  
  private DroppedTetrimino[][] randomSets;
  private Random random = new Random();
  
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

  private List<Matrix> generateMatrices() {
    
    List<Matrix> matrices 
        = Collections.synchronizedList(new ArrayList<Matrix>());
    generateMatrices(matrices, 
        new Matrix(MATRIX_WIDTH, MATRIX_HEIGHT), 0, EMITTED_SQUARES);
    
    return matrices;
  }  
  
  private void generateMatrices(List<Matrix> matrices, 
      Matrix matrix, int startIndex, int remaining) {
    if (remaining == 0) {
      matrices.add(matrix.copyTriples());
    } else if (MATRIX_WIDTH - startIndex >= remaining * 3) {
      for(int i = startIndex; i < MATRIX_WIDTH - 2; i++) {
        matrix.pushTriple(i);
        generateMatrices(matrices, matrix, 
            i + 3, remaining - 1);
        matrix.popTriple();
      }      
    }
  }
  
  private void printMatrices(List<Matrix> matrices, String name) {
    Collections.sort(matrices);
    if (matrices.size() > 0) {
      System.out.println(name + ":");
      System.out.println();
      for(Matrix matrix : matrices) {
        System.out.println(matrix);
      }
    }    
  } 
  
  public void launch() throws Throwable {
    System.out.println("initializing...");
    final List<Matrix> matrices = generateMatrices();
    final List<Matrix> solutions 
        = Collections.synchronizedList(new ArrayList<Matrix>());
    final List<Matrix> noSolutions 
        = Collections.synchronizedList(new ArrayList<Matrix>());    
    initializeRandomSets();   
    
    System.out.println("searching...");    
    final int processors = Runtime.getRuntime().availableProcessors();
    final Thread[] threads = new Thread[processors];
    for(int i = 0; i < processors; i++) {
      threads[i] = new SearchThread(
          matrices, solutions, noSolutions, randomSets);
      threads[i].start();
    }
    for(int i = 0; i < processors; i++) {
      threads[i].join();
    }
    
    System.out.println();
    printMatrices(solutions, "solutions");
    printMatrices(noSolutions, "no solutions");
  }
  
  public static void main(String[] args) throws Throwable {
    new PatternSearcher().launch();
  }
}
