#ifndef _PUZZLE_SOLVER_H
#define _PUZZLE_SOLVER_H

#include <vector>
#include <queue>
#include "PuzzleState.h"
#include <iostream>

class PuzzleSolver{
   public:
      // Constructor / Destructor
      PuzzleSolver(){}
      ~PuzzleSolver(){}
      // Puzzle Solving Algorithms
      void RunManhattanDistance(PuzzleState *puzzle);
      void RunMisplacedTile(PuzzleState *puzzle);
      void RunUniformCostSearch(PuzzleState *puzzle);
   private:
      // Heuristic types
      enum Heuristic{UNIFORM_COST,MISPLACED_TILE,MANHATTAN_DISTANCE};
      // Comparitor class
      struct ComparePuzzle{
         bool operator()(const PuzzleState *lhs,const PuzzleState *rhs) {
            return lhs->GetF() > rhs->GetF();
         }
      };
      // Helper functions
      void Run(PuzzleState *puzzle,Heuristic heuristic);
      void EstimateCost(PuzzleState *puzzle,Heuristic heuristic);
      // Data Structures
      std::priority_queue<PuzzleState*, std::vector<PuzzleState*>, ComparePuzzle> nodes;
      // Variables 
      int currentBest;
      int numberNodesExpanded{0};
      int maxStoredStates{0};
};

void PuzzleSolver::EstimateCost(PuzzleState *puzzle,Heuristic heuristic){
   int new_h=0;
   int i=1;
   int actual_x = 0;
   int actual_y = 0;
   int size = puzzle->GetSize();
   switch(heuristic){
      case UNIFORM_COST:
         puzzle->SetG(puzzle->GetG()+1);
         break;
      case MISPLACED_TILE:
         puzzle->SetG(puzzle->GetG()+1);
         for(int y=0;y<size;++y){
            for(int x=0;x<size;++x){
               if(x == size-1 && y == size-1){
                  if(puzzle->GetValue(x,y) != 0){ new_h++; }
               }else if(puzzle->GetValue(x,y) != 0 && puzzle->GetValue(x,y) != i){ new_h++; } // TODO: not sure about counting the 0 
               i++;
            }
         }
         puzzle->SetH(new_h);
         break;
      case MANHATTAN_DISTANCE:
         puzzle->SetG(puzzle->GetG()+1);
         for(int y=0;y<size;++y){
            for(int x=0;x<size;++x){
               int cur_val = puzzle->GetValue(x,y);
               if(cur_val != i && cur_val != 0){
                  // Get actual location of value 
                  actual_y = 0;
                  actual_x = 0;
                  while(cur_val > size){
                     actual_y++;
                     cur_val -= size;
                  }
                  actual_x = cur_val-1;
                  // calculate distance
                  new_h += abs(x - actual_x) + abs(y - actual_y);
               }
               i++;
            }
         }
         puzzle->SetH(new_h);
         break;
      default:
         puzzle->SetG(puzzle->GetG()+1);
         break;
   };
}

void PuzzleSolver::Run(PuzzleState *puzzle,Heuristic heuristic){
   numberNodesExpanded=0;
   maxStoredStates=0;
   EstimateCost(puzzle,heuristic);
   nodes.push(puzzle);
   PuzzleState *current_node;
   while(1){
      current_node = nodes.top();
      nodes.pop();
      // Check for diamater (No solution)
      if(current_node->GetG() > 31){
         std::cout<<"This problem has no solution!\n";
         break;
      }
      // Check for goal state
      if(current_node->IsGoalState()){
         std::cout<<"Goal State Reached!!\n";
         current_node->Print();
         std::cout<<"Solved in "<<current_node->GetG()<<" steps!\n";
         std::cout<<"Number of nodes expanded: "<<numberNodesExpanded<<std::endl;
         std::cout<<"Max size of queue: "<<maxStoredStates<<std::endl;
         // empty queue
         while(!nodes.empty()){
            nodes.pop();
         }
         return;
      }else{
         // If not initial state
         if(current_node->GetG() != 0){
            std::cout<<"The best state to expand with a g(n) = "<<current_node->GetG()
                     <<" and h(n) = "<<current_node->GetH()<<std::endl;
         }else{
            std::cout<<"Expanding Node\n";
         }
         numberNodesExpanded++;
         current_node->Print();
         // Expand new state 
         PuzzleState *new_state;
         for(int i=0;i<4;++i){
            new_state = current_node->Expand(i);
            if(new_state != NULL){
               EstimateCost(new_state,heuristic); 
               nodes.push(new_state);
            }
         }
         // Save max size of queue
         int temp = nodes.size();
         if(temp>maxStoredStates){ maxStoredStates=temp; }
      }
   }  

}

void PuzzleSolver::RunUniformCostSearch(PuzzleState *puzzle){
   Run(puzzle,UNIFORM_COST);
}

void PuzzleSolver::RunMisplacedTile(PuzzleState *puzzle){
   Run(puzzle,MISPLACED_TILE);
}

void PuzzleSolver::RunManhattanDistance(PuzzleState *puzzle){
   Run(puzzle,MANHATTAN_DISTANCE);
}

#endif
