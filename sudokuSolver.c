#include <stdio.h>

//Declaring global variables
int board[9][9];
int locations[9][3][9];
int possibility[9][3][9];
//board[rows][columns]

//Function prototypes
int square(int rowNum, int colNum);
int checkSolve();
void locationsInit();
void boardInit();
void printBoard();
void setLocations();
void solveEasy();
void solveMed();
void solveHard();

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
    int previousCheck = 0;
    for (;;)
    {
        if ((!checkSolve()) || (checkSolve() == previousCheck))
        {
            break;
        }
        previousCheck = checkSolve();
        solveEasy();
        solveMed();
        solveHard();
    }

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
                    board[rowNum][colNum] = tempNumToFill;
                    locations[tempNumToFill - 1][0][rowNum] = 1;
                    locations[tempNumToFill - 1][1][colNum] = 1;
                    locations[tempNumToFill - 1][2][square(rowNum, colNum)] = 1;
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

                for (int x = 0; x < 3; x++)
                {
                    //Row square check
                    if (locations[number - 1][2][(l / 3) * 3 + x])
                    {
                        for (int rowNum = 0; rowNum < 3; rowNum++)
                        {
                            for (int colNum = 0; colNum < 3; colNum++)
                            {
                                if (board[rowNum + rowFactor][colNum + x * 3] == number)
                                {
                                    row[rowNum] = -1;
                                }
                            }
                        }
                    }

                    //Col square check
                    if (locations[number - 1][2][l % 3 + x * 3])
                    {
                        for (int rowNum = 0; rowNum < 3; rowNum++)
                        {
                            for (int colNum = 0; colNum < 3; colNum++)
                            {
                                if (board[rowNum + x * 3][colNum + colFactor] == number)
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
                    board[coordinate[0]][coordinate[1]] = number;
                    locations[number - 1][0][coordinate[0]] = 1;
                    locations[number - 1][1][coordinate[1]] = 1;
                    locations[number - 1][2][l] = 1;
                }
            }
        }
    }
}

void solveHard()
{ // Function to check possibilities
}