/* pegJump.cpp

Author: ***Tirth Patel***
Program: #3, Peg Jump
CS 141, Spring 2019

Description:
This program represents a peg jumping puzzle  A
move is made by a peg jumping over another peg into an empty
spot, where the jumped peg is then removed from the board. The
game ends when there are no more valid moves to make. The object
is to eliminate as many pegs as possible.

Sample output:

Welcome to the peg jump puzzle!
Enter '-' to exit, or '+' for instructions.

A B C
D E F
G H I J K L M
N O P * Q R S
T U V W X Y Z
1 2 3
4 5 6

1. Enter the peg to move: +

Welcome to the peg jump puzzle. The board starts out with a
single blank position, represented by the '*'.  To make a
move, select the letter of a peg.  A peg must be able to
jump over an adjacent peg into a blank position for a move
to be valid.  The jumped peg is then removed from the board.
The game is over when there are no valid moves left. At any
point enter '-' to exit, or '+' for instructions.

1. Enter the peg to move: E

A B C
D * F
G H I * K L M
N O P E Q R S
T U V W X Y Z
1 2 3
4 5 6

2. Enter the peg to move: w

A B C
D * F
G H I W K L M
N O P * Q R S
T U V * X Y Z
1 2 3
4 5 6

3. Enter the peg to move: 5

A B C
D * F
G H I W K L M
N O P * Q R S
T U V 5 X Y Z
1 * 3
4 * 6

4. Enter the peg to move: 2
*** Invalid move, please retry. ***
4. Enter the peg to move: r

A B C
D * F
G H I W K L M
N O P R * * S
T U V 5 X Y Z
1 * 3
4 * 6

5. Enter the peg to move: R

* * *
* 1 *
* * * * * * *
* * * + * * *
* * * * * * *
* 2 *
* * *

There is more than one possible move.  Which move do you want? 1

     A B C
     D R F
 G H I * K L M
 N O P * * * S
 T U V 5 X Y Z
     1 * 3
     4 * 6

6. Enter the peg to move: -

Exiting...

27 pieces remaining. Ouch!
*/

#include <iostream>
#include <cctype>     // For toupper()
#include <cstdlib>
using namespace std;

//-------------------------------------------------------------------------------------
void displayInstructions()
{
    cout << endl
         << "Welcome to the peg jump puzzle. The board starts out with a \n"
         << "single blank position, represented by the '*'.  To make a \n"
         << "move, select the letter of a peg.  A peg must be able to \n"
         << "jump over an adjacent peg into a blank position for a move \n"
         << "to be valid.  The jumped peg is then removed from the board. \n"
         << "The game is over when there are no valid moves left. At any \n"
         << "point enter '-' to exit, or '+' for instructions. \n"
         << endl;
}

// ---------------------------------------------------------------------------- my functions

// ---------------------------------------------------------------------------- displayBoard()
// display the board
void displayBoard(char board[])
{
    int i;

    for(i = 22; i <99; i++)
    {
        // display space if the character is #
        if(board[i] != '#')
        {
            cout << board[i] << " ";
        }

        // display the character/board piece
        else
        {
            cout << " ";
        }

        // checking for end of the row to print from a new line
        if(i % 11 == 0)
        {
            cout << endl;
        }

    } // for ends

} // displayBoard ends

// ---------------------------------------------------------------------------- checkMove()
// check for possible moves and store the indexes of where the user can move as well as their adjacent indexes
int checkMove(char board[], char userValue, int possibleDest[],int possibleAdj[], int& possibleMoves)
{
    int i,
        posValue = 0; // stores the index of user input

    possibleMoves = 0; // initalizing possibleMoves to zero

    // searching for the user input
    for(i = 0; i < 121; i++)
    {
        if(board[i] == userValue)
        {
            posValue = i; // storing the index position of user input in posValue
            break;
        } // if ends

    } // for i ends

    // check for top move
    if(board[posValue - 22] == '*' && board[posValue - 11] != '*')
    {
        possibleDest[possibleMoves] = posValue - 22; // store the destination index
        possibleAdj[possibleMoves] = posValue - 11; // store the adjacent index
        possibleMoves++;
    } // if ends

    // check for left move
    if(board[posValue - 2] == '*' && board[posValue - 1] != '*')
    {
        possibleDest[possibleMoves] = posValue - 2; // store the destination index
        possibleAdj[possibleMoves] = posValue - 1; // store the adjacent index
        possibleMoves++;
    } // if ends

    // check for right move
    if(board[posValue + 2] == '*' && board[posValue + 1] != '*')
    {
        possibleDest[possibleMoves] = posValue + 2; // store the destination index
        possibleAdj[possibleMoves] = posValue + 1; // store the adjacent index
        possibleMoves++;
    } // if ends

    // check for bottom move
    if(board[posValue + 22] == '*' && board[posValue + 11] != '*')
    {
        possibleDest[possibleMoves] = posValue + 22; // store the destination index
        possibleAdj[possibleMoves] = posValue + 11; // store the adjacent index
        possibleMoves++;
    } // if ends

    return posValue;
} // checkMove ends

