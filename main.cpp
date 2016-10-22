#include "AStarManhattanDistance.h"
#include "AStarMisplacedTile.h"
#include "Menu.h"
#include "Puzzle.h"
#include "UniformCostSearch.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
   // Object Declarations
   Menu menu;
   Puzzle puzzle;
   UniformCostSearch uniformCostSearch;
   AStarManhattanDistance aStarManhattanDistance;
   AStarMisplacedTile aStarMisplacedTile;

   // Menu loop
   do{
      menu.GetUserInput();
      switch(menu.SearchAlgorithmSelected()){
         case SearchAlgorithm::UNIFORM_COST_SEARCH:
            uniformCostSearch.Run(menu.GetPuzzle());
            break;
         case SearchAlgorithm::A_STAR_MANHATTAN_DISTANCE:
            aStarManhattanDistance.Run(menu.GetPuzzle());
            break;
         case SearchAlgorithm::A_STAR_MISPLACED_TILE:
            aStarMisplacedTile.Run(menu.GetPuzzle());
            break;
         default:
            break;
      };
      //TODO: add delay to go from solution to getting input
      menu.PromptForExit();
   }while(!menu.ExitSelected());
   return 0;
}
