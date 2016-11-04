#The Eight Puzzle

An analysis of three solutions using C++

## Introduction and Overview

### The Algorithms

This project requires us to implement 3 different algorithms for solving the classic 8 puzzle. The first and slowest of these is **Uniform Cost Search** which simply searches all paths, checking the ones that require the minimum amount of steps first (essentially a breadth first search). The remaining two algorithms are variations of A*, one using the **Misplaced tile Heuristic** which counts the number of misplaced tiles and uses that as the heuristic. The other heuristic used is the **Manhattan Distance Heuristic** which sums up the distance of every misplaced tile to their respective home locations. 

### The Implementation 

I decided to use C++ to implement this project since I work with it every day at my job and felt that I would learn more having to implement the low level details of the algorithm. I used an object oriented approach implementing the following files:

* **Main.cpp** - The primary program that ties everything together and implements the basic high level logic

* **Menu.h** - The menu object which handles prompting the user for inputs and storing those inputs for further use.

* **PuzzleState.h** - This object represents a single puzzle state and has useful member function that allow the algorithms to easily extract data and process the states. 

* **PuzzleSolver.h** - The puzzle solver object contains the logic for each of the algorithms implementations. Since they are all simply variations of A* much of the code is generalized to eliminate redundant code. 

## Issues Encountered

Writing out these algorithms and troubleshooting them resulted in a lot of learning experiences. I learned the most from the errors that I encountered as well as the solutions that I implemented to solve them. 

### Loops and Repeated States 

Once I finished the initial code for this project I noticed that I was not checking for repeated states, causing (especially uniform cost search) to sometimes get hung up in a loop. This was a problem for me since it would take much more time and space to save a list of past states and then compare every newly expanded state to that list. Due to the complexity of the issue I decided to instead mitigate the problem by simply modifying the PuzzleState object to remember the position of the 0 from its previous state and simply not go back to that state again. This made a huge difference and I have yet to run a test that gets stuck in a loop. This solution could even be expanded such that each state remembers it’s n previous states.

### Discovering that Problem is Unsolvable 

After a good deal of testing I realized that my program would not be able to find that a puzzle had no solution. Since it does not check for repeated states it would potentially run indefinitely. My solution for this problem was to simply stop the program once g(n) reached the diameter of the problem This stems from the fact that if there was a solution it would have found it before reaching the diameter due to the optimality of A* search. 

## Algorithm Comparison 

I ran my solver on multiple puzzles, recording the number of nodes expanded (as a metric for time complexity) as well as the maximum queue size (as a metric for space complexity). 

<table>
   <tr>
      <td>
         2 step solution 
      </td>
      <td>
         <table>
            <tr>
               <td>
               Algorithm 
               </td>
               <td>
               Nodes Expanded
               </td>
               <td>
               Max Queue Size
               </td>
            </tr>
            <tr>
               <td>
               Uniform Cost
               </td>
               <td>
               3
               </td>
               <td>
               4
               </td>
            </tr>
            <tr>
               <td>
               A* w/ Misplaced Tile
               </td>
               <td>
               2
               </td>
               <td>
               3
               </td>
            </tr>
            <tr>
               <td>
               A* w/ Manhattan Distance
               </td>
               <td>
               2
               </td>
               <td>
               3
               </td>
            </tr>
         </table>
      </td>
   </tr>
   <tr>
      <td>
         4 step solution 
      </td>
      <td>
         Algorithm 
         Nodes Expanded
         Max Queue Size
         Uniform Cost
         28
         18
         A* w/ Misplaced Tile
         4
         4
         A* w/ Manhattan Distance
         4
         4
      </td>
   </tr>
   <tr>
      <td>
         11 step solution </td>
      <td>
         Algorithm 
         Nodes Expanded
         Max Queue Size
         Uniform Cost
         1739
         1158
         A* w/ Misplaced Tile
         60
         47
         A* w/ Manhattan Distance
         17
         17
      </td>
   </tr>
   <tr>
      <td>
         15 step solution 
      </td>
      <td>
         Algorithm 
         Nodes Expanded
         Max Queue Size
         Uniform Cost
         13214
         9168
         A* w/ Misplaced Tile
         352
         259
         A* w/ Manhattan Distance
         52
         39
      </td>
   </tr>
   <tr>
      <td>
         22 step solution 
      </td>
      <td>
         Algorithm 
         Nodes Expanded
         Max Queue Size
         Uniform Cost
         580368
         455874
         A* w/ Misplaced Tile
         11123
         8116
         A* w/ Manhattan Distance
         370
         255
      </td>
   </tr>
   <tr>
      <td>
         27 step solution 
      </td>
      <td>
         Algorithm 
         Nodes Expanded
         Max Queue Size
         Uniform Cost
         7382676
         5596218
         A* w/ Misplaced Tile
         161113
         117753
         A* w/ Manhattan Distance
         8434
         5636
      </td>
   </tr>
</table>


## Observations and Conclusion 

A major observation that I made was the importance and power of pruning. Although I was not able to check for all repeated states I was able to prune previous states for a great increase in both time and space complexity. 

As we can see from the above data, using A* with a strong heuristic has major advantages over simply using a generic uniform cost search algorithm. Estimating the remaining distance to the goal state has exponential increases in both space and time complexity. When running the  longer tests I especially noticed how the A* searches finished within a handful of seconds while the uniform cost search took minutes (10-15 in total) to complete. 

## Trace of the Manhattan Distance A* 

Welcome to Frederick Grigsbys 8-puzzle solver.

Type "1" to use a default puzzle, or "2" to enter your own puzzle.

2

Enter your puzzle, use a zero to represent the blank

Enter row 1, use space or tabs between numbers    1 2 3

Enter row 2, use space or tabs between numbers    4 0 6

Enter row 3, use space or tabs between numbers    7 5 8

Enter your choice of algorithm

1. Uniform Cost Search

2. A* with the Misplaced Tile heuristic

3. A* with the Manhattan distance heuristic

3

Expanding Node

1 2 3

4 b 6

7 5 8

The best state to expand with a g(n) = 1 and h(n) = 1

1 2 3

4 5 6

7 b 8

Goal State Reached!!

1 2 3

4 5 6

7 8 b

Solved in 2 steps!

Number of nodes expanded: 2

Max size of queue: 5

Type "1" to run solver again, or "2" to exit.

2

