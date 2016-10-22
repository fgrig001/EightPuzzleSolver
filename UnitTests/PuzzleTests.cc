
#include "../PuzzleState.h"
#include <iostream>
using namespace std;

// Unit Test Prototypes
void PrintPuzzle();
void CopyConstructor();

int main(){
   CopyConstructor();
   //PrintPuzzle();
   return 0;
}

// Unit Test Implementations 
void PrintPuzzle(){
   int data[9] = {1,2,3,4,8,0,7,6,5};
   PuzzleState puzzle(data,3);
   puzzle.Print();
}

void CopyConstructor(){
   int data[9] = {1,2,3,4,8,0,7,6,5};
   PuzzleState puzzle(data,3);
   puzzle.Print();
   PuzzleState *puzzle2 = new PuzzleState(puzzle);
   puzzle2->Print();
}
