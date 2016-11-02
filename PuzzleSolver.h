#ifndef _PUZZLE_SOLVER_H
#define _PUZZLE_SOLVER_H

#include <vector>
#include <queue>
#include "PuzzleState.h"
#include <iostream>

class PuzzleSolver{
   public:
      PuzzleSolver(){}
      ~PuzzleSolver(){}
      void RunManhattanDistance(PuzzleState *puzzle);
      void RunMisplacedTile(PuzzleState *puzzle);
      void RunUniformCostSearch(PuzzleState *puzzle);
   private:
      enum Heuristic{UNIFORM_COST,MISPLACED_TILE,MANHATTAN_DISTANCE};
      // Comparitor class
      struct ComparePuzzle{
         bool operator()(const PuzzleState *lhs,const PuzzleState *rhs) {
            // return "true" if "p1" is ordered before "p2", for example:
            int l = lhs->GetF();
            int r = rhs->GetF(); 
            return l > r;
         }
      };
      // Helper functions
      void Expand(PuzzleState *node);
      void Run(PuzzleState *puzzle,Heuristic heuristic);
      void EstimateCost(PuzzleState *puzzle,Heuristic heuristic);
      // Data Structures
      std::priority_queue<PuzzleState*, std::vector<PuzzleState*>, ComparePuzzle> nodes;
      // Variables 
      int CurrentBest;
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
                  while(cur_val >= size){
                     actual_y++;
                     cur_val -= size;
                  }
                  actual_x = cur_val;
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
   EstimateCost(puzzle,heuristic);
   nodes.push(puzzle);
   PuzzleState *current_node;
   while(1){
      current_node = nodes.top();
      nodes.pop();
      if(current_node->IsGoalState()){
         std::cout<<"Goal State Reached!!\n";
         current_node->Print();
         // TODO: Print results
         return;
      }else{
         // TODO: Print results
         if(current_node->GetG() != 0){
            std::cout<<"The best state to expand with a g(n) = "<<current_node->GetG()
                     <<" and h(n) = "<<current_node->GetH()<<std::endl;
         }else{
            std::cout<<"Expanding Node\n";
         }
         current_node->Print();
         // Expand new statte 
         PuzzleState *new_state;
         for(int i=0;i<4;++i){
            new_state = current_node->Expand(i);
            if(new_state != NULL){
               EstimateCost(new_state,heuristic); 
               nodes.push(new_state);
            }
         }
         delete current_node;
      }
   }  

}

void PuzzleSolver::Expand(PuzzleState *node){
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
