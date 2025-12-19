#include <iostream>
#include <windows.h>
#include <conio.h>
#include <climits>
#include <random>
#include <chrono>
using namespace std;

void moveok(int width, int height, int &px, int &py, string headingcolor, string enemycolor, string playercolor, int &ex1, int &ey1, int &ex2, int &ey2, int &ex3, int &ey3, int &enemy1Health, int &enemy2Health, int &enemy3Health, int &level, bool &level2reached, bool &level3reached, bool &enemy1moveright, bool &e2first, bool &enemy2movedown, bool &enemy2moveright, bool &e3first, bool &enemy3movedown, bool &enemy3moveright, int bullets[2][100], int enemybullets[2][100], bool &playerInvincible, int &score, string coincolor, int enemyfirecontrol, int &cx, int &cy, int &coinFrameIndex, unsigned int &lastCoinFrameTime, vector<string> &coinFrames, int health, int coinFrameDelay, CHAR_INFO savedBuffer[][25]);
// === menu functions ===
void Menu(int width, int height);
void printMaze(int width, int height, int score, int level, int health);
void Gameover(int width, int height);

// === pause function ===
bool pauseMenu(int width, int height, CHAR_INFO savedBuffer[][25]);
void saveRegion(int x, int y, int width, int height, CHAR_INFO savedBuffer[][25]);
void restoreRegion(int x, int y, int width, int height, CHAR_INFO savedBuffer[][25]);

// === coin functions ===
void movecoin(int &cx, int &cy, int &coinFrameIndex, unsigned int &lastCoinFrameTime, const vector<string> &coinFrames, int &score, int px, int py, int width, int height, string coincolor, string headingcolor, string enemycolor, int coinFrameDelay);
bool coinCollision(int cx, int cy, int px, int py);

// ========== firing functions =========
void fire(int &ex1, int &ey1, int &ex2, int &ey2, int &ex3, int &ey3, int &enemy1Health, int &enemy2Health, int &enemy3Health, int bullets[2][100]);
void printBullet(int x, int y, char symbol);
void eraseBullet(int x, int y);
void fireenemybullets(int &enemyfirecontrol, int height, int &health, int &px, int &py, string headingcolor, string enemycolor, int enemybullets[2][100], int ex1, int ey1, int ex2, int ey2, int ex3, int ey3, int width);
bool bulletCollisionwithplayer(int ex, int ey, int x, int y);
void eraseBullet(int x, int y);
bool bulletCollisionwithenemy(int ex, int ey, int x, int y);

// === Player Functions ===
void printPlayer(int px, int py, string enemycolor, string playercolor);
void erasePlayer(int px, int py);
bool playerCollision(int ex, int ey, int px, int py);
void handlePlayerMovementSlow(DWORD &lastMoveTime, int delay, int width, int height, int &px, int &py);
void respawnPlayerWithDelay(int delayMs, int width, int height, int &px, int &py, bool &playerInvincible, string enemycolor, string playercolor, int &ex1, int &ey1, int &ex2, int &ey2, int &ex3, int &ey3, int &enemy1Health, int &enemy2Health, int &enemy3Health, int &level, bool &level2reached, bool &level3reached, bool &enemy1moveright, bool &e2first, bool &enemy2movedown, bool &enemy2moveright, bool &e3first, bool &enemy3movedown, bool &enemy3moveright, int bullets[2][100], int &cx, int &cy, int &coinFrameIndex, unsigned int &lastCoinFrameTime, vector<string> &coinFrames, int &score, int coinFrameDelay, string coincolor, string headingcolor, int &health, int enemyfirecontrol, int enemybullets[2][100]);

// === Enemy Functions ===
void move_enemy(int width, int height, int &ex1, int &ey1, int &ex2, int &ey2, int &ex3, int &ey3, int &enemy1Health, int &enemy2Health, int &enemy3Health, int &level, bool &level2reached, bool &level3reached, bool &enemy1moveright, bool &e2first, bool &enemy2movedown, bool &enemy2moveright, bool &e3first, bool &enemy3movedown, bool &enemy3moveright, string headingcolor, string enemycolor, int &score, int &health);
void spawnEnemy2(int &ex2, int &ey2, bool &enemy2movedown, bool &enemy2moveright, bool &e2first);
void printEnemy(int ex, int ey);
void EraseEnemy(int ex, int ey);
void moveEnemy1(int width, int &ex1, int &ey1, bool &enemy1moveright);
void moveEnemy2(int width, int height, int &ex2, int &ey2, bool &enemy2movedown, bool &enemy2moveright, bool &e2first);
void moveEnemy3(int width, int height, int &ex3, int &ey3, bool &enemy3movedown, bool &enemy3moveright, bool &e3first);

