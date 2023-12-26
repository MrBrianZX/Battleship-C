#include "terminalFX.h"
#include <stdlib.h>
#include <stdio.h>

void clearTerminal()
{
    const char caClearScr[] = "\e[2J";
    printf("%s", caClearScr);
}

void setTerminalCoord(uint8_t x, uint8_t y)
{
    char escape_seq[16];
    snprintf(escape_seq, sizeof(escape_seq), "\x1B[%d;%dH", y, x);
    printf("%s", escape_seq);
}

void setTerminalCoord11()
{
    // Limpie un poco el arreglo de caracteres, los siguientes tres son equivalentes:
    // "\e[1;1H" == "\x1B[1;1H" == {27,'[','1',';','1','H'}
    setTerminalCoord(1, 1);
}

void setTerminalBackgroundColor(uint8_t color)
{
    char color_code[16];
    snprintf(color_code, sizeof(color_code), "\x1B[48;5;%dm", color);
    printf("%s", color_code);
}

void setTerminalTextColor(uint8_t color)
{
    char color_code[16];
    snprintf(color_code, sizeof(color_code), "\x1B[38;5;%dm", color);
    printf("%s", color_code);
}

void setTerminalColor(uint8_t bgColor, uint8_t txtColor)
{
    setTerminalBackgroundColor(bgColor);
    setTerminalTextColor(txtColor);
}

void clearTerminalColor()
{
    setTerminalBackgroundColor(0);
    setTerminalTextColor(255);
}

void printColorPalette()
{
    uint16_t i;
    for (i = 0; i < 256; i++)
    {
        setTerminalColor(255 - i, i);
        printf("%d,", i);
    }
}