#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node* father;
    struct node* brother;
    struct node* son;
} node;

int main() {
    int number_of_trees = 0, amount_of_commands = 0, first_read_number;
    int i;
    node** forest;
    char command[4];

    scanf("%d %d", &number_of_trees, &amount_of_commands);

    forest = calloc(number_of_trees, sizeof(node*));

    for (i = 0 ; i < number_of_trees; ++i) {
        forest[i] = calloc(1, sizeof(node));
        forest[i]->data = i+1;
    }


    for (i = 0; i < amount_of_commands; ++i) {

        scanf("%s", command);
        scanf("%d", &first_read_number);

        if (command[1] == 'i') {
            int second_read_number;
            scanf("%d", &second_read_number);

            if (!forest[second_read_number-1]->son) {
                forest[second_read_number-1]->son = forest[first_read_number-1];
                forest[first_read_number-1]->father = forest[second_read_number-1];
            }
            else {
                node* auxiliar = forest[second_read_number-1]->son;
                while (auxiliar->brother) {
                    auxiliar = auxiliar->brother;
                }
                auxiliar->brother = forest[first_read_number-1];
                forest[first_read_number-1]->father = forest[second_read_number-1];
            }
        }

        else if (command[0] == 'l') {
            int second_read_number;
            scanf("%d", &second_read_number);
            if (first_read_number == second_read_number) {
                printf("%d\n", second_read_number);
            }
            else {
                if (!forest[first_read_number-1]->father) {
                    printf("%d\n", first_read_number);
                }
                else if (!forest[second_read_number-1]->father){
                    printf("%d\n", second_read_number);
                }
                else {
                    int size = 1;
                    node* percorrer = forest[first_read_number-1]->father;
                    while (percorrer) {
                        ++size;
                        percorrer = percorrer->father;
                    }
                    int* ancestor_of_first = malloc(size*sizeof(int));
                    percorrer = forest[first_read_number-1];
                    int k = 0;
                    while (percorrer) {
                        ancestor_of_first[k++] = percorrer->data;
                        percorrer = percorrer->father;
                    }
                    percorrer = forest[second_read_number-1];
                    char f = 0;
                    while (1) {
                        for (k = 0; k < size; ++k) {
                            if (percorrer->data == ancestor_of_first[k]){
                                printf("%d\n", ancestor_of_first[k]);
                                f = 1;
                                break;
                            }
                        }
                        if (f) {
                            break;
                        }
                        percorrer = percorrer->father;
                    }

                    free (ancestor_of_first);
                }
            }
        }
        else if (command[0] == 'c') {
            node* aux = forest[first_read_number-1]->father;
            if (aux->son->data == first_read_number) {
                if (!aux->son->brother) {
                    aux->son = NULL;
                }
                else {
                    aux->son = aux->son->brother;
                }
            } else {
                aux = aux->son;
                while (aux->brother->data != first_read_number) {
                    aux = aux->brother;
                }
                if (!aux->brother->brother) {
                    aux->brother = NULL;
                }
                else {
                    aux->brother = aux->brother->brother;
                }
            }
            forest[first_read_number-1]->father = NULL;
        }

    }


    return 0;
}