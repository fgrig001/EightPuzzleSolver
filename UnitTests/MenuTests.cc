#include "../Menu.h"
#include <iostream>
using namespace std;

// Unit Test Prototypes
void PuzzleSelection();
void AlgorithmSelection();

int main(){
   //PuzzleSelection();
   AlgorithmSelection();
   return 0;
}

// Unit Test Implementations 
void PuzzleSelection(){
   Menu menu;
   menu.GetPuzzleInput();
   menu.GetPuzzle()->Print();
}

void AlgorithmSelection(){
   Menu menu;
   menu.GetSearchAlgorithmInput();
   cout<<"Search algorithm selected: "<<menu.SearchAlgorithmSelected()<<endl;
}
