#include <iostream>
#include <vector>
#include <cmath>
unsigned int modVal;

std::vector<std::vector<int>> domove(std::vector<std::vector<int>> puzzle, int dim1, int dim2, bool reverse)
{
  int loops = 1;
  if(reverse && modVal == 5)
  {
    loops = 3;
  }
  else if(reverse && modVal == 7)
  {
    loops = 2;
  }
  for(int i = 0; i < loops; i++)
  {
    unsigned int inc = puzzle[dim1][dim2];
    puzzle[dim1][dim2] = (puzzle[dim1][dim2] + inc) % modVal;
    if(dim1 - 1 >= 0)
      puzzle[dim1 - 1][dim2] = (puzzle[dim1 - 1][dim2] + inc) % modVal;
    if(dim2 - 1 >= 0)
      puzzle[dim1][dim2 - 1] = (puzzle[dim1][dim2 - 1] + inc) % modVal;
    if(dim1 + 1 < (int)puzzle.size())
      puzzle[dim1 + 1][dim2] = (puzzle[dim1 + 1][dim2] + inc) % modVal;
    if(dim2 + 1 < (int)puzzle[0].size())
      puzzle[dim1][dim2 + 1] = (puzzle[dim1][dim2 + 1] + inc) % modVal;
  }
  return puzzle;
}

int main()
{
  std::cout << "Mod val: ";
  std::cin >> modVal;
  std::cout << "Board size: ";
  int size;
  std::cin >> size;
  int sizeSq = size * size;
  std::vector<int> row(size,1);
  std::vector<std::vector<int>> puzzle(size,row);
  std::vector<std::vector<int>> scramble = puzzle;
  std::vector<std::vector<int>> solvedpuzzle = puzzle;
  for(unsigned int i = 0; i < scramble.size(); i++)
  {
    std::string temp;
    std::cin >> temp;
    for(int j = 0; j < size; j++)
    {
      scramble[i][j] = temp[j] - 48;
    }
  }
  bool solution = false;
  while(!solution)
  {
    int numMoves = 0;
    while(!solution)
    {
      numMoves++;
      std::cout << "Checking " << numMoves << "..." << std::endl;
      std::vector<int> moves(numMoves,0);
      bool done = false;
      std::vector<std::vector<std::vector<int>>> states(numMoves,scramble);
      int lastIncremented = 0;
      while(!done)
      {
        int toIncr = numMoves - 1;
        puzzle = scramble;
        if(lastIncremented > 0)
        {
          puzzle = states[lastIncremented];
        }
        bool breakL = false;
        for(unsigned int i = lastIncremented; i < moves.size() && !breakL; i++)
        {
          states[i] = puzzle;
          if(i > 0 && (modVal == 3 || modVal == 7))
          {
            if(moves[i] == moves[i - 1])
            {
              toIncr = i;
              breakL = true;
            }
          }
          if(puzzle[moves[i]%size][std::floor((moves[i]-((moves[i] >= sizeSq ? sizeSq : 0)))/size)] == 0)
          {
            toIncr = i;
            breakL = true;
          }
          else
          {
            puzzle = domove(puzzle,moves[i]%size,std::floor((moves[i]-((moves[i] >= sizeSq ? sizeSq : 0)))/size),moves[i] >= size * size);
          }
        }
        if(puzzle == solvedpuzzle)
        {
          done = true;
          solution = true;
          for(unsigned int i = 0; i < moves.size(); i++)
          {
            std::cout << "" << moves[i]%size << std::floor((moves[i]-((moves[i] >= sizeSq ? sizeSq : 0)))/size) << (moves[i] >= sizeSq ? "\'" : "") << " ";
          }
        }
        if(!done)
        {
          int incrementing = toIncr;
          bool stillIncr = true;
          while(stillIncr)
          {
            moves[incrementing]++;
            if(moves[incrementing] >= sizeSq * (modVal == 3 ? 1 : 2))
            {
              moves[incrementing] = 0;
              incrementing--;
              if(incrementing < 0)
              {
                done = true;
                stillIncr = false;
              }
            }
            else
            {
              stillIncr = false;
              lastIncremented = incrementing;
            }
          }
        }
      }
    }
  }
  return 0;
}