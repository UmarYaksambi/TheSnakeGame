#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <cstdlib> 
#include <ctime>   
#include <mutex>  

using namespace std;

const int HEIGHT = 20;
const int WIDTH = 40;
bool GameOver;
int x, y, xFruit, yFruit, score;
int tailX[100], tailY[100];
int nTail;
enum directions { STOP = 0, RIGHT, LEFT, UP, DOWN };
directions dir;
mutex mtx; 

void HideCaret() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; 
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void setup() {
    srand(time(0)); // Initialize random seed
    HideCaret();    // Hide the caret
    GameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    do
    {
        xFruit = rand() % (WIDTH + 2);
        yFruit = rand() % (HEIGHT + 2);
    } while(xFruit == 0 || yFruit == 0);
    
    score = 0;
    nTail = 0;
}

void SetCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}  // ???

void Draw() {
    SetCursorPosition(0, 1);
    cout << "Score: " << score << endl;
    cout << "High Score: " << "Need to integrate SQL" << endl;

    for (int i = 0; i < HEIGHT + 2; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            if (i == 0 || i == HEIGHT + 1 || j == 0 || j == WIDTH + 1) {
                cout << "#";
            } else if (i == y && j == x) {
                cout << ">";
            } else if (i == yFruit && j == xFruit) {
                cout << "F";  // I wanna use 🍎 emoji instead
                // Also add BIG Fruit
            } else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "O";
                        print = true;
                        break;
                    }
                }
                if (!print) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}

void Input() {
    while (!GameOver) {
        if (_kbhit()) {
            switch (_getch()) {
                case 'a':
                case 75:
                    mtx.lock();
                    if (dir != RIGHT) dir = LEFT;
                    mtx.unlock();
                    break;
                case 'd':
                case 77:
                    mtx.lock();
                    if (dir != LEFT) dir = RIGHT;
                    mtx.unlock();
                    break;
                case 'w':
                case 72:
                    mtx.lock();
                    if (dir != DOWN) dir = UP;
                    mtx.unlock();
                    break;
                case 's':
                case 80:
                    mtx.lock();
                    if (dir != UP) dir = DOWN;
                    mtx.unlock();
                    break;
                case 'x':
                    mtx.lock();
                    GameOver = true;
                    mtx.unlock();
                    break;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(10)); 
    }
}

void Logic() {
    while (!GameOver) {
        mtx.lock();
        int prevTailX = tailX[0];
        int prevTailY = tailY[0];
        int prev2TailX, prev2TailY;

        tailX[0] = x;
        tailY[0] = y;

        for (int i = 1; i < nTail; i++) {
            prev2TailX = tailX[i];
            prev2TailY = tailY[i];
            tailX[i] = prevTailX;
            tailY[i] = prevTailY;
            prevTailX = prev2TailX;
            prevTailY = prev2TailY;
        }

        switch (dir) {
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
            default:
                break;
        }

        // Wrapping around the edges of the screen
        // Will do Walls ON and OFF option later
        if (x >= (WIDTH + 1)) x = 0;
        if (x < 0) x = (WIDTH + 1);
        if (y >= (HEIGHT + 1)) y = 0;
        if (y < 0) y = HEIGHT + 1;

        // Check collision with tail
        for (int i = 0; i < nTail; i++) {
            if (tailX[i] == x && tailY[i] == y) {
                GameOver = true;
            }
        }

        // Check collision with fruit
        if (x == xFruit && y == yFruit) {
            score += 10;
            // Reposition fruit
            bool fruitOnSnake = true;
            while (fruitOnSnake) {
                do
                {
                    xFruit = rand() % WIDTH;
                    yFruit = rand() % HEIGHT;
                } while(xFruit == 0 || yFruit == 0);

                fruitOnSnake = false;
                for (int i = 0; i < nTail; i++) {
                    if (tailX[i] == xFruit && tailY[i] == yFruit) {
                        fruitOnSnake = true;
                        break;
                    }
                }
            }
            nTail++;
        }
        mtx.unlock();
        this_thread::sleep_for(chrono::milliseconds(50)); 
    }
}

int main() {
    setup();

    thread inputThread(Input);
    thread logicThread(Logic);

    while (!GameOver) {
        Draw();
        this_thread::sleep_for(chrono::milliseconds(50)); // Need to adjust delay for game speed with score
    }

    inputThread.join();
    logicThread.join();

    cout << endl << "Game Over!" << endl;
    if(score > 100)
        cout << "New High Score!" << endl;

    cout << "Score: " << score << endl << endl;

    return 0;
}
