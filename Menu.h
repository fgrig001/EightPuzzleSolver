#ifndef _MENU_H
#define _MENU_H

#include "PuzzleState.h"
#include <iostream>

int PUZZLE_SIZE = 3;

class Menu{
   public:
      enum SearchAlgorithm{UNIFORM_COST_SEARCH=1,A_STAR_MANHATTAN_DISTANCE=3,A_STAR_MISPLACED_TILE=2};

      // Constructor 
      Menu() {}
      ~Menu();

      void GetUserInput();
      void PromptForExit();

      // Getters
      SearchAlgorithm SearchAlgorithmSelected(){ return searchType; }
      PuzzleState *GetPuzzle(){ return puzzle; }
      bool ExitSelected(){ return exit; }
      // Helper Functions TODO: make private
      void GetPuzzleInput();
      void GetSearchAlgorithmInput();
   private:
      // Variables
      SearchAlgorithm searchType{UNIFORM_COST_SEARCH};
      PuzzleState *puzzle{NULL};
      bool exit{0};
      int defaultValues[9] = {0,1,2,4,5,3,7,8,6};
      int *userInputValues;
      int puzzleSize{PUZZLE_SIZE}; // 3x3
};

Menu::~Menu(){
   if(puzzle != NULL){
      delete puzzle;
   }
}

void Menu::GetUserInput(){
   GetPuzzleInput();
   GetSearchAlgorithmInput();
}

void Menu::PromptForExit(){
   if(puzzle != NULL){
      delete puzzle;
      puzzle = NULL;
   }
   std::cout<<std::endl;
   std::cout<<"Type \"1\" to run solver again, or \"2\" to exit."<<std::endl; 
   int _temp;
   std::cin>>_temp;
   if(_temp == 2){ exit = 1; }
}

void Menu::GetPuzzleInput(){
   int input_type;
   std::cout<<std::endl;
   std::cout<<"Welcome to Freerick grigsbys 8-puzzle solver."<<std::endl; 
   std::cout<<"Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle."<<std::endl; 
   std::cin>>input_type;
   userInputValues = new int[puzzleSize*puzzleSize];
   if(input_type == 2){ // User enters puzzle
      int tmp_count=0;
      std::cout<<"Enter your puzzle, use a zero to represent the blank"<<std::endl; 
      for(int j=0;j<puzzleSize;++j){
         std::cout<<"Enter row "<<j+1<<", use space or tabs between numbers\t";
         for(int i=0;i<puzzleSize;++i,++tmp_count){
            std::cin>>userInputValues[tmp_count];
         }
      }
      puzzle = new PuzzleState(userInputValues,puzzleSize);
   }
   else{ // Default Puzzle
      puzzle = new PuzzleState(defaultValues,puzzleSize);
   }
}

void Menu::GetSearchAlgorithmInput(){
   int tmp_int;
   std::cout<<std::endl;
   std::cout<<"Enter your choice of algorithm"<<std::endl; 
   std::cout<<"1. Uniform Cost Search"<<std::endl; 
   std::cout<<"2. A* with the Misplaced Tile heuristic"<<std::endl; 
   std::cout<<"3. A* with the Manhattan distance heuristic"<<std::endl; 
   do{
      std::cin>>tmp_int;
      searchType=(SearchAlgorithm)tmp_int;
      if(tmp_int<1 || tmp_int>3){
         std::cout<<"Selection Not Valid!"<<std::endl; 
      }
   }while(tmp_int<1 || tmp_int>3);
}

#endif
