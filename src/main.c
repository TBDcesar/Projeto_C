#include <string.h>
#include <stdlib.h>
#include <unistd.h> // Para usar a função usleep()

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define MAX_LENGTH 1000  // Comprimento máximo da cobrinha

typedef struct {
    int x, y;
} Segmento;

Segmento snake[MAX_LENGTH];  // Array para os segmentos da cobrinha
int comprimento = 10;             // Comprimento inicial da cobrinha
char direcao = 'd';       // Direção inicial: 'd' (direita)

void initializeSnake()
{
    // Define a posição inicial da cabeça e do corpo da cobrinha
    for (int i = 0; i < comprimento; i++) {
        snake[i].x = 34 - i;  // Inicia com a cabeça na posição (34, 12) e o corpo à esquerda
        snake[i].y = 12;
    }
}

void drawSnake()
{
    screenSetColor(CYAN, DARKGRAY);
    
    // Desenha cada segmentoo da cobrinha
    for (int i = 0; i < comprimento; i++) {
        screenGotoxy(snake[i].x, snake[i].y);
        printf(i == 0 ? "O" : "0");  // Cabeça ("O") e corpo ("0")
    }
}

void clearTail()
{
    // Apaga o último segmentoo da cobrinha
    screenGotoxy(snake[comprimento - 1].x, snake[comprimento - 1].y);
    printf(" ");
}

void moveSnake()
{
    // Atualiza os segmentos da cobrinha, movendo cada um para a posição do anterior
    for (int i = comprimento - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // Move a cabeça da cobrinha na direção atual
    switch (direcao) {
        case 'w':
         snake[0].y -= 1; break; // Para cima
        case 's':
         snake[0].y += 1; break; // Para baixo
        case 'a':
         snake[0].x -= 1; break; // Para esquerda
        case 'd':
         snake[0].x += 1; break; // Para direita
    }
}

int main() 
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);
    initializeSnake();
    drawSnake();
    screenUpdate();

    while (ch != 10) // Tecla Enter (10 = Enter)
    {
        if (snake[0].x <= MINX || snake[0].x >= MAXX || snake[0].y <= MINY || snake[0].y >= MAXY) {
            break;  // Encerra o jogo ao bater na borda
        }
        // Verifica se uma tecla foi pressionada
        if (keyhit()) 
        {
            ch = readch();
            // Muda a direção com base na tecla pressionada
            if ((ch == 'w') || (ch == 's') || (ch == 'a') || (ch =='d')) 
            {
                direcao = ch;
            }
        }

        clearTail();    // Apaga o último segmentoo
        moveSnake();    // Move a cobrinha na direção atual
        drawSnake();    // Redesenha a cobrinha
        screenUpdate(); // Atualiza a tela para refletir as mudanças
        usleep(100000); // Pausa para controlar a velocidade (100ms)
    }
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    

    return 0;
}