// === Default functoins ===
void gotoxy(int x, int y);
void getconsolemeasures(int &width, int &height);
int random(int lower, int upper);
void setcolor(string color);
void hideCursor();
void showCursor();
void setCursorSize(int size);

// ========(++++++++++ Main Calling +++++++++++)=======
int main()
{
    int width, height;
    getconsolemeasures(width, height);

    // === varriables declaration ===
    CHAR_INFO savedBuffer[5][25];
    int px, py, x, y, health = 100, level = 1; // p for player --- e for enemy --- width/height of consle
    string headingcolor = "06", enemycolor = "03", coincolor = "02", playercolor = "05";
    bool level2reached = false, level3reached = false;
    // --------- enemy variables ----------
    int ex1 = 1, ey1 = 4, ex2 = width - 8, ey2 = 0, ex3 = width / 2 - 5, ey3 = 0, enemy1Health = 5, enemy2Health = 5, enemy3Health = 5;
    bool enemy1moveright = true, e2first = true, e3first = true, enemy2moveright = false, enemy3moveright = true, enemy2movedown = false, enemy3movedown = true, playerInvincible = false;
    // -------- coin veriables -------------
    int cx = 0, cy = 4, score = 0;
    vector<string> coinFrames = {"(+)", "(x)", "(*)", "(o)", "(0)"};
    int coinFrameIndex = 0;
    unsigned int lastCoinFrameTime = 0;
    const unsigned int coinFrameDelay = 120;
    // --------------- firing varibles --------------------
    int bullets[2][100], enemybullets[2][100], enemyfirecontrol = 0;

    // ======= main code ========
    hideCursor();
    setcolor(headingcolor);
    for (int i = 0; i < 100; i++)
    {
        enemybullets[0][i] = INT_MIN;
        enemybullets[1][i] = INT_MIN;
        bullets[0][i] = INT_MIN;
        bullets[1][i] = INT_MIN;
    }
    printMaze(width, height, score, level, health);
    Menu(width, height);
    // ---- all movement and game logic in one function ----
    moveok(width, height, px, py, headingcolor, enemycolor, playercolor, ex1, ey1, ex2, ey2, ex3, ey3, enemy1Health, enemy2Health, enemy3Health, level, level2reached, level3reached, enemy1moveright, e2first, enemy2movedown, enemy2moveright, e3first, enemy3movedown, enemy3moveright, bullets, enemybullets, playerInvincible, score, coincolor, enemyfirecontrol, cx, cy, coinFrameIndex, lastCoinFrameTime, coinFrames, health, coinFrameDelay, savedBuffer);
    return 0;
}

// ============================================================ header functions =================================================================================================
// --------------- maze printing -------------------
void printMaze(int width, int height, int score, int level, int health)
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
    cout << "Score : " << score;
    gotoxy(width - 15, 2);
    cout << "Level : " << level;
    gotoxy(3, 1);
    cout << "Health : " << health;
}
// ---------------- menu pringting when game starts --------------------
void Menu(int width, int height)
{
    gotoxy(width / 2 - 16, height / 2);
    cout << "Welcome to space Xtriver game.";
    Sleep(2000);
    gotoxy(width / 2 - 16, height / 2);
    cout << "                              ";
}

// ------------- game over printing -------------------------
void Gameover(int width, int height)
{
    gotoxy(width / 2 - 6, height / 2 - 1);
    cout << "Game Over.";
    Sleep(1000);
    system("07");
    system("cls");
}

// ======================================(++++++++++++++++++++++++++++ Enemy handling ++++++++++++++++++++++++++++++++++++)=======================================================
// ===================== Enemy 1 handlilng =======================================
// -------------- printing enemy 1 -------------------
void printEnemy(int ex, int ey)
{
    gotoxy(ex, ey + 1);
    cout << "(~~~~)";
    gotoxy(ex, ey + 2);
    cout << "|=||=|";
    gotoxy(ex, ey + 3);
    cout << "  \\/  ";
}

