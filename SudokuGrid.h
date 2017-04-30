//Tyler Crabtree



#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

//I referenced stack exchange for syntax for a struct and using a bitset.
class SudokuGrid
{
private:
    struct Cell{
        char num;  // i was origanlly changing chars instead of value
        int val;
        std:: bitset<9> pencil;
        bool isSolved; // = false;
        bool isFixed; // = false;
        
    };
    std:: array <std:: array < Cell, 9>, 9 > grid;
    
public:// implement the following
    
    SudokuGrid(std::string s){
        int stringCounter = 0;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++){
                char c = s[stringCounter++];
                if (c == '.'){
                    grid[i][j].val = 0;
                    
                } else{
                    grid[i][j].val = atoi(&c);     //Cell value.
                    grid[i][j].isFixed = true;    //Cell value.
                    grid[i][j].isSolved = true;    //Cell Value
                    
                }
            }
        
        
    }
    
    
    
    // Functions implemented, layed out in the assingment.
    
    
    int number(int row, int col) const  {
        
        return grid[row][col].val;
    }
    
    void setNumber(int row, int col, int number) {
        
        grid[row][col].val = number;
        
    }
    bool isFixed(int row, int col)  {
        
        return grid[row][col].isFixed;
    }
    
    bool isSolved(int row, int col)  {return
        grid[row][col].isSolved;
    }
    void setSolved(int row, int col) {
        
        grid[row][col].isSolved = true;
        
    }
    
    bool isPencilSet(int row, int col, int n)  {
        
        return grid[row][col].pencil.test(n-1);
    }
    
    
    bool anyPencilsSet(int row, int col)  {
        
        return grid[row][col].pencil.any();
    }
    
    
    void setPencil(int row, int col, int n) {
        grid[row][col].pencil.set(n-1); //
        
    }
    
    void setAllPencils(int row, int col) {
        grid[row][col].pencil.set(); //
        
    }
    
    
    void clearPencil(int row, int col, int n) {
        grid[row][col].pencil.reset(n-1); // for 0 -8
    }
    
    void clearAllPencils(int row, int col) {
        grid[row][col].pencil.reset();  // reset sets all bits
    }
    
    
    // end functions we needed to implement
    
    void gridPrint(){  // tried to mimic my code for printing off a puzzle
        
        int row =0;
        int col = 0;
        //  int check = 0;
        for ( row = 0; row < 9; row++){
            for ( col = 0; col < 9; col++){
                
                
                std:: cout << grid[row][col].val;
                std:: cout << " ";
                
                
                if((col == 2) || (col == 5)){
                    std::  cout << "|";
                    std::  cout << " ";
                    
                    
                }
            }
       
            std::cout<< "\n";
            if ((row == 2) || (row == 5)){
                std::cout << "------+-------+------" ;
                std::cout << "\n" ; // makes it easy to read that there is a new line after the formatting

            }
         
        }
    }
    
};




#endif // SUDOKUGRID_H