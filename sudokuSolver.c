#include <stdio.h>
#include <stdbool.h>

//Declaring global variables
int board[9][9];
//board[rows][columns]
int locations[9][3][9];
bool extreme = false;

//Function prototypes
int square(int, int);
int checkSolve();
void locationsInit();
void boardInit();
void printBoard();
void setLocations();
void update(int, int, int);
void solveEasy();
void solveMed();
void solveHard();
void solveExpert();
void solveBoard();

//Main function
int main()
{

    //Setting sudoku board to solve
    boardInit();

    //Setting locations
    locationsInit();
    setLocations();

    //Printing sudoku board to solve
    printBoard();

    printf("\n\nEnter any key to solve the board:\n");
    getchar();

    //Solving sudoku board
    int previousCheck = 0;
    for (;;)
    {
        solveBoard();
        if (!checkSolve())
        {
            break;
        }
        else if (checkSolve() == previousCheck)
        {
            solveExpert();
            if (checkSolve() == previousCheck)
            {
                printf("The board entered is unsolvable or has multiple solutions.");
                fflush(stdin);
                printf("\n\nEnter any key to quit:\n");
                getchar();
                return 0;
            }
        }
        previousCheck = checkSolve();
    }

    //printing solved sudoku board
    printBoard();

    fflush(stdin);
    printf("\n\nEnter any key to quit:\n");
    getchar();
    return 0;
}

//Function declarations

//Returns the number of square of coordinate (i,j)
/*
The square numbers are:- 
0  0  0  :  1  1  1  :  2  2  2  
0  0  0  :  1  1  1  :  2  2  2  
0  0  0  :  1  1  1  :  2  2  2  
.. .. .. .. .. .. .. .. .. .. .. 
3  3  3  :  4  4  4  :  5  5  5  
3  3  3  :  4  4  4  :  5  5  5  
3  3  3  :  4  4  4  :  5  5  5  
.. .. .. .. .. .. .. .. .. .. .. 
6  6  6  :  7  7  7  :  8  8  8  
6  6  6  :  7  7  7  :  8  8  8  
6  6  6  :  7  7  7  :  8  8  8 
*/
int square(int rowNum, int colNum)
{
    return ((rowNum / 3) * 3 + (colNum / 3));
}

//Function to return the number of zero's still left to fill in the board
int checkSolve()
{
    int count = 0;
    for (int rowNum = 0; rowNum < 9; rowNum++)
    {
        for (int colNum = 0; colNum < 9; colNum++)
        {
            if (!board[rowNum][colNum])
            {
                count++;
            }
        }
    }
    return count;
}

//Initializes the array locations[9][3][9] to all values of 0
void locationsInit()
{
    for (int number = 1; number <= 9; number++)
    {
        for (int rowNum = 0; rowNum < 9; rowNum++)
        {
            for (int colNum = 0; colNum < 9; colNum++)
            {
                //Set rows to 0
                locations[number - 1][0][rowNum] = 0;

                //Set cols to 0
                locations[number - 1][1][colNum] = 0;

                //set squares to 0
                locations[number - 1][2][square(rowNum, colNum)] = 0;
            }
        }
    }
}

//Reads board.txt file to input single sudoku board
void boardInit()
{
    FILE *ptr;
    ptr = fopen("board.txt", "r");
    for (int rowNum = 0; rowNum < 9; rowNum++)
    {
        for (int colNum = 0; colNum < 9; colNum++)
        {
            fscanf(ptr, "%d", &board[rowNum][colNum]);
        }
    }
}

