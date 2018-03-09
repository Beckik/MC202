#include <stdio.h>
#include <stdlib.h>

int main() {
    int* deck;
    int capacity;
    int i;

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
            deck = malloc(capacity * sizeof(int));

            for (i = 0; i < capacity; ++i) {
                deck[i] = i + 1;
            }


            printf("Cartas jogadas: 1");
            deck[0] = 2;
            deck[1] = 0;
            int ini = 2;
            int fim = 1;


            for (--i; i > 0; --i) {
                if (i == 2) {
                    printf(", %d\n", deck[ini]);
                    printf("Carta restante: %d\n", deck[fim - 1]);
                    break;
                }
                printf(", %d", deck[ini]);
                deck[fim] = deck[(ini + 1) % capacity];
                deck[ini] = 0;
                deck[(ini + 1) % capacity] = 0;
                ini = (ini + 2) % capacity;
                fim = (fim + 1) % capacity;
            }
        }
    }

    return 0;
}