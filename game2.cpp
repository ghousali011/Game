#include <iostream>
#include <windows.h>
#include <conio.h>
#include <random>
#include <chrono>
using namespace std;

void move();
// === menu functions ===
void Menu();
void printMaze();
void Gameover();

// === pause function ===
bool pauseMenu();
void saveRegion(int x, int y, int width, int height);
void restoreRegion(int x, int y, int width, int height);

// === coin functions ===
void movecoin();
bool coinCollision();

// === Player Functions ===
void printPlayer();
void erasePlayer();

// === Enemy Functions ===
void move_enemy();
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
int random(int lower, int upper);
void setcolor(string color);
void hideCursor();
void showCursor();
void setCursorSize(int size);

// === global variables ===
CHAR_INFO savedBuffer[5][25];
int width, height, px, py, x, y; // p for player --- e for enemy --- width/height of consle
string headingcolor = "06", enemycolor = "03", coincolor = "02", playercolor = "05";
// --------- enemy variables ----------
int ex1 = 1, ey1 = 4;
int ex2 = 1, ey2 = 8;
int ex3 = 1, ey3 = 12;
bool enemy1moveright = true;
bool enemy2moveright = false;
bool enemy3moveright = true;
bool enemy2movedown = false;
bool enemy3movedown = true;
// -------- coin veriables -------------
int cx, cy = 4;
int score = 0;
vector<string> coinFrames = {"(+)", "(x)", "(*)", "(o)", "(0)"};
int coinFrameIndex = 0;
unsigned int lastCoinFrameTime = 0;
const unsigned int coinFrameDelay = 120;

// ========(++++++++++ Main Calling +++++++++++)=======
int main()
{
    hideCursor();
    getconsolemeasures(width, height);
    setcolor(headingcolor);
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

int random(int lower, int upper)
{
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_int_distribution<> dist(lower, upper);
    int randomNum = dist(gen);
    return randomNum;
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
    setcolor(playercolor);
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
    setcolor(enemycolor);
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

// ============================================================ over all movement ============================================================
void move()
{
    px = width / 2;
    py = height + 1;
    printPlayer();

    DWORD lastEnemyMove = GetTickCount();
    DWORD enemyDelay = 150;

    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            while (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {}
            bool wantExit = pauseMenu();
            if (wantExit)
            {
                setcolor ("04");
                Gameover();
                setcolor("07");
                exit(0);
            }
        }
        if ((GetAsyncKeyState(VK_RIGHT) & 0x8000 )&& px < width - 15)
        {
            erasePlayer();
            px++;
            printPlayer();
        }
        else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && px > 1)
        {
            erasePlayer();
            px--;
            printPlayer();
        }
        else if ((GetAsyncKeyState(VK_UP) & 0x8000) && py > 12)
        {
            erasePlayer();
            py--;
            printPlayer();
        }
        else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && py < height + 2)
        {
            erasePlayer();
            py++;
            printPlayer();
        }
        if (GetTickCount() - lastEnemyMove >= enemyDelay)
        {
            move_enemy();
            movecoin();
            lastEnemyMove = GetTickCount();
        }
        Sleep(10);
    }
}

void move_enemy()
{
    moveEnemy1();
    if (score > 10)
    {
        moveEnemy2();
    }
    if (score > 20)
    {
        moveEnemy3();
    }
    if (score == 21)
    {
        gotoxy(width - 7, 2);
        setcolor(headingcolor);
        cout << "3";
        setcolor(enemycolor);
    }
    else if (score == 11)
    {
        gotoxy(width - 7, 2);
        setcolor(headingcolor);
        cout << "2";
        setcolor(enemycolor);
    }
}
// ======================================================= coin functions ============================================================
void movecoin()
{
    const int frameCount = (int)coinFrames.size();
    if (frameCount <= 0)
        return;
    if (cx == 0)
    {
        cx = random(2, width - 12);
        cy = 4;
        coinFrameIndex = 0;
        lastCoinFrameTime = GetTickCount();
    }
    if (cy >= 0 && cy < height)
    {
        gotoxy(cx, cy);
        cout << "   ";
    }
    cy++;
    if (cx != 0)
    {
        if (GetTickCount() - lastCoinFrameTime >= coinFrameDelay)
        {
            coinFrameIndex = (coinFrameIndex + 1) % frameCount;
            lastCoinFrameTime = GetTickCount();
        }
        if (coinFrameIndex < 0)
            coinFrameIndex = 0;
        if (coinFrameIndex >= frameCount)
            coinFrameIndex = coinFrameIndex % frameCount;
        if (cy >= 0 && cy < height)
        {
            setcolor(coincolor);
            gotoxy(cx, cy);
            cout << coinFrames[coinFrameIndex];
            setcolor(enemycolor);
        }
    }
    if (cy >= height - 2)
    {
        if (cy >= 0 && cy < height)
        {
            gotoxy(cx, cy);
            cout << "   ";
        }
        cx = 0;
        cy = 4;
        return;
    }

    // -------- SCORE DETECTION --------
    if (coinCollision())
    {
        int oldX = cx;
        int oldY = cy;
        score++;
        if (oldY >= 0 && oldY < height)
        {
            gotoxy(oldX, oldY);
            cout << "\a   ";
        }
        cx = 0;
        cy = 4;
        coinFrameIndex = 0;
        lastCoinFrameTime = GetTickCount();
        gotoxy(width - 7, 1);
        setcolor(headingcolor);
        cout << score;
        setcolor(enemycolor);
    }
}