//Prints board[9][9] in sudoku board form
void printBoard()
{
    for (int rowNum = 0; rowNum < 9; rowNum++)
    {
        printf("\n");
        if (rowNum == 3 || rowNum == 6)
        {
            for (int k = 0; k < 11; k++)
            {
                printf(".. ");
            }
            printf("\n");
        }
        for (int colNum = 0; colNum < 9; colNum++)
        {
            if (colNum == 3 || colNum == 6)
            {
                printf(":  ");
            }
            printf("%d  ", board[rowNum][colNum]);
        }
    }
}
/*
Make a 2-D array with 3 1-D arrays for each number
The 3 1-D arrays store 0 or 1 for whether the row, column or square contain the number
Now take the intersection of these 3 arrays, if it is found that a number is in none, then fill it
Sets the value of locations[9][3][9]
If locations[i - 1][0][k] == 1 means that the number i is in the row k
Similarly locations[i-1][1][k] == 1 means that the number i is in the column k
And locations[i-1][2][k] == 1 means that the number i is in the square k
*/
void setLocations()
{
    for (int number = 1; number <= 9; number++)
    {
        for (int rowNum = 0; rowNum < 9; rowNum++)
        {
            for (int colNum = 0; colNum < 9; colNum++)
            {
                //Check rows for all numbers
                locations[number - 1][0][rowNum] += (board[rowNum][colNum] == number);

                //Check columns for all numbers
                locations[number - 1][1][colNum] += (board[rowNum][colNum] == number);

                //Check square for all numbers
                locations[number - 1][2][square(rowNum, colNum)] += (board[rowNum][colNum] == number);
            }
        }
    }
}

//This takes the coordinates of the element to fill and the number to fill in it
//And updates its value in board[][] and locations[][][]
void update(int rowNum, int colNum, int numToFill)
{
    board[rowNum][colNum] = numToFill;
    locations[numToFill - 1][0][rowNum] = 1;
    locations[numToFill - 1][1][colNum] = 1;
    locations[numToFill - 1][2][square(rowNum, colNum)] = 1;
}

