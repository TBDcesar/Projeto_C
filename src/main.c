#include <string.h>
#include <stdlib.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12;  // Coordenadas iniciais

void printHello(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("     "); // Apaga a posição anterior da cobrinha
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("0000O"); // Corpo da cobrinha atualizado
}

void moveMessage(int ch)
{
    switch (ch)
    {
        case 'w':  // Move para cima
            if (y > MINY + 1) printHello(x, y - 1);
            break;
        case 's':  // Move para baixo
            if (y < MAXY - 1) printHello(x, y + 1);
            break;
        case 'a':  // Move para a esquerda
            if (x > MINX + 1) printHello(x - 1, y); 
            break;
        case 'd':  // Move para a direita
            if (x < MAXX - 5) printHello(x + 1, y); // Ajusta para caber o comprimento da cobrinha
            break;
    }
}

int main() 
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);
    printHello(x, y);
    screenUpdate();

    while (ch != 10) // Tecla Enter (10 = Enter)
    {
        // Verifica se uma tecla foi pressionada
        if (keyhit()) 
        {
            ch = readch();
            moveMessage(ch);  // Mover a cobrinha com as teclas WASD
            screenUpdate();  // Atualiza a tela para refletir as mudanças
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