// --------------------- checking coin acceoptance -----------------
bool coinCollision()
{
    int coinLeft = cx;
    int coinRight = cx + 2;
    int coinY = cy;

    int playerLeft = px + 1;
    int playerRight = px + 12;
    int playerTop = py - 8;
    int playerBottom = py - 3;

    if (coinY >= playerTop && coinY <= playerBottom)
    {
        if (coinRight >= playerLeft && coinLeft <= playerRight)
        {
            return true;
        }
    }

    return false;
}
// ============================================= pause game =====================================================================================
bool pauseMenu()
{
    int bx = width / 2 - 10;
    int by = height / 2 - 2;
    int bw = 22;
    int bh = 5;
    saveRegion(bx, by, bw, bh);

    setcolor("0E");
    gotoxy(bx, by);
    cout << "====================";
    gotoxy(bx, by + 1);
    cout << "      GAME PAUSED    ";
    gotoxy(bx, by + 2);
    cout << "  ENTER = Continue   ";
    gotoxy(bx, by + 3);
    cout << "  ESC   = Exit Game  ";
    gotoxy(bx, by + 4);
    cout << "====================";
    while (true)
    {
        if (GetAsyncKeyState(VK_RETURN) & 0x8000)
        {
            while (GetAsyncKeyState(VK_RETURN) & 0x8000) {}
            restoreRegion(bx, by, bw, bh);
            return false;
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            while (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {}
            for (int i = 0; i < 5; i++)
            {
                gotoxy(bx, by + i);
                cout << "                    ";
            }
            return true;
        }
        Sleep(50);
    }
}
void saveRegion(int x, int y, int width, int height)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT readArea = { (SHORT)x, (SHORT)y, (SHORT)(x + width - 1), (SHORT)(y + height - 1) };
    COORD bufferSize = { (SHORT)width, (SHORT)height };
    COORD bufferCoord = { 0, 0 };

    ReadConsoleOutput(
        h,
        (CHAR_INFO*)savedBuffer,  // store into buffer
        bufferSize,
        bufferCoord,
        &readArea
    );
}
void restoreRegion(int x, int y, int width, int height)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT writeArea = { (SHORT)x, (SHORT)y, (SHORT)(x + width - 1), (SHORT)(y + height - 1) };
    COORD bufferSize = { (SHORT)width, (SHORT)height };
    COORD bufferCoord = { 0, 0 };

    WriteConsoleOutput(
        h,
        (CHAR_INFO*)savedBuffer,
        bufferSize,
        bufferCoord,
        &writeArea
    );
}

// ============================================== Default functions =============================================================================
// ------------ setting color -----------------
void setcolor(string hexcolor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color = stoi(hexcolor, nullptr, 16);
    SetConsoleTextAttribute(hConsole, color);
}
// ------------------- gotoxy function -------------
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// ------------------------------- cursor handling -------------------------------------------
void hideCursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(out, &cursorInfo);
}
void showCursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(out, &cursorInfo);
}
void setCursorSize(int size)
{
    if (size < 1)
        size = 1;
    if (size > 100)
        size = 100;
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.dwSize = size;
    SetConsoleCursorInfo(out, &cursorInfo);
}
