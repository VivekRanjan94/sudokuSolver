# sudokuSolverC

The file `board.txt` should contain only one sudoku board  
The board has to be entered element by element line by line (Each element separated by a space)  
  
Once the board is entered, the executable file can be run and the output will be displayed in the terminal  
`easy.txt`, `medium.txt`, `hard.txt`, and `expert.txt` contain some sudoku boards copied from [sudoku](sudoku.com)  

#Working -  
The board is stored in a 2 dimensional array called `board[9][9]`  

There are multiple functions, solveEasy, solveMed, solveHard, and solveExpert  
1) solveEasy -  
	This function traverses through the array and finds all empty elements
