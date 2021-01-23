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

    printf("\n\nEnter any key to solve the board:");
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
                break;
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
    int possibilities[9][9][9];
    int possibleFill[81];
    int iterator = 0;
    //possibleFill[i] is 4 digit number whose thousands digit is rowNum
    //hundreds digit is colNum, tens digit is minNumber, and units digit is minCount

    //initialize possibleFill[81]
    for (int i = 0; i < 81; i++)
    {
        possibleFill[i] = 9999;
    }

    //Board1 stores a copy of board
    int board1[9][9];
    for (int rowNum = 0; rowNum < 9; rowNum++)
    {
        for (int colNum = 0; colNum < 9; colNum++)
        {
            board1[rowNum][colNum] = board[rowNum][colNum];
        }
    }

    //Initialize possibilities
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                possibilities[i][j][k] = 0;
            }
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

    //Initialize twoPossibilities
    int twoPossibilities[9][9][2];
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

    //Now we have possibilities at (i,j) stored in possibilities[i][j][]
    //All elements with only two possibilities stored in twoPossiblities[i][j][]
    //These possibilities are stored

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
                    possibleFill[iterator] += twoPossibilities[rowNum][colNum][0] * 10;
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
    //put the next lines in for loop of sorted array
    //sort array possibleFill
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
            if(i == iterator - 1) {
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
    if(extreme) {
        for(int i = 0; i< iterator - 1; i++) {
            update(possibleFill[i] / 1000, (possibleFill[i] % 1000) / 100, (possibleFill[i] % 100) / 10);
            for(int j = 0; j<iterator; j++) {
                if(i==j) {
                    break;
                }
                update(possibleFill[j] / 1000, (possibleFill[j] % 1000) / 100, (possibleFill[j] % 100) / 10);
                solveBoard();
                if (checkSolve())
                {
                    if(i == iterator - 1) {
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
        }
    }
}

void solveBoard()
{
    int previousCheck = 0;
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
    }
}