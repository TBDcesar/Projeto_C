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
    printf("        ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("-===o");
}

void moveMessage( int ch)
{
    switch (ch)
    {
        case 'w':  // Move up
            if (y > MINY + 1) printHello(x, y--);
            break;
        case 's':  // Move down
            if (y < MAXY - 1) printHello(x, y++);
            break;
        case 'a':  // Move left
            if (x > MINX + 1) printHello(x--, y); 
            break;
        case 'd':  // Move right
            if (x < MAXX - strlen("-===o") - 1) printHello(x++, y);  
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

    while (ch != 10) // Enter key (10 = Enter)
    {
        // Verifica se uma tecla foi pressionada
        if (keyhit()) 
        {
            ch = readch();
            //if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
            
                printHello(x, y--);
                moveMessage(ch);  // Mover a mensagem com as teclas WASD
                screenUpdate();  // Atualiza a tela para refletir as mudanças
            
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}