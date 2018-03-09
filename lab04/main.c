// SIM EU USEI UMA SEQUÊNCIA CIRCULAR EM UM VETOR DINÂMICO
// Oi, Jorge, tudo bom? Me acompanha que eu vou comentar as partes que valem ponto extra.
#include <stdio.h>
#include <stdlib.h>

int main() {
    int capacity;

    while (scanf("%d", &capacity) && capacity){

        if (capacity == 1){
            printf("Cartas jogadas:\n");
            printf("Carta restante: 1\n");
        }
        else if (capacity == 2){
            printf("Cartas jogadas: 1\n");
            printf("Carta restante: 2\n");
        }

        else {
            int* deck;
            deck = malloc(capacity * sizeof(int));
            int i;
            for (i = 0; i < capacity; ++i) {
                deck[i] = i + 1;
            }

            printf("Cartas jogadas: 1");
            deck[0] = 2;
            deck[1] = 0;
            int ini = 2;
            int fim = 1;

            int length = capacity-1;
            for (--i; i > 0; --i) {
				//Aqui eu vejo se a quatidade de cartas (length), é metade ou menor
            	// que a o tamanho do vetor (capacity). Se for, eu crio um vetor novo
            	// new_deck com metade de capacity e vou passando os valores não nulos para ele.
                if (length <= capacity/2){
                    int* new_deck = malloc((capacity/2)*sizeof(int));
                    int j = 0;
                    int k = 0;
                    for (; j < capacity; ++j, ++k) {
                        if(deck[j%capacity]) {
                            new_deck[k] = deck[j % capacity];
                        }
                        else {
                            --k;
                        }
                    }
                    // Ai eu dou free no deck e dou pra ele o novo deck
                    // capacity agora é quantidade de cartas
                    // o início da fila (ini) agora é no início do vetor
                    // e o fim é a posição depois do última carta, mas
                    // mas como capacity-1 é a última posição (e temos uma
                    // temos um sequência circular), o posição depois da 
                    // última (fim) é a zero |-->|0(ini)|1|2|3|4|5|6|fim--|
                    free(deck);
                    deck = new_deck;
                    capacity = length;
                    fim = 0;
                    ini = 0;
                }

                if (i == 2) {
                    printf(", %d\n", deck[ini]);
                    if (fim-1 < 0){
                        fim = ((fim-1)*(-1))%capacity;
                        printf("Carta restante: %d\n", deck[fim]);
                    }
                    else {
                        printf("Carta restante: %d\n", deck[(fim - 1) % capacity]);
                    }
                    break;
                }
                // Essa parte é legal, por que é aqui que é circular
                // imprimo a carta descartada e coloco zero onde ela tava
                printf(", %d", deck[ini]);
                deck[ini] = 0;
                // ai, eu pego a ultima posição e coloco a carta depois
                // de ini nela.
                deck[fim] = deck[(ini + 1) % capacity];
                // e coloco zero nela tbm por que acabei de tirar
                // a carta dela então não pode ter nada nessa posição 
                deck[(ini + 1) % capacity] = 0;
                // e atualizo o ini que se moveu duas casas
                // já que descartei uma carta e tirei a que vem depois
                ini = (ini + 2) % capacity;
                // e também movo fim em 1 por que chegou a carta de dpois de ini
                fim = (fim + 1) % capacity;
                --length;
                // e length diminui em 1 pq joguei uma carta fora
                // Tchau, abraços!
            }
        }
    }

    return 0;
}