#ifndef _AIBASE
#define _AIBASE

#if SIDE_LENGTH == 8
const int initBoardValue[SAFE_LENGTH][SAFE_LENGTH] = 
{
    {-8, -8, -8, -8, -8, -8, -8, -8, -8, -8},
       {-8, 8,-2, 3, 3, 3, 3,-2, 8, -8},
      {-8, -2, 0, 2, 2, 2, 2, 0, -2, -8},
       {-8, 3, 2, 1, 1, 1, 1, 2, 3, -8},
       {-8, 3, 2, 1, 1, 1, 1, 2, 3, -8},
       {-8, 3, 2, 1, 1, 1, 1, 2, 3, -8},
       {-8, 3, 2, 1, 1, 1, 1, 2, 3, -8},
      {-8, -2, 0, 2, 2, 2, 2, 0, -2, -8},
       {-8, 8,-2, 3, 3, 3, 3,-2, 8, -8},
    {-8, -8, -8, -8, -8, -8, -8, -8, -8, -8}
};

#else
const int boardValue[SAFE_LENGTH][SAFE_LENGTH]{}; //Temporary method
#endif



#endif 