void solveEasy()
{
    for (int rowNum = 0; rowNum < 9; rowNum++)
    {
        for (int colNum = 0; colNum < 9; colNum++)
        {
            if (!board[rowNum][colNum])
            {
                int canFillNums[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
                for (int number = 1; number <= 9; number++)
                {
                    if (locations[number - 1][0][rowNum] == locations[number - 1][1][colNum] &&
                        locations[number - 1][2][square(rowNum, colNum)] == locations[number - 1][1][colNum] &&
                        locations[number - 1][0][rowNum] == 0)
                    {
                        canFillNums[number - 1] = 1;
                    }
                }
                int count = 0, tempNumToFill = 0;
                for (int number = 1; number <= 9; number++)
                {
                    if (canFillNums[number - 1] == 1)
                    {
                        count++;
                        tempNumToFill = number;
                    }
                }
                if (count == 1)
                {
                    update(rowNum, colNum, tempNumToFill);
                }
            }
        }
    }
}

void solveMed()
{
    for (int number = 1; number <= 9; number++)
    {
        for (int l = 0; l < 9; l++)
        {
            if (locations[number - 1][2][l] == 0)
            {

                int rowFactor = (l / 3) * 3;
                int colFactor = (l % 3) * 3;
                int row[3] = {rowFactor, rowFactor + 1, rowFactor + 2};
                int col[3] = {colFactor, colFactor + 1, colFactor + 2};

                for (int i = 0; i < 3; i++)
                {
                    //Row square check
                    if (locations[number - 1][2][(l / 3) * 3 + i])
                    {
                        for (int rowNum = 0; rowNum < 3; rowNum++)
                        {
                            for (int colNum = 0; colNum < 3; colNum++)
                            {
                                if (board[rowNum + rowFactor][colNum + i * 3] == number)
                                {
                                    row[rowNum] = -1;
                                }
                            }
                        }
                    }

                    //Col square check
                    if (locations[number - 1][2][l % 3 + i * 3])
                    {
                        for (int rowNum = 0; rowNum < 3; rowNum++)
                        {
                            for (int colNum = 0; colNum < 3; colNum++)
                            {
                                if (board[rowNum + i * 3][colNum + colFactor] == number)
                                {
                                    col[colNum] = -1;
                                }
                            }
                        }
                    }
                }

                int count = 0;
                int coordinate[2];
                for (int rowNum = 0; rowNum < 3; rowNum++)
                {
                    if (row[rowNum] != -1)
                    {
                        for (int colNum = 0; colNum < 3; colNum++)
                        {
                            if (col[colNum] != -1)
                            {
                                if (!board[row[rowNum]][col[colNum]])
                                {
                                    count++;
                                    coordinate[0] = row[rowNum];
                                    coordinate[1] = col[colNum];
                                }
                            }
                        }
                    }
                }
                if (count == 1)
                {
                    update(coordinate[0], coordinate[1], number);
                }
            }
        }
    }
}

void solveHard()
{
    for (int rowNum = 0; rowNum < 9; rowNum++)
    {
        for (int colNum = 0; colNum < 9; colNum++)
        {
            if (!board[rowNum][colNum])
            {
                for (int number = 1; number <= 9; number++)
                {
                    if (locations[number - 1][0][rowNum] == locations[number - 1][1][colNum] &&
                        locations[number - 1][2][square(rowNum, colNum)] == locations[number - 1][1][colNum] &&
                        locations[number - 1][0][rowNum] == 0)
                    {
                        //This number is a possibility in element (rowNum, colNum)
                        bool flagCol = false;
                        for (int colNum2 = 0; colNum2 < 9; colNum2++)
                        {
                            if (!board[rowNum][colNum2] && colNum2 != colNum)
                            {
                                if (locations[number - 1][0][rowNum] == locations[number - 1][1][colNum2] &&
                                    locations[number - 1][2][square(rowNum, colNum2)] == locations[number - 1][1][colNum2] &&
                                    locations[number - 1][0][rowNum] == 0)
                                {
                                    flagCol = true;
                                    break;
                                }
                            }
                        }
                        if (flagCol)
                        {
                            continue;
                        }
                        else
                        {
                            update(rowNum, colNum, number);
                        }
                    }
                }
            }
        }
    }

    for (int colNum = 0; colNum < 9; colNum++)
    {
        for (int rowNum = 0; rowNum < 9; rowNum++)
        {
            if (!board[rowNum][colNum])
            {
                for (int number = 1; number <= 9; number++)
                {

                    if (!locations[number - 1][0][rowNum] &&
                        !locations[number - 1][1][colNum] &&
                        !locations[number - 1][2][square(rowNum, colNum)])
                    {

                        bool flagRow = false;
                        for (int rowNum2 = 0; rowNum2 < 9; rowNum2++)
                        {
                            if (!board[rowNum2][colNum] && rowNum2 != rowNum)
                            {
                                if (!locations[number - 1][0][rowNum2] &&
                                    !locations[number - 1][1][colNum] &&
                                    !locations[number - 1][2][square(rowNum2, colNum)])
                                {
                                    flagRow = true;
                                    break;
                                }
                            }
                        }
                        if (flagRow)
                        {
                            continue;
                        }
                        else
                        {
                            update(rowNum, colNum, number);
                        }
                    }
                }
            }
        }
    }
}

void solveExpert()
{
    int possibilities[9][9][9] = {0};
    //possibilities[9][9][9] is an array that stores whether a number can be filled in an element
    //possibilities[i][j][k-1] means that the number k can be filled in the coordinates (i,j)

    int possibleFill[81] = {9999};
    //possibleFill[i] is an array of 4 digit number whose thousands digit is rowNum
    //hundreds digit is colNum, tens digit is minNumber, and units digit is minCount
    int iterator = 0;

    //Board1 stores a copy of board so that changes made to board
    //that do not result in solution of the sudoku board can be reverted

    int board1[9][9];
    for (int rowNum = 0; rowNum < 9; rowNum++)
    {
        for (int colNum = 0; colNum < 9; colNum++)
        {
            board1[rowNum][colNum] = board[rowNum][colNum];
        }
    }

    //Set all possibilities
    for (int rowNum = 0; rowNum < 9; rowNum++)
    {
        for (int colNum = 0; colNum < 9; colNum++)
        {
            if (!board[rowNum][colNum])
            {
                for (int number = 1; number <= 9; number++)
                {
                    if (!locations[number - 1][0][rowNum] &&
                        !locations[number - 1][1][colNum] &&
                        !locations[number - 1][2][square(rowNum, colNum)])
                    {
                        possibilities[rowNum][colNum][number - 1] = 1;
                    }
                }
            }
        }
    }

    int twoPossibilities[9][9][2];
    // twoPossibilities[9][9][2] stores which coordinates only have 2 possible numbers that can be filled in them
    // twoPossibilities[i][j][0] gives the first possibility that can be stored in (i,j) and twoPossibilities[i][j][1] returns the other

    //Initialize twoPossibilities
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                twoPossibilities[i][j][k] = 0;
            }
        }
    }

    //Count possibilities and if count == 2 store it in twoPossibilities
    //Set twopossibilities
    for (int rowNum = 0; rowNum < 9; rowNum++)
    {
        for (int colNum = 0; colNum < 9; colNum++)
        {
            if (!board[rowNum][colNum])
            {
                int count = 0;
                for (int number = 1; number <= 9; number++)
                {
                    if (possibilities[rowNum][colNum][number - 1])
                    {
                        if (count == 2)
                        {
                            twoPossibilities[rowNum][colNum][0] = 0;
                            twoPossibilities[rowNum][colNum][1] = 0;
                            break;
                        }
                        twoPossibilities[rowNum][colNum][count] = number;
                        count++;
                    }
                }
            }
        }
    }

    /*
        Now we have possibilities at (i,j) stored in possibilities[i][j][k]
        All elements with only two possibilities stored in twoPossiblities[i][j]
        Now the number of times a possibility appears in that respective row and column is stored in countP1 and countP2
        The minimum of these will be stored in possibleFill[i] as rowNum*1000 + colNum*100 + minValue*10 + min
        where min is the minimum of countP1 and countP2 and minValue is the respective number to be filled
    */
    for (int rowNum = 0; rowNum < 9; rowNum++)
    {
        for (int colNum = 0; colNum < 9; colNum++)
        {
            if (!board[rowNum][colNum])
            {
                int countP1 = 0;
                int countP2 = 0;
                for (int rowNum2 = 0; rowNum2 < 9; rowNum2++)
                {
                    if (twoPossibilities[rowNum][colNum][0] && rowNum2 != rowNum)
                    {
                        if (possibilities[rowNum2][colNum][twoPossibilities[rowNum][colNum][0] - 1])
                        {
                            countP1++;
                        }
                        if (possibilities[rowNum2][colNum][twoPossibilities[rowNum][colNum][1] - 1])
                        {
                            countP2++;
                        }
                    }
                }
                for (int colNum2; colNum2 < 9; colNum2++)
                {

                    if (twoPossibilities[rowNum][colNum][0] && colNum2 != colNum)
                    {
                        if (possibilities[rowNum][colNum2][twoPossibilities[rowNum][colNum][0] - 1])
                        {
                            countP1++;
                        }
                        if (possibilities[rowNum][colNum2][twoPossibilities[rowNum][colNum][1] - 1])
                        {
                            countP2++;
                        }
                    }
                }

                if (countP1 > countP2)
                {
                    possibleFill[iterator] = rowNum * 1000;
                    possibleFill[iterator] += colNum * 100;
                    possibleFill[iterator] += twoPossibilities[rowNum][colNum][1] * 10;
                    possibleFill[iterator] += countP2;
                    iterator++;
                }
                else if (countP1 < countP2)
                {
                    possibleFill[iterator] = rowNum * 1000;
                    possibleFill[iterator] += colNum * 100;
                    possibleFill[iterator] += twoPossibilities[rowNum][colNum][0] * 10;
                    possibleFill[iterator] += countP1;
                    iterator++;
                }
            }
        }
    }

    /*
        Array possibleFill[81] is sorted by ascending order of min using insertion sort
        Here min is the minimum number of times the possibility checked appears in that row and column
        Now the possibility with least min will be filled into board and we will use solveBoard()
        If the sudoku board remains unsolved after this, then it will reset board back to the state it was in 
        using board1 and then try the next item in possibleFill[81]
        If all values of possibleFill are checked and none can solve the sudoku board, then a boolean value extreme is set to true
        If extreme == true, then instead of trying one possibility from possibleFill[81] we try 2 possiblities simultaneously
    */

    //    Insertion sort for array possibleFill
    for (int i = 1; i < iterator; i++)
    {
        for (int j = i; j >= 0; j--)
        {
            if (possibleFill[j + 1] % 10 < possibleFill[j] % 10)
            {
                int temp = possibleFill[j];
                possibleFill[j] = possibleFill[j + 1];
                possibleFill[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < iterator; i++)
    {
        update(possibleFill[i] / 1000, (possibleFill[i] % 1000) / 100, (possibleFill[i] % 100) / 10);
        solveBoard();
        if (checkSolve())
        {
            if (i == iterator - 1)
            {
                extreme = true;
            }
            for (int rowNum = 0; rowNum < 9; rowNum++)
            {
                for (int colNum = 0; colNum < 9; colNum++)
                {
                    board[rowNum][colNum] = board1[rowNum][colNum];
                }
            }
            locationsInit();
            setLocations();
        }
        else
        {
            return;
        }
    }
    if (extreme)
    {
        for (int i = 0; i < iterator; i++)
        {
            int iterator2 = 0;
            update(possibleFill[i] / 1000, (possibleFill[i] % 1000) / 100, (possibleFill[i] % 100) / 10);
            solveBoard();
            //Update newTwoPossibilities array according to new board after filling possibleFill[i]

            int newPossibilities[9][9][9] = {0};
            //Set all newPossibilities
            for (int rowNum = 0; rowNum < 9; rowNum++)
            {
                for (int colNum = 0; colNum < 9; colNum++)
                {
                    if (!board[rowNum][colNum])
                    {
                        for (int number = 1; number <= 9; number++)
                        {
                            if (!locations[number - 1][0][rowNum] &&
                                !locations[number - 1][1][colNum] &&
                                !locations[number - 1][2][square(rowNum, colNum)])
                            {
                                newPossibilities[rowNum][colNum][number - 1] = 1;
                            }
                        }
                    }
                }
            }

            int newPossibleFill[81] = {0};
            //initialize newPossibleFill[81]
            // for (int l = 0; l < 81; l++)
            // {
            //     newPossibleFill[l] = 9999;
            // }
            int newTwoPossibilities[9][9][2] = {0};
            // newTwoPossibilities[9][9][2] stores which coordinates only have 2 possible numbers that can be filled in them
            // newTwoPossibilities[i][j][0] gives the first possibility that can be stored in (i,j) and newTwoPossibilities[i][j][1] returns the other

            //Count newPossibilities and if count == 2 store it in newTwoPossibilities
            //Set newTwoPossibilities
            for (int rowNum = 0; rowNum < 9; rowNum++)
            {
                for (int colNum = 0; colNum < 9; colNum++)
                {
                    if (!board[rowNum][colNum])
                    {
                        int count = 0;
                        for (int number = 1; number <= 9; number++)
                        {
                            if (newPossibilities[rowNum][colNum][number - 1])
                            {
                                if (count == 2)
                                {
                                    newTwoPossibilities[rowNum][colNum][0] = 0;
                                    newTwoPossibilities[rowNum][colNum][1] = 0;
                                    break;
                                }
                                newTwoPossibilities[rowNum][colNum][count] = number;
                                count++;
                            }
                        }
                    }
                }
            }

            /*
                Now we have newPossibilities at (i,j) stored in newPossibilities[i][j][k]
                All elements with only two newPossibilities stored in twoPossiblities[i][j]
                Now the number of times a possibility appears in that respective row and column is stored in countP1 and countP2
                The minimum of these will be stored in newPossibleFill[i] as rowNum*1000 + colNum*100 + minValue*10 + min
                where min is the minimum of countP1 and countP2 and minValue is the respective number to be filled
            */
            for (int rowNum = 0; rowNum < 9; rowNum++)
            {
                for (int colNum = 0; colNum < 9; colNum++)
                {
                    if (!board[rowNum][colNum])
                    {
                        int countP1 = 0;
                        int countP2 = 0;
                        for (int rowNum2 = 0; rowNum2 < 9; rowNum2++)
                        {
                            if (newTwoPossibilities[rowNum][colNum][0] && rowNum2 != rowNum)
                            {
                                if (newPossibilities[rowNum2][colNum][newTwoPossibilities[rowNum][colNum][0] - 1])
                                {
                                    countP1++;
                                }
                                if (newPossibilities[rowNum2][colNum][newTwoPossibilities[rowNum][colNum][1] - 1])
                                {
                                    countP2++;
                                }
                            }
                        }
                        for (int colNum2; colNum2 < 9; colNum2++)
                        {

                            if (newTwoPossibilities[rowNum][colNum][0] && colNum2 != colNum)
                            {
                                if (newPossibilities[rowNum][colNum2][newTwoPossibilities[rowNum][colNum][0] - 1])
                                {
                                    countP1++;
                                }
                                if (newPossibilities[rowNum][colNum2][newTwoPossibilities[rowNum][colNum][1] - 1])
                                {
                                    countP2++;
                                }
                            }
                        }

                        if (countP1 > countP2)
                        {
                            newPossibleFill[iterator2] = rowNum * 1000;
                            newPossibleFill[iterator2] += colNum * 100;
                            newPossibleFill[iterator2] += newTwoPossibilities[rowNum][colNum][1] * 10;
                            newPossibleFill[iterator2] += countP2;
                            iterator2++;
                        }
                        else if (countP1 < countP2)
                        {
                            newPossibleFill[iterator2] = rowNum * 1000;
                            newPossibleFill[iterator2] += colNum * 100;
                            newPossibleFill[iterator2] += newTwoPossibilities[rowNum][colNum][0] * 10;
                            newPossibleFill[iterator2] += countP1;
                            iterator2++;
                        }
                    }
                }
            }

            /*
                Array newPossibleFill[81] is sorted by ascending order of min using insertion sort
                Here min is the minimum number of times the possibility checked appears in that row and column
                Now the possibility with least min will be filled into board and we will use solveBoard()
                If the sudoku board remains unsolved after this, then it will reset board back to the state it was in 
                using board1 and then try the next item in newPossibleFill[81]
                If all values of newPossibleFill are checked and none can solve the sudoku board, then a boolean value extreme is set to true
                If extreme == true, then instead of trying one possibility from newPossibleFill[81] we try 2 possiblities simultaneously
            */

            //    Insertion sort for array newPossibleFill
            for (int l = 1; l < iterator2; l++)
            {
                for (int j = l; j >= 0; j--)
                {
                    if (newPossibleFill[j + 1] % 10 < newPossibleFill[j] % 10)
                    {
                        int temp = newPossibleFill[j];
                        newPossibleFill[j] = newPossibleFill[j + 1];
                        newPossibleFill[j + 1] = temp;
                    }
                }
            }

            for (int j = 0; j < iterator2; j++)
            {
                update(newPossibleFill[j] / 1000, (newPossibleFill[j] % 1000) / 100, (newPossibleFill[j] % 100) / 10);
                solveBoard();
                if (checkSolve())
                {
                    for (int rowNum = 0; rowNum < 9; rowNum++)
                    {
                        for (int colNum = 0; colNum < 9; colNum++)
                        {
                            if ((possibleFill[i]) / 1000 == rowNum && (possibleFill[i] % 1000) / 100 == colNum)
                            {
                                board[rowNum][colNum] = (possibleFill[i] % 100) / 10;
                            }
                            else
                            {
                                board[rowNum][colNum] = board1[rowNum][colNum];
                            }
                        }
                    }
                    locationsInit();
                    setLocations();
                }
                else
                {
                    return;
                }
            }
        }
    }
}

//If the sudoku board can be solved using solveEasy() and solveMed(), then those will be used
//As soon as the same array goes through the loop twice, checkSolve() becomes equal to previousCheck
//Then solveHard() is used with the same condition
void solveBoard()
{
    int previousCheck = 0;
    for (;;)
    {
        if ((!checkSolve()) || (checkSolve() == previousCheck))
        {
            int previousCheckHard = previousCheck;
            solveHard();
            if (previousCheckHard == checkSolve())
            {
                break;
            }
        }
        previousCheck = checkSolve();
        solveEasy();
        solveMed();
    }
}