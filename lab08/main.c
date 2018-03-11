#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int priority;
} node ;

void check (int key, int* aug, node* heap) {

    int now = aug[key], father = (now-1)/2;

    for (; father >= 0; father = (father-1)/2) {
        if (heap[now].priority < heap[father].priority) {
            int aux1 = heap[father].key, aux2 = heap[father].priority;
            heap[father].key = heap[now].key;
            heap[father].priority = heap[now].priority;
            heap[now].key = aux1;
            heap[now].priority = aux2;
            aux1 = aug[key];
            aug[key] = father;
            aug[heap[now].key] = aux1;
            now = (now-1)/2;
        }
        else if (heap[father].key == -69) {
            heap[father].key = heap[now].key;
            heap[father].priority = heap[now].priority;
            heap[now].key = -69;
            now = (now-1)/2;
        }
        else {
            break;
        }
    }
}

int main() {
    node* heap = NULL;
    int* aug = NULL, size, i, last = 0;
    char command;

    scanf("%d", &size);
    if (!size) {
        return 0;
    }

    heap = malloc(size*sizeof(node));
    aug = malloc(size*sizeof(int));

    for (i = 0; i < size; ++i) {
        heap[i].key = -69;
        aug[i] = -69;
    }

    while (scanf("\n%c", &command) && command != 't') {

        if (command == 'i') {
            int key, priority;
            scanf("%d %d", &key, &priority);
            if (key < size) {
                if (aug[key] == -69) {
                    if (last >= size) {
                        for (i = size - 1; i >= 0; --i) {
                            if (heap[i].key == -69) {
                                last = i;
                                break;
                            }
                        }
                    }
                    heap[last].priority = priority;
                    heap[last].key = key;
                    aug[key] = last++;
                    check(key, aug, heap);
                }
            }
        }

        else if (command == 'd') {
            int key, priority;
            scanf("%d %d", &key, &priority);
            heap[aug[key]].priority = priority;
            check(key, aug, heap);
        }

        else if (command == 'm') {
            if (heap[0].key != -69) {
                printf("minimo {%d,%d}\n", heap[0].key, heap[0].priority);

                aug[heap[0].key] = -69;
                heap[0].key = -69;

                int now = 0, left = 1, right = 2;

                while ((heap[left].key != -69 && left <= size-1) || (heap[right].key != -69 && right <= size-1)) {

                    if ((heap[left].key != -69 && heap[right].key == -69 ) || (heap[left].key != -69 && heap[right].key != -69 && heap[left].priority < heap[right].priority)) {
                        heap[now].key = heap[left].key;
                        heap[now].priority = heap[left].priority;
                        heap[left].key = -69;
                        now = left;
                        left = now*2+1;
                        right = now*2+2;
                    }
                    else {
                        heap[now].key = heap[right].key;
                        heap[now].priority = heap[right].priority;
                        heap[right].key = -69;
                        now = right;
                        left = now*2+1;
                        right = now*2+2;
                    }
                }
            }
            else {
                printf("vazio\n");
            }
        }
    }

    free(heap);
    free(aug);

    return 0;
}
