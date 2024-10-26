# 🐍 Jogo da cobrinha

Um jogo da cobrinha desenvolvido em C como um projeto acadêmico utilizando a biblioteca Clib. O objetivo é controlar a cobra e coletar a maior quantidade possível de pontos sem colidir com as paredes ou consigo mesma.

## 👥 Integrantes da Equipe

- Thomas Barlavento Duarte [@TBDcesar](https://github.com/TBDcesar)
- Lucas Bezerra Lima [@lblima038](https://github.com/lblima038)
- Arllesson Gomes da Silva [@arllekws](https://github.com/arllekws)

## 📜 Sobre o Projeto

Este projeto consiste em um jogo da cobrinha com jogabilidade simples e clássica. O jogador controla uma cobra em uma área de jogo e deve coletar frutas para aumentar seu tamanho e pontuação. O jogo termina quando a cobra colide com as bordas da tela ou com o próprio corpo.

### ✨ Funcionalidades

- 🕹️ Controle da cobra usando as setas do teclado.
- 🍎 A cobra cresce ao coletar frutas e aumenta a pontuação.
- 💥 Encerramento do jogo ao colidir com as bordas ou o próprio corpo.
<br>

# cli-lib
Command Line Interface library, for developing CLI applications and games in C. It has functions to access keyboard, screen and manage timing tasks.

## Requirements
- This library works with the follwing OS:
   - Linux based (Ubuntu, etc)
   - MacOS
- It is necessary to have GCC installed.

## Usage 
The file `main.c` has an example of how to use the Keyboard, Screen nd Timer functions. 

To build this example via command line, just switch to library root directory and type the following command:
```
$ gcc ./src/*.c -I./include -o cli-lib-example
```

To use this library to create your own apps, simply add source and header files to your project and compile it together with your own code, 
replacing the main.c file to your own.

