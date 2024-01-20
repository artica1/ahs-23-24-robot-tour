#include <Arduino.h>
#include "maze.h"

#define MAX_TRIALS 10

// starting square = 1
// ending square = 2
// gates = 3
int zones[4][4] = {{0, 0, 0, 0},
                   {1, 1, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 2}};

int hwalls[3][4] = {{0, 0, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}};

int vwalls[4][3] = {{0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}};

bool DisplayArray()
{
    Serial.println("///////////");
    for (int i = 0; i <= 3; i++)
    {
        Serial.print("[ ");
        for (int j = 0; j <= 3; j++)
        {
            Serial.print(output[i][j]);
            Serial.print(" ");
        }
        Serial.println("]");
    }
    Serial.println("///////////");
    return true;
}

bool WaveExpansion()
{
    for (int find = 1; find <= MAX_TRIALS; find++)
    {
        for (int j = 0; j <= 3; i++)
        {
            for (int i = 0; i <= 3; j++)
            {
                if (output[j][i] == find)
                {
                    if (Expand(j, i, find + 1); == true)
                    {
                        return true;
                    }
                }
            }
        }
        delay(100); // this thing is too fast bruh
    }
}

bool CreateArrays(int starty, int startx, int finishy, int finishx)
{
    int prosessing[4][4] = {{0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0}};

    // don't touch
    // no walls = 0
    // left wall = 1
    // top wall = 2
    // left & top wall = 3
    int walls[4][4] = {{0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0}};

    for (int j = 0; j <= 3; j++)
    {
        for (int i = 0; i <= 3, j++)
        {
        }
    }
    // don't touch
    // none = 0
    // starting square = 1
    // ending square = 2
    // gate zones = 3 (ordered)
    int gates[4][4] = {{0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0}};

    gate[starty][startx] = 1;
    gate[finishy][finishx] = 2;
}

bool Expand(int y, int x, int setto)
{
    xmod = 1;
    ymod = 0;
    if (IsOutOfBounds(y + ymod, x + xmod) == false)
    {
        if (output[y + ymod][x + xmod] == 0)
        {
            output[y + ymod][x + xmod] = setto;
        }
        else if (output[y + ymod][x + xmod] == -1)
        {
            found = true;
        }
    }

    xmod = 0;
    ymod = 1;
    if (IsOutOfBounds(y + ymod, x + xmod) == false)
    {
        if (output[y + ymod][x + xmod] == 0)
        {
            output[y + ymod][x + xmod] = setto;
        }
        else if (output[y + ymod][x + xmod] == -1)
        {
            found = true;
        }
    }

    xmod = -1;
    ymod = 0;
    if (IsOutOfBounds(y + ymod, x + xmod) == false)
    {
        if (output[y + ymod][x + xmod] == 0)
        {
            output[y + ymod][x + xmod] = setto;
        }
        else if (output[y + ymod][x + xmod] == -1)
        {
            found = true;
        }
    }

    xmod = 0;
    ymod = -1;
    if (IsOutOfBounds(y + ymod, x + xmod) == false)
    {
        if (output[y + ymod][x + xmod] == 0)
        {
            output[y + ymod][x + xmod] = setto;
        }
        else if (output[y + ymod][x + xmod] == -1)
        {
            found = true;
        }
    }

    return found;
}

bool IsOutOfBounds(int y, int x)
{
    if (y >= 0 && y <= 3 && x >= 0 && x <= 3)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    delay(1000);

    Initialization();

    // initial display
    Serial.print(MAZE_startx);
    Serial.print(" ");
    Serial.println(MAZE_starty);

    Serial.print(MAZE_finishx);
    Serial.print(" ");
    Serial.println(finishy);

    DisplayArray();

    WaveExpansion();

    // Wave expansion
    nerd();
}

