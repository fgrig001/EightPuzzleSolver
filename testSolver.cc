#include <iostream>
using namespace std;
#include "PuzzleState.h"

int main(){

   int values[9] = {1,3,2,4,5,6,0,7,8};
   PuzzleState puzzle(values);

   int size=3;
   int i=1;
   int actual_y=0;
   int actual_x=0;
   int new_h=0; 
   puzzle.SetG(puzzle.GetG()+1);
   for(int y=0;y<size;++y){
      for(int x=0;x<size;++x){
         int cur_val = puzzle.GetValue(x,y);
         cout<<"I: "<<i<<"  ";
         cout<<"Actual: "<<cur_val<<endl;
         if(cur_val != i && cur_val != 0){
            // Get actual location of value 
            actual_y = 0;
            actual_x = 0;
            while(cur_val > size){
               actual_y++;
               cur_val -= size;
            }
            actual_x = cur_val-1;
            cout<<"Actual x: "<<actual_x<<"  ";
            cout<<"Current x: "<<x<<endl;
            cout<<"Actual y: "<<actual_y<<"  ";
            cout<<"Current y: "<<y<<endl;
            // calculate distance
            new_h += abs(x - actual_x) + abs(y - actual_y);
         }
         i++;
      }
   }
   puzzle.SetH(new_h);

   puzzle.Print();
   cout<<"H: "<<puzzle.GetH()<<endl;
   return 0;
}
