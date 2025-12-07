#include <iostream>
#include <windows.h>
#include <conio.h>
#include <random>
#include <chrono>
using namespace std;

// === menu functions ===
void Menu();
void printMaze();
void Gameover();
void movecoin();


// === Player Functions ===
void printPlayer();
void erasePlayer();
void move();

// === Enemy Functions ===
void printEnemy1();
void EraseEnemy1();
void moveEnemy1();
void printEnemy2();
void EraseEnemy2();
void moveEnemy2();
void printEnemy3();
void EraseEnemy3();
void moveEnemy3();

// === Default functoins ===
void gotoxy(int x, int y);
void getconsolemeasures(int &width, int &height);
int random( int lower, int upper);

// === global variables ===
int width, height, px, py, x, y; // p for player --- e for enemy --- width/height of consle
int ex1 = 1, ey1 = 4;
int ex2 = 1, ey2 = 8;
int ex3 = 1, ey3 = 12;
int cx, cy = 4;
bool enemy1moveright = true;
bool enemy2moveright = false;
bool enemy3moveright = true;
bool enemy2movedown = false;
bool enemy3movedown = true;

// ========(++++++++++ Main Calling +++++++++++)=======
int main()
{
    getconsolemeasures(width, height);
    ex2 = width - 8;     // initializing 2nd enemy as width is not measured above
    ex3 = width / 2 - 5; // initializing 3rd enemy as width is not measured above
    printMaze();
    Menu();
    move(); // enemy is also moving inside move

    // Gameover();
    return 0;
}

void printMaze()
{
    system("cls");
    int primarywidth = 0;
    int primaryheight = 0;

    while (primaryheight < height)
    {
        if (primaryheight == height)
        {
            break;
        }
        if (primaryheight == 0 || primaryheight == 3)
        {
            while (primarywidth < width)
            {
                gotoxy(primarywidth, primaryheight);
                cout << "_";
                primarywidth++;
            }
            primarywidth = 0;
            primaryheight++;
        }
        else if (primaryheight > 0 && primaryheight <= height - 1 && primaryheight != 3)
        {
            while (primaryheight > 0 && primaryheight <= height - 1)
            {

                gotoxy(primarywidth, primaryheight);
                if (primarywidth == 0)
                {
                    cout << "|";
                    primarywidth++;
                }
                else if (primarywidth == width - 1)
                {
                    cout << "|";
                    primaryheight++;
                    primarywidth = 0;
                }
                else
                {
                    if (primaryheight == 3 || primaryheight == height - 1)
                    {
                        cout << "_";
                    }
                    else
                    {
                        cout << " ";
                    }
                    primarywidth++;
                }
            }
        }
        else if (primaryheight == height)
        {
            break;
        }
    }
    gotoxy(width / 2 - 7, 2);
    cout << "Space Xtrive";
    gotoxy(width - 15, 1);
    cout << "Score : 0";
    gotoxy(width - 15, 2);
    cout << "Level : 1";
    gotoxy(3, 1);
    cout << "Health : 100";
}

void Menu()
{
    gotoxy(width / 2 - 16, height / 2);
    cout << "Welcome to space Xtriver game.";
    Sleep(2000);
    gotoxy(width / 2 - 16, height / 2);
    cout << "                              ";
}