void nerd()
{
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⠤⠟⠛⠉⠉⠉⠁⠀⠀⠀⠀⠀⠈⠉⠉⠉⠑⠒⠢⠤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠔⠊⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⠢⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⠦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠖⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⣠⠎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⢀⡜⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠳⡀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⣠⠏⠀⠀⠀⢀⣀⣀⣤⣤⣤⣶⣶⣶⣶⣦⣤⣤⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⣤⣴⣶⣶⣶⣶⣤⣤⣤⣄⣀⡀⠀⠀⠀⠙⣄⠀⠀⠀⠀"));
    Serial.println(F("⠀⢀⣤⣴⣃⣀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣄⣈⣦⣤⡄⠀"));
    Serial.println(F("⠀⢀⣤⣴⣃⣀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣄⣈⣦⣤⡄⠀"));
    Serial.println(F("⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠛⠋⠉⠉⠉⠉⠉⠙⠛⠛⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠛⠋⠉⠉⠉⠉⠉⠙⠛⠛⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀"));
    Serial.println(F("⠀⢠⠏⠛⢿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣷⣄⠀⠙⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⢠⣶⣿⣿⣷⣦⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⡿⠟⠛⡅⠀"));
    Serial.println(F("⠀⡮⠀⠀⠀⢹⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⡆⠀⢸⣿⣿⣿⡿⠋⠉⠉⢻⣿⣿⣿⣿⠀⢀⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⡿⠀⠀⠀⢹⠀"));
    Serial.println(F("⣼⠃⠀⠀⠀⢸⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣧⠀⣾⣿⣿⣿⠃⠀⠀⠀⠀⣿⣿⣿⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⡇⠀⠀⠀⠀⡇"));
    Serial.println(F("⡏⠀⠀⠀⠀⠀⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⡏⠀⣿⣿⣿⣿⠀⠀⠀⠀⠀⢻⣿⣿⣿⡆⢸⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⠃⠀⠀⠀⠀⠘"));
    Serial.println(F("⡇⠀⠀⠀⠀⠀⢹⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⡿⠁⣼⣿⣿⣿⡇⠀⠀⠀⠀⠀⠘⣿⣿⣿⣷⠀⢿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⡿⠀⠀⠀⠀⠀⢰"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⣆⡀⠀⠀⠀⠀⠀⠈⠛⠿⠿⠛⣡⣼⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣷⣄⡙⠿⠿⠟⠋⠀⠀⠀⠀⠀⢀⣠⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⣿⣿⣶⣶⣶⣤⣤⣴⣶⣾⣿⣿⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣷⣶⣶⣤⣤⣶⣶⣶⣿⣿⣿⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸"));
    Serial.println(F("⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸"));
    Serial.println(F("⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇"));
    Serial.println(F("⠈⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠀"));
    Serial.println(F("⠀⠘⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣿⣷⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢨⠃⠀"));
    Serial.println(F("⠀⠀⠹⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣷⣶⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⣶⣾⣿⣿⣿⣿⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠏⠀⠀"));
    Serial.println(F("⠀⠀⠀⠹⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⡿⢿⣿⣿⣷⣶⣶⣶⣶⣶⣾⣿⣿⡿⢿⣿⣿⣿⣿⣿⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠎⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠘⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠿⣿⣿⡇⠀⠀⠀⠈⠉⢹⣿⡏⠉⠁⠀⠀⠀⢸⣿⣿⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠋⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠈⢣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⣷⣤⠀⠀⠀⠀⢸⣿⣇⠀⠀⠀⠀⣤⣾⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠁⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠙⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡏⠀⠀⠀⠀⣿⣿⣿⡄⠀⠀⠀⢹⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠋⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠒⠤⠤⠾⠛⠛⠛⠳⠤⠤⠒⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⠢⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡠⠴⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"));
    Serial.println(F("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⣑⣒⣤⡤⢀⣀⣀⣀⠀⠀⠀⠀⠀⢀⣀⣀⣀⢤⣤⣞⣚⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"));
}

void loop()
{
    // put your main code here, to run repeatedly:
}