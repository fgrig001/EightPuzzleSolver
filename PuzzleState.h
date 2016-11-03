#ifndef _PUZZLE_STATE_H
#define _PUZZLE_STATE_H

#define SWAP(A,B) A=A^B,B=A^B,A=A^B

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
      int GetValue(int x,int y);
      int GetG(){ return g; }
      int GetH(){ return h; }
      int GetF() const { return g+h; }
      int GetSize(){ return puzzleSize; }

      bool IsGoalState();
   
      // Directions: 0 Up, 1 Down, 2 Left, 3 Right 
      PuzzleState *Expand(int direction);

      void Print();
      
   private:
      int zeroLocation[2];
      int **puzzleData;
      int puzzleSize;
      int g{-1};
      int h{0};
      int parentDirection{-1};
};

/* Constructor */
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
         if(values[i] == 0){
            zeroLocation[0] = y;
            zeroLocation[1] = x;
         }
         i++;
      }
   }
}

/* Copy Constructor */
PuzzleState::PuzzleState(const PuzzleState &obj){
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
   zeroLocation[0] = obj.zeroLocation[0];
   zeroLocation[1] = obj.zeroLocation[1];
}

PuzzleState::~PuzzleState(){
   for(int i=0;i<puzzleSize;++i){
      delete[] puzzleData[i];
   }
   delete[] puzzleData;
   puzzleData =NULL;
}

PuzzleState &PuzzleState::operator=(const PuzzleState &obj){
   // Copy over values
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

PuzzleState *PuzzleState::Expand(int direction){
   PuzzleState *new_state = new PuzzleState(*this);
   int y = zeroLocation[0/*y*/];
   int x = zeroLocation[1/*x*/];
   new_state->parentDirection;
   switch(direction){
      case 0: //EXPAND_UP
         if(y == 0 || parentDirection == 0){
            delete new_state;
            return NULL;
         }else{
            SWAP(new_state->puzzleData[y][x],new_state->puzzleData[y-1][x]);
            new_state->zeroLocation[0] -= 1;
            new_state->parentDirection = 1;
            return new_state;
         }
         break;
      case 1: //EXPAND_DOWN
         if(y == puzzleSize-1 || parentDirection == 1){
            delete new_state;
            return NULL;
         }else{
            SWAP(new_state->puzzleData[y][x],new_state->puzzleData[y+1][x]);
            new_state->zeroLocation[0] += 1;
            new_state->parentDirection = 0;
            return new_state;
         }
         break;
      case 2: //EXPAND_LEFT
         if(x == 0 || parentDirection == 2){
            delete new_state;
            return NULL;
         }else{
            SWAP(new_state->puzzleData[y][x],new_state->puzzleData[y][x-1]);
            new_state->zeroLocation[1] -= 1;
            new_state->parentDirection = 3;
            return new_state;
         }
         break;
      case 3: //EXPAND_RIGHT
         if(x == puzzleSize-1 || parentDirection == 3){
            delete new_state;
            return NULL;
         }else{
            SWAP(new_state->puzzleData[y][x],new_state->puzzleData[y][x+1]);
            new_state->zeroLocation[1] += 1;
            new_state->parentDirection = 2;
            return new_state;
         }
         break;
      default:
         delete new_state;
         return NULL;
   };
}

bool PuzzleState::IsGoalState(){
   int i=1;
   for(int y=0;y<puzzleSize;++y){
      for(int x=0;x<puzzleSize;++x){
         if(x == puzzleSize-1 && y == puzzleSize-1){
            return true;
         }else if(puzzleData[y][x] != i){
            return false; 
         }
         i++;
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

/* Get puzzle value, out of bounds returns -1 */
int PuzzleState::GetValue(int x,int y){
   if(x>=puzzleSize || y>=puzzleSize){
      return -1;
   }
   return puzzleData[y][x];
}

/* Set puzzle value, out of bound returns false */
bool PuzzleState::SetValue(int x,int y,int data){
   if(x>=puzzleSize || y>=puzzleSize){
      return false;
   }
   puzzleData[y][x] = data;
   return true;
}

#endif
