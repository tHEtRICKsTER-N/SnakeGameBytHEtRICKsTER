/*SnakeGameBytHEtRICKstER

Use W to go UP 
    S to go Down
    A to go left
    D to go right

if you eat one fruit , the score increments by 1.
if you hit the WALLS , you LOSE! and if you hit Yourself , YOU LOSE!.
Enjoy !!!


SOME FUNCTIONS USED :-
srand() - it retrns a andom number , andif we modulo divide it with any number it will return a random value
         less than the the divisor. eg - rand()%20 will return random number less than 20

system("CLS") - clears the screen - stdlib.h

_kbhit() - returns true value if a key is pressed - conio.h
_getch() - pauses the screen until a key is pressed and stores it's ASCII value - conio.h
Sleep()  - it holds the program for miliseconds provided as arguments - windows.h
str.length() - returns the number of characters in str string - string.h

AXES :-
             Y`
             |
             |  
             |
             |  
             |  
X` - - - - - + - - - - - X
             |
             |  
             |
             |  
             |  
             Y

*/

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
using namespace std;

//Game Variables:-

bool gameOver;
const int screenHeight = 25;
const int screenWidth = 50;
int snakeX, snakeY, fruitX, fruitY, score, tailX[100], tailY[100], nTail;
string gameName = "-+-+- SNAKE GAME -+-+-", gameScore = "Your Score = ",gameInstructions="Use WSAD to Move and ESC to exit";
enum Actions
{
    STOP = 0,
    LEFT,
    RIGHT, // I HAVE CREATED AN ENUM WHICH WILL HAVE THE VALUES LEFT 1 , RIGHT 2 , UP 3 , AND DOWN 4
    UP,
    DOWN
};
Actions snakeActions;

int numLength(int a)
{
    int count = 0;
    if (a == 0)
        return 1;
    else
    {
        while (a != 0)
        {
            a /= 10;
            count++;
        }
        return count;
    }
}

void startGame()
{
    for (int i = 1; i <= screenWidth; i++)
    {
        cout << "#";
    }

    cout << endl;
    for (int i = 1; i <= screenHeight; i++)
    {
        for (int j = 1; j <= screenWidth; j++)
        {
            if (j == 1 || j == screenWidth)
                cout << "#";
            else if (i == screenHeight / 2 && j == 15)
            {
                cout << gameName;
                j += gameName.length();
                j--;
            }
            else
                cout << " ";
        }
        cout << endl;
    }

    for (int i = 1; i <= screenWidth; i++)
    {
        cout << "#";
    }
    cout << endl;


    Sleep(2000);
    system("CLS");

    for (int i = 1; i <= screenWidth; i++)
    {
        cout << "#";
    }

    cout << endl;
    for (int i = 1; i <= screenHeight; i++)
    {
        for (int j = 1; j <= screenWidth; j++)
        {
            if (j == 1 || j == screenWidth)
                cout << "#";
            else if (i == screenHeight / 2 && j == 10)
            {
                cout << gameInstructions;
                j += gameInstructions.length();
                j--;
            }
            else
                cout << " ";
        }
        cout << endl;
    }

    for (int i = 1; i <= screenWidth; i++)
    {
        cout << "#";
    }
    cout << endl;

    Sleep(5000);
}

void endGame()
{
    system("CLS");
    for (int i = 1; i <= screenWidth; i++)
    {
        cout << "#";
    }

    cout << endl;
    for (int i = 1; i <= screenHeight; i++)
    {
        for (int j = 1; j <= screenWidth; j++)
        {
            if (j == 1 || j == screenWidth)
                cout << "#";
            else if (i == screenHeight / 2 && j == 15)
            {
                cout << gameScore << score;
                j += numLength(score);
                j += gameScore.length();
                j--;
            }
            else
                cout << " ";
        }
        cout << endl;
    }

    for (int i = 1; i <= screenWidth; i++)
    {
        cout << "#";
    }
    cout << endl;
    system("pause"); //press any key to continue
}

void InitialSetup()
{
    gameOver = false;
    snakeActions = STOP;
    snakeX = screenWidth / 2;
    snakeY = screenHeight / 2;
    fruitX = rand() % screenWidth;
    fruitY = rand() % screenHeight;
    score = 0;
}

void drawObjects()
{
    system("CLS"); //clears the screen

    //displaying the borders of the game

    //upper walls
    for (int i = 1; i <= screenWidth + 1; i++)
    {
        cout << "#";
    }
    cout << endl;

    //side walls
    for (int i = 1; i <= screenHeight; i++)
    {
        for (int j = 1; j <= screenWidth; j++)
        {
            if (j == 1 || j == screenWidth)
                cout << "#";
            if (i == snakeY && j == snakeX) //snake head printing
                cout << "0";
            else if (i == fruitY && j == fruitX) //fruit printing
                cout << "*";
            else
            {
                bool tailPrinted = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        tailPrinted = true;
                    }
                }
                if (!tailPrinted)
                    cout << " ";
            }
        }
        cout << endl;
    }

    //bottom walls
    for (int i = 1; i <= screenWidth + 1; i++)
    {
        cout << "#";
    }
    cout << endl;
    cout << "Score : " << score;
}

void gameInput()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            snakeActions = LEFT;
            break;

        case 's':
            snakeActions = DOWN;
            break;

        case 'd':
            snakeActions = RIGHT;
            break;

        case 'w':
            snakeActions = UP;
            break;

        case 27:
            gameOver = true;
            break;
        }
    }
}

void gameLogic()
{
    int prevTailX = tailX[0], prevTailY = tailY[0];
    int prevTailX2, prevTailY2;
    for (int i = 1; i < nTail; i++)
    {
        prevTailX2 = tailX[i];
        prevTailY2 = tailY[i];
        tailX[i] = prevTailX;
        tailY[i] = prevTailY;
        prevTailX = prevTailX2;
        prevTailY = prevTailY2;
        tailX[0] = snakeX;
        tailY[0] = snakeY;
    }
    switch (snakeActions)
    {
    case UP:
        snakeY--;
        break;
    case DOWN:
        snakeY++;
        break;
    case LEFT:
        snakeX--;
        break;
    case RIGHT:
        snakeX++;
        break;
    }

    if (snakeX >= screenWidth || snakeX <= 0 || snakeY >= screenHeight || snakeY <= 0)
        gameOver = true;
    //if snake touches the walls , game ends

    for (int i = 0; i < nTail; i++)
    { //if snaketouches it's tail , game gets over
        if (tailX[i] == snakeX && tailY[i] == snakeY)
            gameOver = true;
    }

    if (snakeX == fruitX && snakeY == fruitY) //if snake touches the fruit , socre increments by 1
    {
        srand(time(0));
        score += 1;
        fruitX = (rand() % screenWidth) + 1;
        fruitY = (rand() % screenHeight) + 1;
        nTail++;
    }
}

int main()
{

    //this sets the console window size
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 480, 500, TRUE);

    startGame();
    InitialSetup();
    while (!gameOver)
    {
        drawObjects();
        gameInput();
        gameLogic();
    }
    endGame();
}