// ---------------------------------------------------------------------------- endGame()
// check if the user cannot make anymore moves, and if so end the game
int endGame(char board[])
{
    int i, j,
        adjIndex = 0, // used to store the adjacent index
        destIndex = 0, // used to store the destination index
        movesLeft = 0, // used to count the number of moves left / if there are any possible moves left
        adjIndexes[] = {-11, -1, 1, 11}, // used to calculate the adjacent indexes
        moveIndexes[] = {-22, -2, 2, 22}; // used to calculate the destination indexes

    for(i = 0; i < 121; i++)
    {
        if(board[i] != '#' && board[i] != '*')
        {
            for(j = 0; j < 4; j++)
            {
                destIndex = i + moveIndexes[j]; // storing the destination index
                adjIndex = i + adjIndexes[j]; // storing the adjacent index

                if(board[destIndex] == '*' && board[adjIndex] != '*' && board[adjIndex] != '#')
                {
                    movesLeft++; // increment the moves left
                } // inner if ends

            } // for j ends

        } // outer if ends

    } // for i ends

  return movesLeft;
}

// ---------------------------------------------------------------------------- makeMove()
// make the move
void makeMove(char board[], char userValue, int destIndex, int adjIndex, int posValue)
{
    board[destIndex] = userValue; // change the value at the destination index to the user input
    board[adjIndex] = '*'; // change the value at the adjacent index to an asterisk
    board[posValue] = '*'; // change the value at the index of user input to an asterisk

} // makeMove ends

// ---------------------------------------------------------------------------- multipleMove()
// print the board with the possible destinations and ask the user for their choice
void multipleMove(char board[], char userValue, int possibleDest[], int possibleAdj[], int possibleMoves, int posValue)
{
    char moveNumber = '1', // used to indicate the possible move on the board
         multipleMoveInput, // used to store the user input for which possible move they want
         multipleMoveBoard[] = {
                                  '#','#','#','#','#','#','#','#','#','#','#',
                                  '#','#','#','#','#','#','#','#','#','#','#',
                                  '#','#','#','#','*','*','*','#','#','#','#',
                                  '#','#','#','#','*','*','*','#','#','#','#',
                                  '#','#','*','*','*','*','*','*','*','#','#',
                                  '#','#','*','*','*','*','*','*','*','#','#',
                                  '#','#','*','*','*','*','*','*','*','#','#',
                                  '#','#','#','#','*','*','*','#','#','#','#',
                                  '#','#','#','#','*','*','*','#','#','#','#',
                                  '#','#','#','#','#','#','#','#','#','#','#',
                                  '#','#','#','#','#','#','#','#','#','#','#'
                               };

    int i, j,
        adjIndex = 0, // used to store the adjacent index
        destIndex = 0; // used to store the destination index

    multipleMoveBoard[posValue] = '+'; // change the location at which the character to move is to a '+' character

    // loop to display the possible move number at the possible destination indexes
    for(i = 0; i < possibleMoves; i++)
    {
        destIndex = possibleDest[i]; // storing the destination index
        multipleMoveBoard[destIndex] = moveNumber; // display the possible move number at the possible destination indexes
        moveNumber++; // increment the possible move number
    } // for i ends

    // display the board and ask for user input
    displayBoard(multipleMoveBoard);
    cout << "There is more than one possible move.  Which move do you want? ";
    cin >> multipleMoveInput;

    // loop to find the possible move number that the user chose and store it's index
    for(i = 0; i < 121; i++)
    {
        if(multipleMoveBoard[i] == multipleMoveInput)
        {
            for(j = 0; j < possibleMoves; j++)
            {
                if(possibleDest[j] == i)
                {
                    destIndex = possibleDest[j]; // storing the destination index
                    adjIndex = possibleAdj[j]; // storing the adjacent index
                    break;
                } // inner if ends

            } // for j ends

        } // outer if ends

    } // for i ends

    // make the move
    makeMove(board, userValue, destIndex, adjIndex, posValue);


} // multipleMove ends

