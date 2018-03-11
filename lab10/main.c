#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int partition (int* array, int begin, int end) {
    int pivot = array[end];

    while (begin < end){
        while (begin < end && array[begin] <= pivot)
            ++begin;
        while (begin < end && array[end] > pivot)
            --end;
        int aux = array[begin];
        array[begin] = array[end];
        array[end] = aux;
    }
    return begin;
}

void quick_sort (int* array, int begin, int end) {
    if (begin < end ){
        int position = partition(array, begin, end);
        quick_sort(array, begin, position-1);
        quick_sort(array, position, end);
    }
}

void insertionSort(int array[], int size) {
    int i, j, now;
    for (i = 1; i < size; i++) {
        now = array[i];

        for (j = i - 1; (j >= 0) && (now < array[j]); j--) {
            array[j + 1] = array[j];
        }
        array[j+1] = now;
    }
}

void bubble_sort (int* array, int size) {
    int i, j;
    for (i = size-1; i > 0; --i) {
        for (j = 0; j < i; ++j) {
            if (array[j] > array[j+1]){
                int aux = array[j];
                array[j] = array[j+1];
                array[j+1] = aux;
            }
        }
    }
}

void selection_sort(int array[], int size) {
    int i, j, min, aux;
    for (i = 0; i < (size-1); i++)
    {
        min = i;
        for (j = (i+1); j < size; j++) {
            if(array[j] < array[min])
                min = j;
        }
        if (array[i] != array[min]) {
            aux = array[i];
            array[i] = array[min];
            array[min] = aux;
        }
    }
}

int main() {
    double mediabubble[2], mediaselection[2], mediainsertion[2];
    int size;
    scanf("%d", &size);

    for (int j = 0; j < 2; ++j) {
        int *bubbleArray, *insertionArray, *selectionArray;
        time_t init, end;
        double time_span;

        bubbleArray = malloc(size * sizeof(int));
        insertionArray = malloc(size * sizeof(int));
        selectionArray = malloc(size * sizeof(int));

        printf("Teste de tamanho %d vez %d\n", size, j);

        for (unsigned int i = 0; i < size; ++i) {
            srand((unsigned) (i + time(NULL)));
            bubbleArray[i] = rand();
            insertionArray[i] = bubbleArray[i];
            selectionArray[i] = bubbleArray[i];
        }
        printf("vetores criados\n");

        init = time(NULL);
        bubble_sort(bubbleArray, size);
        end = time(NULL);
        time_span = difftime(end, init);
        printf("Bubble levou %lf segundos\n", time_span);
        mediabubble[j]= time_span;

        init = time(NULL);
        selection_sort(selectionArray, size);
        end = time(NULL);
        time_span = difftime(end, init);
        printf("Selection levou %lf segundos\n", time_span);
        mediaselection[j]= time_span;

        init = time(NULL);
        insertionSort(insertionArray, size);
        end = time(NULL);
        time_span = difftime(end, init);
        printf("Insertion levou %lf segundos\n", time_span);
        mediainsertion[j]= time_span;
    }

    double fimB = 0, fimI = 0, fimS = 0;
    for (int k = 0; k < 2; ++k) {
        fimB += mediabubble[k];
        fimI += mediainsertion[k];
        fimS += mediaselection[k];
    }
    fimB /= 2;
    fimS /= 2;
    fimI /= 2;

    printf("media bubble: %lf\nmedia selection: %lf\nmedia insertion %lf\n",fimB, fimS,fimI);
    return 0;
}