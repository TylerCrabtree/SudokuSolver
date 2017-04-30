//Tyler Crabtree
//Some code provided by Wayne Cochran
//Referenced stack exchange for syntax


// include libraries
#include <string>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <cctype>
#include <stdexcept>
#include <bitset>
#include "SudokuGrid.h"  // for header file



using namespace std;

std:: string puzzle;


//Code section
// XXX


// below are functions that needed to be implemented by the code provided by cochran.
bool  useInRow(SudokuGrid& grid, int row, int col, int n){ // checks to see if number conflicts with row
    
    for (int c = 0; c < 9; c++){
        if( col != c){
            if( grid.number(row,c) == n){
                return true;
            }
        }
    }
    
    return false;
}


bool useInColumn(SudokuGrid& grid, int row, int col,int n){ // checks to see if number conflicts in column
    
    
    for (int r = 0; r < 9; r++){
        if( row != r){
            if( grid.number(r,col) == n){
                return true;
            }
        }
    }
    
    return false;
}


bool useInMini (SudokuGrid& grid, int row, int col,int n){  // checks to see if you can use in the mini boxes
    int goldenRow = (row - (row % 3));  //basically forming little 3 by 3 boxes
    int goldenCol = (col - (col % 3));  //basically forming little 3 by 3 boxes
    
    
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            
            if (row != (r+goldenRow) && col != (c+goldenCol)){
                if(grid.number(r+goldenRow,c +goldenCol)== n){
                    
                    return true;
                }
            }
        }
    }
    return false;
}





bool conflictingNumber(SudokuGrid& grid,int row, int col, int n){   // function that calls three mini functions to see if a number conflicts
    
    
    return(useInColumn(grid,row,col,n) || useInRow(grid,row,col,n) || useInMini(grid,row,col,n) == true);
    
}


bool findUnassignedLocation(SudokuGrid& grid, int& row, int& col) {  // for solve sudoku method,
    
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if(grid.number(row,col) == 0){
                return true;
            }
    return false;
}


///////////Cochran Code /////////////////////

bool solveSudoku(SudokuGrid& grid) {
    int row, col;
    if (!findUnassignedLocation(grid, row, col))
        return true; // puzzle filled, solution found!
    for (int num = 1; num <= 9; num++)
        if (!conflictingNumber(grid, row, col, num)) {
            grid.setNumber(row, col, num); // try next number
            if (solveSudoku(grid))
                return true; // solved!
            grid.setNumber(row, col, 0); // not solved, clear number
        }
    return false; // not solved, back track
}





void autoPencil(SudokuGrid& grid) {
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
            if (grid.number(r,c) == 0) {
                grid.setAllPencils(r,c);
                for (int n = 1; n <= 9; n++)
                    if (conflictingNumber(grid,r,c,n))
                        grid.clearPencil(r,c,n);
            }
}



///////////Cochran Code /////////////////////





int numPencilsInRow(SudokuGrid& grid, int row, int n){  // functions for pencil listed below
    
    int increment = 0;  // create a count for pencils in row
    
    for (int c = 0; c < 9; c++){
        
        if( grid.isPencilSet(row, c, n) == true){
            increment++;
        }
        
    }
    return increment;
}




int numPencilsInColumn(SudokuGrid& grid, int col, int n){ // count pencils in column
    
    int increment = 0;
    
    for (int r = 0; r < 9; r++){
        
        if( grid.isPencilSet(r, col, n)){
            increment++;
        }
    }
    return increment;
}


int numPencilsInBlock(SudokuGrid& grid, int row, int col, int n){  //check mini blocks. 
    
    
    int increment = 0;
    int goldenRow = (row - (row % 3));  // basically finding the smaller grids
    int goldenCol = (col - (col % 3));
    
    
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            if((grid.isPencilSet(r+goldenRow,c +goldenCol, n)) == true){
                increment++;
            }
        }
    }
    return increment;
}




///////////Cochran Code /////////////////////

