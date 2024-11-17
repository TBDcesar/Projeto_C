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
Segmento fruta;
int comprimento = 4;        // Comprimento inicial da cobrinha
char direcao = 'd';          // Direção inicial: 'd' (direita)
int jogoEmExecucao = 0;      // Variável de controle para iniciar ou sair do jogo
int gameOver = 0;
int pontos = 0;

void exibirPontuacao() {
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(MINX, MINY - 2); // Exibe um pouco acima do campo de jogo
    printf("Pontuacao: %d", pontos);
}

void initializeSnake() {
    // Define a posição inicial da cabeça e do corpo da cobrinha
    for (int i = 0; i < comprimento; i++) {
        snake[i].x = 34 - i;  // Inicia com a cabeça na posição (34, 12) e o corpo à esquerda
        snake[i].y = 12;
    }
}

void gerarFruta(){
    fruta.x = MINX + 1 + rand() % (MAXX - MINX - 2);
    fruta.y = MINY + 1 + rand() % (MAXY - MINY - 2);
}

void drawFruit() {
    screenSetColor(RED, DARKGRAY);
    screenGotoxy(fruta.x, fruta.y);
    printf("@");
}

void marcandoPontos() {
    if (snake[0].x == fruta.x && snake[0].y == fruta.y) {
        pontos++;
        comprimento++;  // Aumenta o comprimento da cobrinha
        gerarFruta();
        drawFruit();  // Gera uma nova posição para a fruta
    }
}

void drawSnake() {
    screenSetColor(GREEN, DARKGRAY);
    
    // Desenha cada segmento da cobrinha
    for (int i = 0; i < comprimento; i++) {
        screenGotoxy(snake[i].x, snake[i].y);
        printf(i == 0 ? "O" : "0");  // Cabeça ("O") e corpo ("0")
    }
}

void clearTail() {
    // Apaga o último segmento da cobrinha
    screenGotoxy(snake[comprimento - 1].x, snake[comprimento - 1].y);
    printf(" ");
}

void moveSnake() {
    // Atualiza os segmentos da cobrinha, movendo cada um para a posição do anterior
    for (int i = comprimento - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // Move a cabeça da cobrinha na direção atual
    switch (direcao) {
        case 'w': snake[0].y -= 1; break; // Para cima
        case 's': snake[0].y += 1; break; // Para baixo
        case 'a': snake[0].x -= 1; break; // Para esquerda
        case 'd': snake[0].x += 1; break; // Para direita
    }
}

int colisaoCobra(){
    for (int i = 1; i < comprimento; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return 1;  // Colisão detectada
        }
    }
    return 0;
}

void exibirMenu() {
    screenClear();
    screenSetColor(YELLOW, DARKGRAY);

    screenGotoxy(20, 8);
    printf("============== Jogo da Cobrinha ==============");

    // Opções do menu
    screenGotoxy(25, 12);
    printf("1. Iniciar Jogo");
    screenGotoxy(25, 14);
    printf("2. Sair");
    screenGotoxy(25, 16);
    printf("Escolha uma opcao: ");
    screenUpdate();
}

int selecionarOpcaoMenu() {
    int opcao = 0;

    while (1) {
        if (keyhit()) {
            char ch = readch();
            if (ch == '1') {
                return 1;  // Iniciar jogo
            } else if (ch == '2') {
                return 2;  // Sair
            }
        }
    }
}

//void screenGameOver(){
    //screenClear();
    //screenSetColor(YELLOW, DARKGRAY);

    //screenGotoxy(20, 8);
    //printf("============== GAME OVER! ==============");

    //screenGotoxy(25, 12);
    //printf("1. Reiniciar o jogo?");
    //screenGotoxy(25, 14);
    //printf("2. Sair");
    //screenUpdate();
//}

//int opcaoGameOver(){
    //int opcao = 0;
    //if (keyhit()){
        //char ch = readch();
            //if (ch == '1') {
                //return 1;  // Reiniciar jogo
            //} else if (ch == '2') {
                //return 2;  // Sair
            //}
    //}    
//}

void iniciarJogo() {
    int ch = 0;
    gameOver = 0;
    pontos = 0;
    jogoEmExecucao = 1;
    initializeSnake();
    drawSnake();
    
    gerarFruta();
    drawFruit();
    screenUpdate();

    while (jogoEmExecucao && ch != 10) // Tecla Enter (10 = Enter)
    {
        if (snake[0].x <= MINX || snake[0].x >= MAXX || snake[0].y <= MINY || snake[0].y >= MAXY || colisaoCobra()) {
            gameOver = 1;  // Marca o jogo como encerrado
            break;
        }

        if (keyhit()) {
            ch = readch();
            // Muda a direção com base na tecla pressionada
            if ((ch == 'w' && direcao != 's') || (ch == 's' && direcao != 'w') || (ch == 'a' && direcao != 'd') || (ch == 'd' && direcao != 'a')) {
                direcao = ch;
            }
        }
        marcandoPontos();
        exibirPontuacao();
        clearTail();    // Apaga o último segmento
        moveSnake();    // Move a cobrinha na direção atual
        drawSnake();    // Redesenha a cobrinha
        screenUpdate(); // Atualiza a tela para refletir as mudanças
        usleep(100000);// Pausa para controlar a velocidade (100ms)
    }
}

int main() {

    exibirMenu();
    int opcao = selecionarOpcaoMenu();
    
    if (opcao == 1) {
        screenInit(1);
        keyboardInit();
        timerInit(50);
        iniciarJogo();
        screenUpdate();
        
    }
    if (gameOver){
        printf("Você Perdeu!");  
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}