#include <stdlib.h>
//makes the 4 x 4 result grid
int **InitGrid(void)
{
  int i;
  int **grid;

  i = 0;
  grid = malloc(8 * 4);
  while (i < 4)
  {
    grid[i] = malloc(4 * 4);
    i++;
  }
  return (grid);
}

//check if element in a given position is already in a row or a column
int checkNumberRepition(int x, int y, int **grid)
{
  int i;

  i = 0;
  while (i < x)
  {
    if (grid[y][i] == grid[y][x]) 
      return (0);
    i++;
  }
  i = 0;
  while (i < y)
  {
    if (grid[i][x] == grid[y][x]) 
      return (0);
    i++;
  }
  return (1);
}

int CheckRowClueR(int x, int y, int **grid, int *clues)
{
  int i;
  int max;
  int count;

  i = 3;
  max = -1;
  count = 0;

  if (x != 3 || clues[4 + y] == 0) 
    return (1);
  while (i >= 0)
  {
    if (grid[y][i] > max)
    {
      max = grid[y][i];
      count++;
    }
    i--;
  }
  if (count != clues[4 + y]) 
    return (0);
  return (1);
}

int CheckRowClueL(int x, int y, int **grid, int *clues)
{
  int i;
  int max;
  int count;

  i = 0;
  max = -1;
  count = 0;

  if (clues[15 - y] == 0) 
    return (1);
  while (i <= x)
  {
    if (grid[y][i] > max)
    {
      max = grid[y][i];
      count++;
    }
    if (count > clues[15 - y]) 
      return (0);
    i++;
  }
  if (count != clues[15 - y] && x == 3) 
    return (0);
  return (1);
}

int CheckColClueU(int x, int y, int **grid, int *clues)
{
  int i;
  int max;
  int count;

  i = 0;
  max = -1;
  count = 0;

  if (clues[x] == 0) 
    return (1);
  while (i <= y)
  {
    if (grid[i][x] > max)
    {
      max = grid[i][x];
      count++;
    }
    if (count > clues[x]) 
      return (0);
    i++;
  }
  if (count != clues[x] && y == 3) 
    return (0);
  return (1);
}

int CheckColClueD(int x, int y, int **grid, int *clues)
{
  int i;
  int max;
  int count;

  i = 3;
  max = -1;
  count = 0;

  if (y != 3 || clues[11 - x] == 0) 
    return (1);
  while (i >= 0)
  {
    if (grid[i][x] > max)
    {
      max = grid[i][x];
      count++;
    }
    i--;
  }
  if (count != clues[11 - x]) 
    return (0);
  return (1);
}

int CheckConstraint(int x, int y, int **grid, int *clues)
{
  if (!checkNumberRepition(x, y, grid)) 
    return (0);
  if (!CheckRowClueR(x, y, grid, clues)) 
    return (0);
  if (!CheckRowClueL(x, y, grid, clues)) 
    return (0);
  if (!CheckColClueU(x, y, grid, clues)) 
    return (0);
  if (!CheckColClueD(x, y, grid, clues)) 
    return (0);
  return (1);
}

int SolveRecursive(int x, int y, int **grid, int *clues)
{
  int i;
  i = 0;

  while (i < 4)
  {
    grid[y][x] = i + 1;
    if (CheckConstraint(x, y, grid, clues))
    {
      if (x == 3 && y == 3) 
        return (1);
      else if (SolveRecursive((1 + x) % 4, y + x / 3, grid, clues)) 
        return (1);
    }
    i++;
  }
  return (0);
}

int **SolvePuzzle(int *clues)
{
  int **grid = InitGrid();
  
  SolveRecursive(0, 0, grid, clues);
  return (grid);
}

int main(){
    int clues[] = {4,3,2,1,1,2,2,2,2,2,2,1,1,2,3,4};
    int **res = SolvePuzzle(clues);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            printf("%d",res[i][j]);
        printf("\n");
    }
    return 0;
}