void EraseEnemy(int ex, int ey)
{
    gotoxy(ex, ey + 1);
    cout << "      ";
    gotoxy(ex, ey + 2);
    cout << "       ";
    gotoxy(ex, ey + 3);
    cout << "       ";
}

void moveEnemy1(int width, int &ex1, int &ey1, bool &enemy1moveright)
{
    if (enemy1moveright == true)
    {
        EraseEnemy(ex1, ey1);
        ex1++;
        printEnemy(ex1, ey1);
        if (ex1 == width - 8)
        {
            enemy1moveright = false;
        }
    }
    else
    {
        EraseEnemy(ex1, ey1);
        ex1--;
        printEnemy(ex1, ey1);
        if (ex1 == 1)
        {
            enemy1moveright = true;
        }
    }
}

// ------------ initial settings for first time printing enemy 2 ------------------
void spawnEnemy2(int &ex2, int &ey2, bool &enemy2movedown, bool &enemy2moveright, bool &e2first)
{
    ex2 = 1;
    ey2 = 8;
    enemy2movedown = true;
    enemy2moveright = true;
    e2first = false;
}

// -------------------- moving enemy 2 ----------------------
void moveEnemy2(int width, int height, int &ex2, int &ey2, bool &enemy2movedown, bool &enemy2moveright, bool &e2first)
{
    if (e2first)
        spawnEnemy2(ex2, ey2, enemy2movedown, enemy2moveright, e2first);
    if (enemy2movedown == true)
    {
        EraseEnemy(ex2, ey2);
        ey2++;
        if (enemy2moveright == true)
        {
            ex2++;
        }
        else
        {
            ex2--;
        }
        printEnemy(ex2, ey2);
        if (ey2 == height - 5)
        {
            enemy2movedown = false;
        }
    }
    else
    {
        EraseEnemy(ex2, ey2);
        ey2--;
        if (enemy2moveright == true)
        {
            ex2++;
        }
        else
        {
            ex2--;
        }
        printEnemy(ex2, ey2);
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

// ----------------- moving enemy 3 -------------------
void moveEnemy3(int width, int height, int &ex3, int &ey3, bool &enemy3movedown, bool &enemy3moveright, bool &e3first)
{
    if (e3first)
    {
        ex3 = width / 2;
        ey3 = 12;
        e3first = false;
    }
    if (enemy3movedown == true)
    {
        EraseEnemy(ex3, ey3);
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
        printEnemy(ex3, ey3);
    }
    else
    {
        EraseEnemy(ex3, ey3);
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
        printEnemy(ex3, ey3);
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
// --------------- moving all enemies in one function -----------------------
void move_enemy(int width, int height, int &ex1, int &ey1, int &ex2, int &ey2, int &ex3, int &ey3, int &enemy1Health, int &enemy2Health, int &enemy3Health, int &level, bool &level2reached, bool &level3reached, bool &enemy1moveright, bool &e2first, bool &enemy2movedown, bool &enemy2moveright, bool &e3first, bool &enemy3movedown, bool &enemy3moveright, string headingcolor, string enemycolor, int &score, int &health)
{
    if (enemy1Health <= 0 && enemy2Health <= 0 && enemy3Health <= 0)
    {
        system("cls");
        setcolor("02");
        printMaze(width, height, score, level, health);
        setcolor("04");
        gotoxy(width / 2 - 6, height / 2 - 1);
        cout << "You win.";
        Sleep(1000);
        system("cls");
        setcolor("07");
        showCursor();
        exit(0);
    }
    else if (enemy1Health <= 0 && enemy2Health <= 0 && enemy3Health == 5 && level == 2)
    {
        level = 3;
    }
    else if (enemy1Health <= 0 && enemy2Health == 5 && enemy3Health == 5 && level == 1)
    {
        level = 2;
    }
    if (level == 1)
    {
        moveEnemy1(width, ex1, ey1, enemy1moveright);
        level2reached = true;
    }
    else if (level == 2)
    {
        if (level2reached)
        {
            enemy1Health = 5;
            ex1 = 1;
            ey1 = 4;
            level2reached = false;
            enemy1moveright = true;
        }
        if (enemy1Health > 0)
            moveEnemy1(width, ex1, ey1, enemy1moveright);
        if (enemy2Health > 0)
            moveEnemy2(width, height, ex2, ey2, enemy2movedown, enemy2moveright, e2first);
        level3reached = true;
    }
    if (level == 3)
    {
        if (level3reached)
        {
            enemy1Health = 5;
            enemy2Health = 5;
            ex1 = 1;
            ey1 = 4;
            enemy1moveright = true;
            e2first = true;
            level3reached = false;
        }
        if (enemy1Health > 0)
            moveEnemy1(width, ex1, ey1, enemy1moveright);
        if (enemy2Health > 0)
            moveEnemy2(width, height, ex2, ey2, enemy2movedown, enemy2moveright, e2first);
        if (enemy3Health > 0)
            moveEnemy3(width, height, ex3, ey3, enemy3movedown, enemy3moveright, e3first);
    }
    gotoxy(width - 7, 2);
    setcolor(headingcolor);
    cout << level;
    setcolor(enemycolor);
}
// =================================(++++++++++++++++++++ Player functions ++++++++++++++++++++++++)===========================================
// ----------- printing player -------------
void printPlayer(int px, int py, string enemycolor, string playercolor)
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
// ------------------ erasing player ---------------------
void erasePlayer(int px, int py)
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
// --------------- checking player collision with enemy -------------------
bool playerCollision(int ex, int ey, int px, int py)
{
    int playerLeft = px + 1;
    int playerRight = px + 12;
    int playerTop = py - 8;
    int playerBottom = py - 3;

    int enemyLeft = ex;
    int enemyRight = ex + 7;
    int enemyTop = ey + 1;
    int enemyBottom = ey + 4;

    if (playerLeft < enemyRight && playerRight > enemyLeft && playerTop < enemyBottom && playerBottom > enemyTop)
    {
        return true;
    }
    return false;
}
// ---------------- respawn player afer collision with enemy -------------
void respawnPlayerWithDelay(int delayMs, int width, int height, int &px, int &py, bool &playerInvincible, string enemycolor, string playercolor, int &ex1, int &ey1, int &ex2, int &ey2, int &ex3, int &ey3, int &enemy1Health, int &enemy2Health, int &enemy3Health, int &level, bool &level2reached, bool &level3reached, bool &enemy1moveright, bool &e2first, bool &enemy2movedown, bool &enemy2moveright, bool &e3first, bool &enemy3movedown, bool &enemy3moveright, int bullets[2][100], int &cx, int &cy, int &coinFrameIndex, unsigned int &lastCoinFrameTime, vector<string> &coinFrames, int &score, int coinFrameDelay, string coincolor, string headingcolor, int &health, int enemyfirecontrol, int enemybullets[2][100])
{
    playerInvincible = true;

    erasePlayer(px, py);
    px = width / 2;
    py = height + 1;

    DWORD start = GetTickCount();
    DWORD lastMoveTime = GetTickCount();
    DWORD moveDelay = 5;

    while (GetTickCount() - start < delayMs)
    {
        move_enemy(width, height, ex1, ey1, ex2, ey2, ex3, ey3, enemy1Health, enemy2Health, enemy3Health, level, level2reached, level3reached, enemy1moveright, e2first, enemy2movedown, enemy2moveright, e3first, enemy3movedown, enemy3moveright, enemycolor, playercolor, score, health);
        movecoin(cx, cy, coinFrameIndex, lastCoinFrameTime, coinFrames, score, px, py, width, height, coincolor, headingcolor, enemycolor, coinFrameDelay);
        fire(ex1, ey1, ex2, ey2, ex3, ey3, enemy1Health, enemy2Health, enemy3Health, bullets);
        fireenemybullets(enemyfirecontrol, height, health, px, py, headingcolor, enemycolor, enemybullets, ex1, ey1, ex2, ey2, ex3, ey3, width);
        handlePlayerMovementSlow(lastMoveTime, moveDelay, width, height, px, py);

        if (((GetTickCount() / 200) % 2) == 0)
            printPlayer(px, py, enemycolor, playercolor);
        else
            erasePlayer(px, py);
        Sleep(150);
    }
    playerInvincible = false;
    printPlayer(px, py, enemycolor, playercolor);
}

// ------------------- handle movement of player in respawn in slow motion with blinking -------------------
void handlePlayerMovementSlow(DWORD &lastMoveTime, int delay, int width, int height, int &px, int &py)
{
    if (GetTickCount() - lastMoveTime < delay)
        return;
    bool moved = false;
    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && px < width - 15)
    {
        erasePlayer(px, py);
        px++;
        moved = true;
    }
    else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && px > 1)
    {
        erasePlayer(px, py);
        px--;
        moved = true;
    }
    else if ((GetAsyncKeyState(VK_UP) & 0x8000) && py > 12)
    {
        erasePlayer(px, py);
        py--;
        moved = true;
    }
    else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && py < height + 2)
    {
        erasePlayer(px, py);
        py++;
        moved = true;
    }
    if (moved)
        lastMoveTime = GetTickCount();
}

// ======================================(+++++++++++++++++++++ over all movement ++++++++++++++++++++++)============================================================
void moveok(int width, int height, int &px, int &py, string headingcolor, string enemycolor, string playercolor, int &ex1, int &ey1, int &ex2, int &ey2, int &ex3, int &ey3, int &enemy1Health, int &enemy2Health, int &enemy3Health, int &level, bool &level2reached, bool &level3reached, bool &enemy1moveright, bool &e2first, bool &enemy2movedown, bool &enemy2moveright, bool &e3first, bool &enemy3movedown, bool &enemy3moveright, int bullets[2][100], int enemybullets[2][100], bool &playerInvincible, int &score, string coincolor, int enemyfirecontrol, int &cx, int &cy, int &coinFrameIndex, unsigned int &lastCoinFrameTime, vector<string> &coinFrames, int health, int coinFrameDelay, CHAR_INFO savedBuffer[][25])
{
    px = width / 2;
    py = height + 1;
    printPlayer(px, py, enemycolor, playercolor);

    DWORD lastEnemyMove = GetTickCount();
    DWORD enemyDelay = 150;
    DWORD lastFireTime = 0;

    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            while (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
            }
            bool wantExit = pauseMenu(width, height, savedBuffer);
            if (wantExit)
            {
                setcolor("04");
                Gameover(width, height);
                setcolor("07");
                showCursor();
                exit(0);
            }
        }
        if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && px < width - 15)
        {
            erasePlayer(px, py);
            px++;
            printPlayer(px, py, enemycolor, playercolor);
        }
        else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && px > 1)
        {
            erasePlayer(px, py);
            px--;
            printPlayer(px, py, enemycolor, playercolor);
        }
        else if ((GetAsyncKeyState(VK_UP) & 0x8000) && py > 12)
        {
            erasePlayer(px, py);
            py--;
            printPlayer(px, py, enemycolor, playercolor);
        }
        else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && py < height + 2)
        {
            erasePlayer(px, py);
            py++;
            printPlayer(px, py, enemycolor, playercolor);
        }
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) &&
            GetTickCount() - lastFireTime > 150)
        {
            lastFireTime = GetTickCount();

            for (int i = 0; i < 100; i++)
            {
                if (bullets[0][i] == INT_MIN)
                {
                    bullets[0][i] = px + 7;
                    bullets[1][i] = py - 9;
                    printBullet(bullets[0][i], bullets[1][i], '.');
                    break;
                }
            }
        }
        if (enemyfirecontrol >= 10)
        {
            for (int e = 1; e <= 3; e++)
            {
                if (e == 1 && enemy1Health <= 0)
                    continue;
                if (e == 2 && (enemy2Health <= 0 || level < 2))
                    continue;
                if (e == 3 && (enemy3Health <= 0 || level < 3))
                    continue;

                for (int i = 0; i < 100; i++)
                {
                    if (enemybullets[0][i] == INT_MIN)
                    {
                        if (e == 1)
                        {
                            enemybullets[0][i] = ex1 + 3;
                            enemybullets[1][i] = ey1 + 3;
                        }
                        else if (e == 2)
                        {
                            enemybullets[0][i] = ex2 + 3;
                            enemybullets[1][i] = ey2 + 3;
                        }
                        else
                        {
                            enemybullets[0][i] = ex3 + 3;
                            enemybullets[1][i] = ey3 + 3;
                        }

                        printBullet(enemybullets[0][i], enemybullets[1][i], '|');
                        break;
                    }
                }
            }
            enemyfirecontrol = 0;
        }

        if (GetTickCount() - lastEnemyMove >= enemyDelay)
        {
            fire(ex1, ey1, ex2, ey2, ex3, ey3, enemy1Health, enemy2Health, enemy3Health, bullets);
            move_enemy(width, height, ex1, ey1, ex2, ey2, ex3, ey3, enemy1Health, enemy2Health, enemy3Health, level, level2reached, level3reached, enemy1moveright, e2first, enemy2movedown, enemy2moveright, e3first, enemy3movedown, enemy3moveright, headingcolor, enemycolor, score, health);
            movecoin(cx, cy, coinFrameIndex, lastCoinFrameTime, coinFrames, score, px, py, width, height, coincolor, headingcolor, enemycolor, coinFrameDelay);
            fire(ex1, ey1, ex2, ey2, ex3, ey3, enemy1Health, enemy2Health, enemy3Health, bullets);
            fireenemybullets(enemyfirecontrol, height, health, px, py, headingcolor, enemycolor, enemybullets, ex1, ey1, ex2, ey2, ex3, ey3, width);
            if (playerCollision(ex1, ey1, px, py) || playerCollision(ex2, ey2, px, py) || playerCollision(ex3, ey3, px, py))
            {
                setcolor(headingcolor);
                health -= 20;
                gotoxy(12, 1);
                cout << health << " ";
                if (health <= 0)
                {
                    setcolor("04");
                    Gameover(width, height);
                    setcolor("07");
                    exit(0);
                }
                respawnPlayerWithDelay(3000, width, height, px, py, playerInvincible, enemycolor, playercolor, ex1, ey1, ex2, ey2, ex3, ey3, enemy1Health, enemy2Health, enemy3Health, level, level2reached, level3reached, enemy1moveright, e2first, enemy2movedown, enemy2moveright, e3first, enemy3movedown, enemy3moveright, bullets, cx, cy, coinFrameIndex, lastCoinFrameTime, coinFrames, score, coinFrameDelay, coincolor, headingcolor, health, enemyfirecontrol, enemybullets);
            }
            lastEnemyMove = GetTickCount();
        }
        Sleep(20);
    }
}
// ===================================================== firing ======================================================================
// ------------ player firing ---------------------
void fire(int &ex1, int &ey1, int &ex2, int &ey2, int &ex3, int &ey3, int &enemy1Health, int &enemy2Health, int &enemy3Health, int bullets[2][100])
{
    for (int i = 0; i < 100; i++)
    {
        if (bullets[0][i] == INT_MIN)
            continue;
        eraseBullet(bullets[0][i], bullets[1][i]);
        bullets[1][i]--;
        if (bulletCollisionwithenemy(ex1, ey1, bullets[0][i], bullets[1][i]))
        {
            enemy1Health--;
            bullets[1][i] = 4;
            if (enemy1Health == 0)
            {
                EraseEnemy(ex1, ey1);
                ex1 = 0;
                ey1 = 0;
            }
        }
        else if (bulletCollisionwithenemy(ex2, ey2, bullets[0][i], bullets[1][i]))
        {
            enemy2Health--;
            bullets[1][i] = 4;
            if (enemy2Health == 0)
            {
                EraseEnemy(ex2, ey2);
                ex2 = 0;
                ey2 = 0;
            }
        }
        else if (bulletCollisionwithenemy(ex3, ey3, bullets[0][i], bullets[1][i]))
        {
            enemy3Health--;
            bullets[1][i] = 4;
            if (enemy3Health == 0)
            {
                EraseEnemy(ex3, ey3);
                ex3 = 0;
                ey3 = 0;
            }
        }
        if (bullets[1][i] <= 4)
        {
            for (int j = i; j < 99; j++)
            {
                bullets[0][j] = bullets[0][j + 1];
                bullets[1][j] = bullets[1][j + 1];
            }
            bullets[0][99] = INT_MIN;
            bullets[1][99] = INT_MIN;
            i--;
            continue;
        }
        printBullet(bullets[0][i], bullets[1][i], '.');
    }
}
// ---- print bullet ---------
void printBullet(int x, int y, char symbol)
{
    gotoxy(x, y);
    cout << symbol;
}
// ---------- erase bullet -----------
void eraseBullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}

