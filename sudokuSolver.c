#include <stdio.h>
#include <stdbool.h>

//Declaring global variables
int board[9][9];
//board[rows][columns]
int locations[9][3][9];

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

    printf("\n");

    //Solving sudoku board
    solveBoard();

    //printing solved sudoku board
    printBoard();

    fflush(stdin);
    printf("\nEnter any key to quit:\n");
    getchar();
    return 0;
}

//Function declarations

int square(int rowNum, int colNum)
{
    return ((rowNum / 3) * 3 + (colNum / 3));
}

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

//Make a 2-D array with 3 1-D arrays for each number
//The 3 1-D arrays store 0 or 1 for whether the row, column or square contain the number
//Now take the intersection of these 3 arrays, if it is found that a number is in none, then fill it

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

void update(int rowNum, int colNum, int numToFill)
{
    board[rowNum][colNum] = numToFill;
    locations[numToFill - 1][0][rowNum] = 1;
    locations[numToFill - 1][1][colNum] = 1;
    locations[numToFill - 1][2][square(rowNum, colNum)] = 1;
}

void solveEasy()
{
    //Now we have an array locations[9][3][9]
    //If locations[k][0][i] == locations[k][1][j] == locations[k][2][l] == 0
    //Means that the number k is not in location (i,j) coordinate and l'th square

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
    //rowNum = 5
    //colNum = 0
    // number = 1
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

void solveBoard()
{
    int previousCheck = 0;
    int loopCount = 0;
    for (;;)
    {
        if ((!checkSolve()) || (checkSolve() == previousCheck))
        {
            int var = previousCheck;
            solveHard();
            if (var == checkSolve())
            {
                break;
            }
        }
        previousCheck = checkSolve();
        solveEasy();
        solveMed();
        loopCount++;
    }
    printf("%d\n", loopCount);
}