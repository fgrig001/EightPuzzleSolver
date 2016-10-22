#ifndef _PUZZLE_STATE_H
#define _PUZZLE_STATE_H

#include <cmath>
#include <iostream>

class PuzzleState{
   public:
      // Constructors
      PuzzleState(int* values, int size=3);
      PuzzleState(const PuzzleState &obj);
      ~PuzzleState();
      PuzzleState &operator=(const PuzzleState &obj);
      // Setters
      bool SetValue(int x,int y,int data);
      void SetG(int _g){ g = _g; }
      void SetH(int _h){ h = _h; }
      // Getters
      int GetG(){ return g; }
      int GetF(){ return g+h; }

      void Print();
      
   private:
      int **puzzleData;
      int puzzleSize;
      int g{0};
      int h{0};
};

// Constructor
PuzzleState::PuzzleState(int* values, int size):
   puzzleSize(size) 
{
   // Initialize Puzzle data structure
   puzzleData = new int*[puzzleSize];
   for(int i=0;i<puzzleSize;++i){
      puzzleData[i] = new int[puzzleSize];
   }
   // Initialize default values TODO: expand for larger puzzle sizes
   int i=0;
   for(int y=0;y<puzzleSize;++y){
      for(int x=0;x<puzzleSize;++x){
         puzzleData[y][x] = values[i];
         i++;
      }
   }
}

PuzzleState::PuzzleState(const PuzzleState &obj){
   std::cout<<"Copy Constructor!"<<std::endl;
   // Coppy over values
   g = obj.g;
   h = obj.h;
   puzzleSize = obj.puzzleSize;
   // Initialize Puzzle data structure
   puzzleData = new int*[puzzleSize];
   for(int i=0;i<puzzleSize;++i){
      puzzleData[i] = new int[puzzleSize];
   }
   // Copy over puzzle values
   for(int y=0;y<puzzleSize;++y){
      for(int x=0;x<puzzleSize;++x){
         puzzleData[y][x] = obj.puzzleData[y][x];
      }
   }
}

PuzzleState::~PuzzleState(){
   for(int i=0;i<puzzleSize;++i){
      delete[] puzzleData[i];
   }
   delete[] puzzleData;
   puzzleData =NULL;
}

PuzzleState &PuzzleState::operator=(const PuzzleState &obj){
   std::cout<<"= Overload!"<<std::endl;
   // Coppy over values
   g = obj.g;
   h = obj.h;
   puzzleSize = obj.puzzleSize;
    // Initialize Puzzle data structure
   puzzleData = new int*[puzzleSize];
   for(int i=0;i<puzzleSize;++i){
      puzzleData[i] = new int[puzzleSize];
   }
   // Copy over puzzle values
   for(int y=0;y<puzzleSize;++y){
      for(int x=0;x<puzzleSize;++x){
         puzzleData[y][x] = obj.puzzleData[y][x];
      }
   }
}

void PuzzleState::Print(){
   for(int y=0;y<puzzleSize;++y){
      for(int x=0;x<puzzleSize;++x){
         if(puzzleData[y][x] == 0){
            std::cout<<"b ";
         }else{
            std::cout<<puzzleData[y][x]<<" ";
         }
      }
      std::cout<<std::endl;
   }
}

#endif
