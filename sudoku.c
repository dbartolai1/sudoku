#include "sudoku.h"


/*
DRAKE BARTOLAI - MP7
To implement the sudoku solver, I used a recursive backtracking method. The function "solve_sudoku" will run through each cell
looking for one with no value assigned (equal to 0). Once it finds a cell, it will try each possible value, 1-9, to try to find a solution.
It will first check if the value is valid based on the rules of the game. The value cannot be found elsewhere in the row, column, or
zone of the grid. The program does this with the is_value_valid function, which calls three sub-functions to test for the row, column,
and zone separately. If the value is valid, then the program assumes that is the correct answer. solve_sudoku will then call itself, and if
that value will allow for a solution to be found, it will keep going. Otherwise, the cell will be reset to 0 and the next value will be
tested in that cell. The process continues until a solution is found.
*/
// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

assert(i>=0 && i<9);
for (int k = 0; k <= 8; k++){
	if (sudoku[i][k] == val){return 1;} //iterate through the row to check if value already occured and return 1 if it does
}
  return 0; //return 0 if value is not found in the row
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

assert(j>=0 && j<9);
for (int k = 0; k <= 8; k++){
	if (sudoku[k][j] == val){return 1;} //iterate through the column to check if value already occured and return 1 if it does
}
  return 0; //return 0 if value is not found in the row
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

assert(i>=0 && i<9);
for (int m = 0; m <= 2; m++){ //use m as arbitrary loop variable
if (i%3 == m){ //using modulus 3 gives us the position of the row relative to the zone boundaries
	for (int n = 0; n <= 2; n++){ //use n as arbitrary loop variable
		if (j%3 == n){ //using modulus 3 gives us the position of the column relative to the zone boundaries
			for (int a = i-m; a <= i-m+2; a++){ //use the modulus value to locate the cell relative to the zone
			for (int b = j-n; b <= j-n+2; b++){ //and loop through the rows and columns necessary
			if (a>=0 && a<=9 && b>=0 && b<=9 && sudoku[a][b] == val){return 1;} //if the coordinates are on the board and the value is in the zome already, return 1
			}}}}}}
  return 0; //if the value doesn't occur in the zone, return 0
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

assert(i>=0 && i<9 && j>=0 && j<9);
if (is_val_in_row(val, i, sudoku) == 0 && is_val_in_col(val, j, sudoku) == 0 && is_val_in_3x3_zone(val, i, j, sudoku) == 0)
  {return 1;} //if all of the functions above return 0, the value being tested at the cell is valid and the function returns 1
return 0; //otherwise, return 0
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

for (int i = 0; i <= 8; i++){ //use i to loop through rows
	for (int j = 0; j <= 8; j++){ //use j to loop through columns
		if (sudoku[i][j] == 0){ //check if value at coordinates is 0
			for (int val = 1; val <= 9; val++){ //if it is 0, check through each possible value
				if (is_val_valid(val, i, j, sudoku)==1){ //if the value is valid, test using recursive backtracking
					sudoku[i][j] = val; //set the cell equal to the value
					if (solve_sudoku(sudoku)==1){return 1;} //implement recursive backtracking by having the function call itself. if it leads to a solution, return 1
					sudoku[i][j] = 0;}} //if the value doesn't work, set the cell to 0 and try again
				return 0;}}} //if we get stuck in a loop with no solution, return 0

  return 1; //if every cell is filled, return 1
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





