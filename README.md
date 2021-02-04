# sudokuSolverC

The file `board.txt` should contain only one sudoku board  
The board has to be entered element by element line by line (Each element separated by a space)  
  
Once the board is entered, the executable file can be run and the output will be displayed in the terminal  
`easy.txt`, `medium.txt`, `hard.txt`, and `expert.txt` contain some sudoku boards copied from [sudoku](sudoku.com)  

#Working -  
The board is stored in a 2 dimensional array called `board[9][9]`  
  
`0  0  0  :  1  1  1  :  2  2  2`   
`0  0  0  :  1  1  1  :  2  2  2`  
`0  0  0  :  1  1  1  :  2  2  2`  
`. . . . . . . . . . .   `  
`3  3  3  :  4  4  4  :  5  5  5`  
`3  3  3  :  4  4  4  :  5  5  5`  
`3  3  3  :  4  4  4  :  5  5  5`  
`. . . . . . . . . . .   `  
`6  6  6  :  7  7  7  :  8  8  8`  
`6  6  6  :  7  7  7  :  8  8  8`  
`6  6  6  :  7  7  7  :  8  8  8`  
  
An array called `locations[9][3][9]`
	This array stores whether or not a number can be filled in a certain element or not  
	If `locations[n][0][i] == 0`, then, the row `i` does not have the number `n` in it  
	Similarly locations[n][1][j] for column `j`  
	And `locations[n][2][k]` for square `k`  
  
Once `locations[9][3][9]` is set,
There are multiple functions, `solveEasy`, `solveMed`, `solveHard`, and `solveExpert`  
1) solveEasy -  
	This function traverses through all empty elements in the board   
	If the locations[9][3][9] array shows that a number is uniquely absent in  
	the corresponding row, column, and square of the empty element,  
	the number is filled into the element  
	  
	This is a complete brute force method and can only solve easy level boards  
	  
2) solveMed -  
	This function traverses through the empty elements in the board  
	The board is divided into 3 trios of columns and 3 trios of rows  
	If a number is filled in the other two rows/columns/squares of the trio,  
	then the number is filled into the empty element as it is the only available option  
  
3) solveHard -  
	This function traverses through the empty elements in the board  
	For all possible numbers that can be filled in the empty element,  
	If that number can only be filled in that element,  
		(because it cannot be filled in any of the empty elements in the  
		corresponding row, column and square)  
	then the number will be filled in that element  

4) solveExpert -  
	This function traverses through the empty elements in the board  
	For all elements which only have two possibilities which can be filled in them  
	It tries both and returns whichever solves the board  
	  
	In some cases, guessing only one element is not enough  
	In these extreme cases, two sets of two possibility elements are guessed
