#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    unsigned long key;
    int contagem;
} node;

unsigned long djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int hashing (unsigned long key, node hash_table[]) {
    int position = key % 6997;
    int aux = position;
    int i = 0;
    for (; i < 6997; ++i) {
        position = (aux + i*(1+(key%6995)))% 6997;
        if (!hash_table[position].key || hash_table[position].key == 1)
            return position;
    }
    return -1;
}

int search (unsigned long key, node hash_table[]) {
    int position = key % 6997;
    int aux = position;
    int i = 0;
    for (; i < 6997; ++i) {
        position = (aux + i*(1+(key%6995)))% 6997;
        if (hash_table[position].key == key)
            return position;
        else if (hash_table[position].key == 0)
            return -1;
    }
    return -1;
}

int main() {
    node* hash_table;
    char command;
    int position, count = 0;

    hash_table = calloc (6997, sizeof(node));

    while (scanf("%c", &command) && command != 'f' ) {
        unsigned char word_to_be_key[251];
        scanf("%s\n", word_to_be_key);

        unsigned long key = djb2(&word_to_be_key[0]);

        if (command == 'i') {
            if (search(key, hash_table) == -1) {
                position = hashing(key, hash_table);
                if (position != -1) {
                    hash_table[position].key = key;
                    hash_table[position].contagem = count++;
                }
            }
        }

        else if (command == 'b') {
            position = search(key, hash_table);
            if (position == -1)
                printf("nao encontrado\n");
            else
                printf("encontrado %d\n", hash_table[position].contagem);
        }

        else if (command == 'r') {
            position = search(key, hash_table);
            if (position != -1)
            hash_table[position].key = 1;
        }
    }
    return 0;
}