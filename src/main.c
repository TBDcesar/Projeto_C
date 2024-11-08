#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12;      // Coordenadas iniciais
char direction = 'd';    // Direção inicial: 'd' (direita)

void printSnake(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("     "); // Apaga a posição anterior da cobrinha
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("0000O"); // Corpo da cobrinha atualizado
}

void moveMessage()
{
    switch (direction)
    {
        case 'w':  // Mover para cima
            if (y > MINY + 1) printSnake(x, y - 1);
            break;
        case 's':  // Mover para baixo
            if (y < MAXY - 1) printSnake(x, y + 1);
            break;
        case 'a':  // Mover para a esquerda
            if (x > MINX + 1) printSnake(x - 1, y); 
            break;
        case 'd':  // Mover para a direita
            if (x < MAXX - 5) printSnake(x + 1, y); // Ajusta para caber o comprimento da cobrinha
            break;
    }
}

int main() 
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);
    printSnake(x, y);
    screenUpdate();

    while (ch != 10) // Tecla Enter (10 = Enter)
    {
        // Verifica se uma tecla foi pressionada
        if (keyhit()) 
        {
            ch = readch();
            // Muda a direção com base na tecla pressionada
            if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') 
            {
                direction = ch;
            }
        }

        moveMessage();    // Move a cobrinha na direção atual
        screenUpdate();   // Atualiza a tela para refletir as mudanças
        usleep(100000);   // Pausa para controlar a velocidade (100ms)
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
