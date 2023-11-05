#include <iostream>
#include <math.h>

#ifndef movimentos_h
#define movimentos_h

void movimentoPersonagem(int *keyW, int *keyA, int *keyS, int *keyD, float *posX, float *posY, int velocidade) {

	//printf("W: %d\nA: %d\nS: %d\nD: %d", *keyW,*keyA,*keyS,*keyD);
    //Teste para a entrada de dados

    double normalizacao = sqrt(pow(*posX, 2) + pow(*posY, 2));
    double normaX = *posX / normalizacao;
    double normaY = *posY / normalizacao;
    if (*keyD && *keyS && !*keyA && !*keyW) {
        *posX += normaX * velocidade;
        *posY += normaY * velocidade;
    }
    else if (*keyD && *keyW && !*keyA && !*keyS) {
        *posX += normaX * velocidade;
        *posY -= normaY * velocidade;
    }
    else if (*keyA && *keyW && !*keyD && !*keyS) {
        *posX -= normaX * velocidade;
        *posY -= normaY * velocidade;
    }
    else if (*keyA && *keyS && !*keyD && !*keyW) {
        *posX -= normaX * velocidade;
        *posY += normaY * velocidade;
    }

    if (*keyD && !*keyA && !*keyW && !*keyS) {
        *posX += velocidade;
    }
    else if (*keyA && !*keyD && !*keyW && !*keyS) {
        *posX -= velocidade;
    }
    else if (*keyW && !*keyA && !*keyD && !*keyS) {
        *posY -= velocidade;
    }
    else if (*keyS && !*keyA && !*keyD&& !*keyW) {
        *posY += velocidade;
    }
}

#endif movimentos_h

