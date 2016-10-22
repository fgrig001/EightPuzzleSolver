#ifndef _N_PUZZLE_ALGORITHM_H
#define _N_PUZZLE_ALGORITHM_H

#include "Puzzle.h"

class NPuzzleAlgorithm{
   public:
      virtual NPuzzleAlgorithm();
      virtual Run(Puzzle _puzzle);
};

#endif
