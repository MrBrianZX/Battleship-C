#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include "libs/terminalFX.h"

#define elif else if

#define M_SIZE 10
#define S_SHIP_C 20
#define O_SHIP_C 10

#define DEATH -1
#define SEA 0
#define S_SHIP 1
#define V_SHIP 2
#define H_SHIP 3

#define P1_X_OFFSET 3
#define PX_Y_OFFSET 3
#define P2_X_OFFSET 40

int8_t tablero[2][M_SIZE][M_SIZE] = {0}; // 512 bytes
int8_t P1 = 30, P2 = 30;

void startScreen();
void initGameMatrix();
void printGameMatrix();
int8_t shoot(uint8_t x, uint8_t y, uint8_t player);

int main()
{
    int x = 1, y = 1;
    uint8_t result;
    clearTerminal();
    initGameMatrix();
    printGameMatrix();
    startScreen();

    while ((P1 > 0 && P2 > 0) && (x != 0 && y != 0))
    {
        setTerminalCoord(1, 20);
        setTerminalTextColor(PURPLE);
        printf("Ingrese la coordenada:");
        scanf("%d,%d", &x, &y);

        if (x == 0 && y == 0)
        {
            break;
        }
        result = shoot(x, y, 1);
        P2 = P2 - result;

        setTerminalCoord(1, 20);
        setTerminalColor(BLACK, BLACK);
        printf("                               ");

        if (result)
        {
            setTerminalCoord(1, 20);
            setTerminalTextColor(GREEN);
            printf("Disparo Exitoso!");
        }
        else
        {
            setTerminalCoord(1, 20);
            setTerminalTextColor(RED);
            printf("Disparo Fallido!");
        }

        printGameMatrix();
        getch();

        setTerminalCoord(1, 20);
        setTerminalColor(BLACK, BLACK);
        printf("                               ");

        setTerminalCoord(1, 20);
        setTerminalTextColor(YELLOW);
        printf("Turno Rival!");
        getch();

        x = rand() % M_SIZE;
        y = rand() % M_SIZE;

        result = shoot(x, y, 0);
        P1 = P1 - result;

        setTerminalCoord(1, 20);
        setTerminalColor(BLACK, BLACK);
        printf("                               ");

        if (result)
        {
            setTerminalCoord(1, 20);
            setTerminalTextColor(GREEN);
            printf("Disparo Exitoso!");
        }
        else
        {
            setTerminalCoord(1, 20);
            setTerminalTextColor(RED);
            printf("Disparo Fallido!");
        }
        printGameMatrix();
        getch();
    }

    if (!P1)
    {
        setTerminalCoord(1, 20);
        setTerminalColor(BLACK, BLACK);
        printf("                               ");
        setTerminalCoord(1, 20);
        setTerminalTextColor(GREEN);
        printf("Gano Jugador 2!");
    }
    elif (!P2)
    {
        setTerminalCoord(1, 20);
        setTerminalColor(BLACK, BLACK);
        printf("                               ");
        setTerminalCoord(1, 20);
        setTerminalTextColor(GREEN);
        printf("Gano Jugador 1!");
    }

    return 0;
}

void startScreen()
{
    setTerminalCoord(1, 22);
    setTerminalTextColor(RED);
    printf("Set coord to 0,0 to exit");
    setTerminalCoord(1, 23);
    setTerminalTextColor(YELLOW);
    printf("Version 1 \t");
    setTerminalTextColor(BLUE);
    printf("By Brian Soto :D");
    clearTerminalColor();
}