// --------------- checking bullet collision with enemy -------------------
bool bulletCollisionwithenemy(int ex, int ey, int x, int y)
{
    int enemyLeft = ex;
    int enemyRight = ex + 7;
    int enemyTop = ey + 1;
    int enemyBottom = ey + 4;

    if (x < enemyRight && x > enemyLeft && y < enemyBottom && y > enemyTop)
    {
        return true;
    }
    return false;
}
// --------------- checking bullet collision with player -------------------
bool bulletCollisionwithplayer(int px, int py, int x, int y)
{
    if (x == INT_MIN || y == INT_MIN)
        return false;

    int playerLeft = px;
    int playerRight = px + 12;
    int playerTop = py - 8;
    int playerBottom = py - 5;

    return (x >= playerLeft && x <= playerRight &&
            y >= playerTop && y <= playerBottom);
}

//-------------------- enemy firing ---------------
void fireenemybullets(int &enemyfirecontrol, int height, int &health, int &px, int &py, string headingcolor, string enemycolor, int enemybullets[2][100], int ex1, int ey1, int ex2, int ey2, int ex3, int ey3, int width)
{
    for (int i = 0; i < 100; i++)
    {
        if (enemybullets[0][i] == INT_MIN)
            continue;
        eraseBullet(enemybullets[0][i], enemybullets[1][i]);
        enemybullets[1][i]++;
        if (bulletCollisionwithplayer(px, py, enemybullets[0][i], enemybullets[1][i]))
        {
            setcolor(headingcolor);
            health -= 10;
            gotoxy(12, 1);
            cout << health << " ";
            enemybullets[1][i] = height - 2;
            if (health <= 0)
            {
                setcolor("04");
                Gameover(width, height);
                setcolor("07");
                showCursor();
                exit(0);
            }
        }
        if (enemybullets[1][i] >= height - 2)
        {
            for (int j = i; j < 99; j++)
            {
                enemybullets[0][j] = enemybullets[0][j + 1];
                enemybullets[1][j] = enemybullets[1][j + 1];
            }
            enemybullets[0][99] = INT_MIN;
            enemybullets[1][99] = INT_MIN;
            i--;
            continue;
        }
        printBullet(enemybullets[0][i], enemybullets[1][i], '|');
    }
    enemyfirecontrol++;
}
// ======================================================= coin functions ============================================================
void movecoin(int &cx, int &cy, int &coinFrameIndex, unsigned int &lastCoinFrameTime, const vector<string> &coinFrames, int &score, int px, int py, int width, int height, string coincolor, string headingcolor, string enemycolor, int coinFrameDelay)
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
    if (coinCollision(cx, cy, px, py))
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
bool coinCollision(int cx, int cy, int px, int py)
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
bool pauseMenu(int width, int height, CHAR_INFO savedBuffer[][25])
{
    int bx = width / 2 - 10;
    int by = height / 2 - 2;
    int bw = 22;
    int bh = 5;
    saveRegion(bx, by, bw, bh, savedBuffer);

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
            while (GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
            }
            restoreRegion(bx, by, bw, bh, savedBuffer);
            return false;
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            while (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
            }
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
// ------------- saving region of pause menu to print after continue ----------------
void saveRegion(int x, int y, int width, int height, CHAR_INFO savedBuffer[][25])
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT readArea = {(SHORT)x, (SHORT)y, (SHORT)(x + width - 1), (SHORT)(y + height - 1)};
    COORD bufferSize = {(SHORT)width, (SHORT)height};
    COORD bufferCoord = {0, 0};

    ReadConsoleOutput(
        h,
        (CHAR_INFO *)savedBuffer, // store into buffer
        bufferSize,
        bufferCoord,
        &readArea);
}
// ---------------- again printing saved region after continuing game ----------------
void restoreRegion(int x, int y, int width, int height, CHAR_INFO savedBuffer[][25])
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT writeArea = {(SHORT)x, (SHORT)y, (SHORT)(x + width - 1), (SHORT)(y + height - 1)};
    COORD bufferSize = {(SHORT)width, (SHORT)height};
    COORD bufferCoord = {0, 0};

    WriteConsoleOutput(
        h,
        (CHAR_INFO *)savedBuffer,
        bufferSize,
        bufferCoord,
        &writeArea);
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
// --------------------- getting random number -------------
int random(int lower, int upper)
{
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_int_distribution<> dist(lower, upper);
    int randomNum = dist(gen);
    return randomNum;
}
// ----------------- getting console measures ------------------------
void getconsolemeasures(int &width, int &height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
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