// ---------------------------------------------------------------------------- moveDriver()
// moveDriver() acts as the central function
int moveDriver(char board[], char userInput)
{
    int flag = 0, // used to check for invalid move
        posValue = 0, // stores position of user input
        movesLeft = 0, // used to count number of moves left, used to check if the game should end or not
        possibleAdj[] = {0, 0, 0, 0}, // top, left, right, bottom
        possibleDest[] = {0, 0, 0, 0}, // top, left, right, bottom
        possibleMoves = 0; // number of possible moves

    // storing the user input in another variable for ease of tracking / passing arguments
    char userValue = userInput;

    // get the index position of the user input and check the number of possible moves the user can make
    posValue = checkMove(board, userValue, possibleDest, possibleAdj, possibleMoves);

    // if possibleMoves = 0 then invalid input, handled using flag in main()
    if(possibleMoves == 0)
    {
        flag = 0;
    } // if ends

    // if possibleMoves = 1, call makeMove() directly
    else if(possibleMoves == 1)
    {
        flag = 1;
        makeMove(board, userValue, possibleDest[0], possibleAdj[0], posValue);
    } // else if ends

    // if possibleMoves > 1, ask user which position, then call makeMove()
    else if(possibleMoves > 1)
    {
        flag = 1;
        multipleMove(board, userValue, possibleDest, possibleAdj, possibleMoves, posValue);
    } // else if ends

    return flag;
} // moveDriver ends

//-------------------------------------------------------------------------------------
int main()
{
    //Variable declarations
    char board[] = {
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','A','B','C','#','#','#','#',
            '#','#','#','#','D','E','F','#','#','#','#',
            '#','#','G','H','I','J','K','L','M','#','#',
            '#','#','N','O','P','*','Q','R','S','#','#',
            '#','#','T','U','V','W','X','Y','Z','#','#',
            '#','#','#','#','1','2','3','#','#','#','#',
            '#','#','#','#','4','5','6','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#'
          };

    // my variable declarations
    int roundNumber = 1, // used to count the round number
        numberOfPieces = 0, // used to count the number of pieces left in the board
        movesLeft = 0, // used to count number of moves left, used to check if the game should end or not
        flagCheck = 2; // used to check for invlaid move using value returned from moveDriver()

    char userInput; // used to store the user input

    cout << "Welcome to the peg jump puzzle! \n"
         << "Enter '-' to exit, or '+' for instructions. "
         << endl;

    displayBoard(board); // displaying the board

    // Main loop to play the game
    // ...
    while(true)
    {
        // checking if the user can make a move or not
        movesLeft = endGame(board);

        // if the user cannot make any moves then end the game
        if(movesLeft == 0)
        {
            break;
        } // if ends

        // if the user can make at least one move then continue the game
        else
        {
            // Prompt for and get move
            // ...
            cout << roundNumber << ". Enter the peg to move: ";
            cin >> userInput;
            cout << endl;

            // convert input to upper case
            userInput = toupper(userInput);

            // Check for '-' to exit, and '+' for displaying instructions
            // ...
            if(userInput == '+')
            {
                displayInstructions(); // displaying instructions
            }

            else if(userInput == '-')
            {
                cout << "Exiting..." << endl << endl; // exiting the game based on user inout of '-'
                break;
            }

            else
            {
                // Make move
                // ...
                flagCheck = moveDriver(board, userInput);

                // if the flag returned from moveDriver() is one then it indicates a valid move by user
                if(flagCheck == 1)
                {
                    // Increment move number and display the board
                    // ...
                    roundNumber++;
                    displayBoard(board);
                } // if ends

                // if the flag returned from moveDriver() is zero then it indicates invalid move by user
                else if(flagCheck == 0)
                {
                    cout << "*** Invalid move, please retry. ***" << endl;
                    continue;
                } // else if ends

            } // inner else ends

        } // outer else ends / else, attached to if(movesLeft == 0), ends

    } // while(true) ends

    // Display appropriate message depending on number of remaining pegs
    // ...
   // checking the number of pieces remaining on the board
    numberOfPieces = 32 - roundNumber + 1;
    if(numberOfPieces == 1)
    {
        cout << numberOfPieces << " piece remaining. Excellent!" << endl;
    }

    else if(numberOfPieces == 2)
    {
        cout << numberOfPieces << " pieces remaining. Good!" << endl;
    }

    else if(numberOfPieces == 3)
    {
        cout << numberOfPieces << "pieces remaining. OK." << endl;
    }

    else if(numberOfPieces == 4)
    {
        cout << numberOfPieces << " pieces remaining. Needs Improvement." << endl;
    }

    else if(numberOfPieces >= 5)
    {
        cout << numberOfPieces << " pieces remaining. Ouch!" << endl;
    }

    return 0;
}//end main()
