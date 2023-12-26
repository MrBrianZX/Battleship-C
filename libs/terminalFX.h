#include <inttypes.h>

#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define PURPLE 5
#define GRAY 8
#define BLACK 0
#define WHITE 15

/**
 * Esta funcion cambia el color de fondo de la consola
 *
 * @param bgColor  Color de fondo
 */
void setTerminalBackgroundColor(uint8_t color);

/**
 * Esta funcion cambia el color del texto de la consola
 *
 * @param Color Color de texto
 */
void setTerminalTextColor(uint8_t color);

/**
 * Esta funcion cambia el color de fondo y del texto de la consola
 *
 * @param bgColor  Color de fondo
 * @param txtColor Color de texto
 */
void setTerminalColor(uint8_t bgColor, uint8_t txtColor);

/**
 * Esta funcion reestablece el color de fondo y texto de la consola
 */
void clearTerminalColor();

// Pointer Position Functions
/**
 * Esta funcion mueve el puntero de la consola a la pocision (X,Y) tomando como referencia
 * la esquina superior izquierda como punto de origen.
 *
 * @param x Coordenada Horizontal
 * @param y Coordenada Vertical
 */
void setTerminalCoord(uint8_t x, uint8_t y);

/**
 * Esta funcion mueve el puntero de la consola a la pocision del origen (0,0)
 */
void setTerminalCoord11();

/**
 * Esta funcion limpia la consola
 */
void clearTerminal();

/**
 * This function prints all colors that are available
 */

void printColorPalette();