void initGameMatrix()
{
    srand(time(NULL)); // Initialization, should only be called once.
    int r;
    uint8_t x, y, hships;

    uint8_t ships = 20;
    while (ships > 0)
    {
        r = rand();
        x = (uint8_t)(r * 3 + 7) % (M_SIZE - 1) + 1;
        y = (uint8_t)(r * 2 + 5) % (M_SIZE - 1) + 1;

        if (tablero[0][y][x] == 0)
        {
            ships--;
            tablero[0][y][x] = S_SHIP;
        }
    }

    ships = rand() % O_SHIP_C;
    hships = O_SHIP_C - ships;

    while (ships > 0)
    {
        r = rand();
        x = (uint8_t)(r * 3 + 2) % (M_SIZE - 1) + 1;
        y = (uint8_t)(r * 2 + 6) % (M_SIZE - 1) + 1;

        if (tablero[0][y][x] == 0 && tablero[0][y - 1][x] == 0)
        {
            ships--;
            tablero[0][y][x] = H_SHIP;
            tablero[0][y - 1][x] = H_SHIP;
        }
        elif (tablero[0][y][x] == 0 && tablero[0][y + 1][x] == 0)
        {
            ships--;
            tablero[0][y][x] = H_SHIP;
            tablero[0][y + 1][x] = H_SHIP;
        }
    }

    ships = hships;
    while (ships > 0)
    {
        r = rand();
        x = (uint8_t)(r + 3) % (M_SIZE - 1) + 1;
        y = (uint8_t)(r + 9) % (M_SIZE - 1) + 1;

        if (tablero[0][y][x] == 0 && tablero[0][y][x - 1] == 0)
        {
            ships--;
            tablero[0][y][x] = V_SHIP;
            tablero[0][y][x - 1] = V_SHIP;
        }
        elif (tablero[0][y][x] == 0 && tablero[0][y][x + 1] == 0)
        {
            ships--;
            tablero[0][y][x] = V_SHIP;
            tablero[0][y][x + 1] = V_SHIP;
        }
    }

    ships = S_SHIP_C;
    while (ships > 0)
    {
        r = rand();
        x = (uint8_t)(r * 3 + 7) % (M_SIZE - 1) + 1;
        y = (uint8_t)(r * 2 + 5) % (M_SIZE - 1) + 1;

        if (tablero[1][y][x] == 0)
        {
            ships--;
            tablero[1][y][x] = S_SHIP;
        }
    }

    ships = rand() % O_SHIP_C;
    hships = O_SHIP_C - ships;

    while (ships > 0)
    {
        r = rand();
        x = (uint8_t)(r * 3 + 2) % (M_SIZE - 1) + 1;
        y = (uint8_t)(r * 2 + 6) % (M_SIZE - 1) + 1;

        if (tablero[1][y][x] == 0 && tablero[1][y - 1][x] == 0 && y > 0)
        {
            ships--;
            tablero[1][y][x] = H_SHIP;
            tablero[1][y - 1][x] = H_SHIP;
        }
        elif (tablero[1][y][x] == 0 && tablero[1][y + 1][x] == 0 && y < (M_SIZE - 1))
        {
            ships--;
            tablero[1][y][x] = H_SHIP;
            tablero[1][y + 1][x] = H_SHIP;
        }
    }

    ships = hships;
    while (ships > 0)
    {
        r = rand();
        x = (uint8_t)(r + 3) % (M_SIZE - 1) + 1;
        y = (uint8_t)(r + 9) % (M_SIZE - 1) + 1;

        if (tablero[1][y][x] == 0 && tablero[1][y][x - 1] == 0 && x > 0)
        {
            ships--;
            tablero[1][y][x] = V_SHIP;
            tablero[1][y][x - 1] = V_SHIP;
        }
        elif (tablero[1][y][x] == 0 && tablero[1][y][x + 1] == 0 && x < (M_SIZE - 1))
        {
            ships--;
            tablero[1][y][x] = V_SHIP;
            tablero[1][y][x + 1] = V_SHIP;
        }
    }
}

void printGameMatrix()
{
    uint8_t i, j;

    for (i = 0; i < M_SIZE; i++)
    {
        for (j = 0; j < M_SIZE; j++)
        {
            if (tablero[0][i][j] == SEA)
            {
                setTerminalColor(BLUE, BLUE);
                setTerminalCoord(P1_X_OFFSET + 2 * i, PX_Y_OFFSET + j);
                printf("0 ");
            }
            elif (tablero[0][i][j] == DEATH)
            {
                setTerminalColor(BLUE, RED);
                setTerminalCoord(P1_X_OFFSET + 2 * i, PX_Y_OFFSET + j);
                printf("X ");
            }
            elif (tablero[0][i][j] == S_SHIP)
            {
                setTerminalColor(BLUE, 119);
                setTerminalCoord(P1_X_OFFSET + 2 * i, PX_Y_OFFSET + j);
                printf("O ");
            }
            elif (tablero[0][i][j] == V_SHIP)
            {
                setTerminalColor(BLUE, 119);
                setTerminalCoord(P1_X_OFFSET + 2 * i, PX_Y_OFFSET + j);
                printf("||");
            }
            else
            {
                setTerminalColor(BLUE, 119);
                setTerminalCoord(P1_X_OFFSET + 2 * i, PX_Y_OFFSET + j);
                printf("==");
            }

            // Player 2 Conditions
            if (tablero[1][i][j] == -1)
            {
                setTerminalColor(BLUE, RED);
                setTerminalCoord(P2_X_OFFSET + 2 * i, PX_Y_OFFSET + j);
                printf("X ");
            }
            else
            {
                setTerminalColor(BLUE, BLUE);
                setTerminalCoord(P2_X_OFFSET + 2 * i, PX_Y_OFFSET + j);
                printf("0 ");
            }
        }
    }
    clearTerminalColor();
}

int8_t shoot(uint8_t x, uint8_t y, uint8_t player)
{
    uint8_t flag = 0;
    x--;
    y--;
    if (tablero[player][x][y] == S_SHIP)
    {
        tablero[player][x][y] = DEATH;
        flag = 1;
    }
    elif (tablero[player][x][y] == V_SHIP && tablero[player][x][y - 1] == V_SHIP && y > 0)
    {
        tablero[player][x][y] = DEATH;
        tablero[player][x][y - 1] = DEATH;
        flag = 1;
    }
    elif (tablero[player][x][y] == V_SHIP && tablero[player][x][y + 1] == V_SHIP && y < (M_SIZE - 1))
    {
        tablero[player][x][y] = DEATH;
        tablero[player][x][y + 1] = DEATH;
        flag = 1;
    }
    elif (tablero[player][x][y] == H_SHIP && tablero[player][x - 1][y] == H_SHIP && x > 0)
    {
        tablero[player][x][y] = DEATH;
        tablero[player][x - 1][y] = DEATH;
        flag = 1;
    }
    elif (tablero[player][x][y] == H_SHIP && tablero[player][x + 1][y] == H_SHIP && x < (M_SIZE - 1))
    {

        tablero[player][x][y] = DEATH;
        tablero[player][x + 1][y] = DEATH;
        flag = 1;
    }
    return flag;
}
