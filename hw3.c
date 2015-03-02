#include <stdio.h>
#pragma warning(disable: 4996)

// This program exercises the operations of pointers and arrays
#define maxrow 50
#define maxcolumn 50
#define triple(x) x % 3 ==0  ? 1:0

char maze[maxrow][maxcolumn]; // Define a static array of arrays of characters.
int lastrow = 0;
int x; // needs to be declared for macro to work
int p;
// Forward Declarations
//int triple(int);
void initialization(int, int);
void randommaze(int, int);
void printmaze(int, int);
//void encryptmaze(int, int, int);
//int triple(int x) {   // % is modulo operator.
//  return ((x % 3 == 0) ? 1 : 0);
//}

void initialization(int r, int c) {
  int i, j;
  for (i = 0; i < maxrow; i++){
    maze[i][0] = 'X';     // add border 
    maze[i][c - 1] = 'X'; // add border 
    maze[i][c] = '\0';    // add string terminator 

    for (j = 1; j < c - 1; j++)
    {
      if ((i == 0) || (i == r - 1))
        maze[i][j] = 'X'; // add border 
      else
        maze[i][j] = ' '; // initialize with space 
    }
  }
}

// Add 'X' into the maze at random positions
void randommaze(int r, int c) {
  char *pointer  = maze;
  char i, j, d;
  for (i = 1; i < r - 1; i++) {
    for (j = 1; j < c - 2; j++) {
      d = rand();
      if (triple(d))
      {
        *(pointer+(i*c+j))= 'X';   
        //maze[i][j] = 'X';
      }
    }}
  i = rand() % (r - 2) + 1;
  j = rand() % (c - 3) + 1;
  maze[i][j] = 'S'; // define Starting point
  do
  {
    i = rand() % (r - 2) + 1;
    j = rand() % (c - 3) + 1;
  } while (maze[i][j] == 'S');
  
  maze[i][j] = 'G'; // define Goal point
}

// Print the maze
void printmaze(int r, int c) {
  int i, j;
  printf("\n");
  char *pointer = maze;
  for (i = 0; i < r; i++) {
    for (j = 0; j < c; j++)
      printf("%c", maze[i][j]);
    printf("\n");
  }
}

void encryptmaze(int r, int c)
{
  int i, j;
  char *pointer = &maze;
  //printf("\nEncryptmaze start:\n");
  for(i = 0; i < r; i++)
  {
    for(j = 0; j < c; j++)
    {
      pointer = &maze[i][j];// this was the whole reason the assignemnt is so late.  I could not figure out why or how using char *p = *(p+i*c+j) when initiated at line 80 wouldn't work. But it works here.
      //char *pointer;
      //*pointer = *(p+i*c+j);
      //printf(" |%c", *pointer);
      if(*pointer  == ' ')
      {
        *pointer += i;
        //*(pointer+(i*c+j)) += i;   This is the math behind finding any position in the array. A much more efficient way to do things, than just incrementing by one.
      }
      else if(*pointer == 'G')
      {
          *pointer += j;
      }
      else if(*pointer == 'S')
      {
          *pointer += j;
      }
      else if(*pointer == 's')
      {
        *pointer += j;
      }
      pointer++; // This was originally being use inside of every if and if/else. I was not incrementing when the case was "X", which was causing me to uselessly change the same value maxarray times
 
      /* testing the pointer assign. This proved that the way that I was assigning the pointer was incorrect.
      printf(" |%c", maze[i][j]);
      if(maze[i][j] == ' ')
      {
        maze[i][j] += i;
      }...
      printf("%c| ", maze[i][j]);*/
    }
    //printf("\n"); 
  }
}

void decryptmaze(int r,int c)
{
  int i, j;
  char *pointer = &maze;
  for(i = 0; i < r; i++)
  {
    for(j = 0; j < c; j++)
    {
      pointer = &maze[i][j];
      if(*pointer  == ' ' + i)
      {
        *pointer -= i;
        //*(pointer+(i*c+j)) += i;   This is the math behind finding any position in the array. A much more efficient way to do things, than just incrementing by one.
      }
      else if(*pointer == 'G' + j)
      {
          *pointer -= j;
      }
      else if(*pointer == 'S' + j)
      {
          *pointer -= j;
      }
      else if(*pointer == 's' + j)
      {
        *pointer -= j;
      }
      pointer++;
      //printf("%c| ", *pointer);
    }
  }
}

void main() {
  int row, column;
  char *pointer;
  printf("Please enter two integers, which must be greater than 3 and less than maxrow and maxcolomn, respectively\n");
  scanf("%d\n%d", &row, &column);
  while ((row <= 3) || (column <= 3) || (row >= maxrow) || (column >= maxcolumn)) {
    printf("both integers must be greater than 3. Row must be less than %d, and column less than %d. Please reenter\n", maxrow, maxcolumn);
    scanf("%d\n%d", &row, &column);
  }
  initialization(row, column);
  randommaze(row, column);
  printmaze(row, column);
  encryptmaze(row, column);
  printmaze(row, column);
  decryptmaze(row, column); 
  printmaze(row, column);
}