int random( int lower, int upper)
{
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_int_distribution<> dist(lower, upper);
    int randomNum = dist(gen);
    return randomNum;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getconsolemeasures(int &width, int &height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Gameover()
{
    gotoxy(width / 2 - 6, height / 2 - 1);
    cout << "Game Over.";
    Sleep(1000);
    system("cls");
}

void printEnemy1()
{
    gotoxy(ex1, ey1 + 1);
    cout << "(~~~~)";
    gotoxy(ex1, ey1 + 2);
    cout << "|=||=|";
    gotoxy(ex1, ey1 + 3);
    cout << "  \\/  ";
}

void EraseEnemy1()
{
    gotoxy(ex1, ey1 + 1);
    cout << "      ";
    gotoxy(ex1, ey1 + 2);
    cout << "       ";
    gotoxy(ex1, ey1 + 3);
    cout << "       ";
}

void moveEnemy1()
{
    if (enemy1moveright == true)
    {
        EraseEnemy1();
        ex1++;
        printEnemy1();
        if (ex1 == width - 8)
        {
            enemy1moveright = false;
        }
    }
    else
    {
        EraseEnemy1();
        ex1--;
        printEnemy1();
        if (ex1 == 1)
        {
            enemy1moveright = true;
        }
    }
}

void printEnemy2()
{
    gotoxy(ex2, ey2 + 1);
    cout << "(~~~~)";
    gotoxy(ex2, ey2 + 2);
    cout << "|=||=|";
    gotoxy(ex2, ey2 + 3);
    cout << "  \\/";
}

void EraseEnemy2()
{
    gotoxy(ex2, ey2 + 1);
    cout << "      ";
    gotoxy(ex2, ey2 + 2);
    cout << "       ";
    gotoxy(ex2, ey2 + 3);
    cout << "       ";
}

void moveEnemy2()
{
    if (enemy2movedown == true)
    {
        EraseEnemy2();
        ey2++;
        if (enemy2moveright == true)
        {
            ex2++;
        }
        else
        {
            ex2--;
        }
        printEnemy2();
        if (ey2 == height - 5)
        {
            enemy2movedown = false;
        }
    }
    else
    {
        EraseEnemy2();
        ey2--;
        if (enemy2moveright == true)
        {
            ex2++;
        }
        else
        {
            ex2--;
        }
        printEnemy2();
        if (ey2 == 4)
        {
            enemy2movedown = true;
        }
    }
    if (ex2 == width - 8)
    {
        enemy2moveright = false;
    }
    else if (ex2 == 1)
    {
        enemy2moveright = true;
    }
}

void printEnemy3()
{
    gotoxy(ex3, ey3 + 1);
    cout << "(~~~~)";
    gotoxy(ex3, ey3 + 2);
    cout << "|=||=|";
    gotoxy(ex3, ey3 + 3);
    cout << "  \\/";
}

void EraseEnemy3()
{
    gotoxy(ex3, ey3 + 1);
    cout << "      ";
    gotoxy(ex3, ey3 + 2);
    cout << "       ";
    gotoxy(ex3, ey3 + 3);
    cout << "       ";
}

void moveEnemy3()
{
    if (enemy3movedown == true)
    {
        EraseEnemy3();
        ey3++;
        if (ey3 == height - 5)
        {
            enemy3movedown = false;
            if (enemy3moveright == true)
            {
                ex3++;
            }
            else
            {
                ex3--;
            }
        }
        printEnemy3();
    }
    else
    {
        EraseEnemy3();
        ey3--;
        if (ey3 == 4)
        {
            enemy3movedown = true;
            if (enemy3moveright == true)
            {
                ex3++;
            }
            else
            {
                ex3--;
            }
        }
        printEnemy3();
    }
    if (ex3 == width - 8)
    {
        enemy3moveright = false;
    }
    else if (ey3 == height - 5)
    {
        enemy3movedown = false;
    }
}

void printPlayer()
{
    gotoxy(px + 1, py - 8);
    cout << "     /\\";
    gotoxy(px + 1, py - 7);
    cout << "  __/~~\\__";
    gotoxy(px + 1, py - 6);
    cout << " /  |  |  \\";
    gotoxy(px + 1, py - 5);
    cout << "====.  .====";
    gotoxy(px + 1, py - 4);
    cout << "    ||||     ";
}

void erasePlayer()
{
    gotoxy(px + 1, py - 8);
    cout << "            ";
    gotoxy(px + 1, py - 7);
    cout << "            ";
    gotoxy(px + 1, py - 6);
    cout << "            ";
    gotoxy(px + 1, py - 5);
    cout << "            ";
    gotoxy(px + 1, py - 4);
    cout << "            ";
}

void move()
{
    px = width / 2;
    py = height + 1;
    printPlayer();
    while (true)
    {
        if (GetAsyncKeyState(VK_RIGHT))
        {
            if (px >= width - 15)
            {
                continue;
            }
            erasePlayer();
            px++;
            printPlayer();
            Sleep(10);
        }
        else if (GetAsyncKeyState(VK_LEFT))
        {
            if (px <= 1)
            {
                continue;
            }
            erasePlayer();
            px--;
            printPlayer();
            Sleep(10);
        }
        else if (GetAsyncKeyState(VK_UP))
        {
            if (py <= 12)
            {
                continue;
            }
            erasePlayer();
            py--;
            printPlayer();
            Sleep(10);
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            if (py >= height + 2)
            {
                continue;
            }
            erasePlayer();
            py++;
            printPlayer();
            Sleep(10);
        }
        Sleep(200);
        moveEnemy1();
        moveEnemy2();
        moveEnemy3();
        movecoin();
    }
}

void movecoin()
{
    if (cx == 0){
        cx = random(2, width - 3);
    }
    gotoxy(cx, cy);
    cout << "   ";
    cy++;
    gotoxy(cx, cy);
    cout << "(+)";
    if (cy == height - 2){
        gotoxy(cx, cy);
        cout << "   ";
        cx = 0;
        cy = 4;
    }
}