void deduce(SudokuGrid& grid) {
    bool changed;
    do { // repeat until no changes made
        autoPencil(grid);
        changed = false;
        for (int row = 0; row < 9; row++)
            for (int col = 0; col < 9; col++)
                for (int n = 1; n <= 9; n++)
                    if (grid.isPencilSet(row, col, n) &&
                        (numPencilsInRow(grid, row, n) == 1 ||
                         numPencilsInColumn(grid, col, n) == 1 ||
                         numPencilsInBlock(grid, row, col, n) == 1)) {
                            grid.clearAllPencils(row, col);
                            grid.setNumber(row,col,n);
                            grid.setSolved(row,col);
                            autoPencil(grid);
                            changed = true;
                            break;
                        }
    } while(changed);
}
///////////Cochran Code /////////////////////





void printAndSolve(){  // cleaned up, nice function for solve/printing everything. Would have been fine in main, but clearer this way.
    
    //formGrid(); // this forms a puzzle based off the string itself, no need for array of arrays yet.
    SudokuGrid grid(puzzle);
    
    
    grid.gridPrint();
    
    autoPencil(grid);
    deduce(grid);
    cout << "\n";
    grid.gridPrint();
    cout << "\n";
    
    solveSudoku(grid);
    grid.gridPrint();
    
    
    // number(8,0);     // check to see if these functions work
    //setNumber(0, 0,9);
    // isFixed(1,8);
    
}



int main(int argc, char *argv[]) {
    
    
    //string puzzle;
    //cin >> puzzle;
    puzzle = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    
    if (puzzle.length() != 9*9 ||
        !all_of(puzzle.begin(), puzzle.end(), [](char ch) {
        return ch == '.' || ('1' <= ch && ch <= '9');
    })) {
        cerr << "bogus puzzle!" << endl;
        exit(1);
    }
    
    
    printAndSolve();
    
    
    // XXX
    
    return 0;
}




// Code not current used, but helpful for testing & development.
/*
 int numberOffPuzzle(int row, int col){   // so i originally did the output this isn't needed
 int rowCheck = col;
 
 //char c;
 
 
 for(unsigned int i = 0; i<= puzzle.length(); i++) {
 //  char c = puzzle[i]; //this is your character
 
 }
 
 
 for(unsigned int j = 0; j <= puzzle.length(); j++) {
 
 if ( (row == 0) && (col == 0) ){
 c = puzzle[j];
 break;
 }
 if(j == 0){
 j = j + row*9;
 }
 
 if  (rowCheck == 0){
 c = puzzle[j];
 
 break;
 }
 rowCheck--;
 }
 
 printf("\nnumber = ");
 std:: cout << c ;
 std:: cout << "\n";
 
 
 return 0;
 
 }
 
 
 
 
 
 void setNumber(int row, int col, int number) {
 
 int goldenNum = col + row*(9);
 puzzle[goldenNum] = number;
 
 if (number == 9){
 std::replace(puzzle.begin(), puzzle.end(), '\t', '9');
 }
 if (number == 8){
 std::replace(puzzle.begin(), puzzle.end(), '\t', '8');
 }
 if (number ==  7){
 std::replace(puzzle.begin(), puzzle.end(), '\t', '7');
 }
 if (number ==  6){
 std::replace(puzzle.begin(), puzzle.end(), '\t', '6');
 }
 if (number ==  5){
 std::replace(puzzle.begin(), puzzle.end(), '\t', '5');
 }
 if (number ==  4){
 std::replace(puzzle.begin(), puzzle.end(), '\t', '4');
 }
 if (number ==  3){
 std::replace(puzzle.begin(), puzzle.end(), '\t', '3');
 }
 if (number ==  2){
 std::replace(puzzle.begin(), puzzle.end(), '\t', '2');
 }
 if (number ==  1){
 std::replace(puzzle.begin(), puzzle.end(), '\t', '1');
 }
 if (number ==  0){
 std::replace(puzzle.begin(), puzzle.end(), '\t', '.');
 }
 
 SudokuGrid grid(puzzle); // update array
 
 }
 
 
 
 bool isFixedOffPuzzle(int row, int col)  {
 int goldenNum = col + row*(9);
 
 // for(unsigned int i = 0; i<= goldenNum; i++) {
 char c = puzzle[goldenNum]; //this is your character
 
 if (c == '.'){
 // cout << "false";
 return false;
 }
 if (c != '.'){
 //  cout << "true";
 return true;
 }
 //   }
 
 return false;
 }
 
 
 // end un-used code
 */
