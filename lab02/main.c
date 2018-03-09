#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int id;
    int requisitions;
    struct no* prox;
}no;

int cost;
int* array_cost;
int length;

 no** search (no* lista, int id) {
     no** return_variable;

     return_variable = malloc(3*sizeof(no*));
     return_variable[1]= NULL;

     for (cost = 0;; lista = lista->prox) {
         if(lista->id == id){
             return_variable[0] = lista;
             return return_variable;
         }
         return_variable[2] = return_variable[1];
         return_variable[1] = lista;
         ++cost;
     }
 }

int move_to_front (no** lista, int id){
    if ((*lista)->id == id){
        return 1;
    }
    no** id_location = search(*lista, id);
    no* aux = id_location[0];
    id_location[1]->prox = id_location[0]->prox;
    id_location[0]->prox = *lista;
    *lista = aux;
    return cost + 1;
}

int transpose (no** lista, int id){
    if((*lista)->id == id){
        return 1;
    }
    no** id_location = search(*lista, id);
    if (id_location[2]) {
        no *aux = id_location[2]->prox;
        id_location[2]->prox = id_location[1]->prox;
        id_location[1]->prox = id_location[0]->prox;
        id_location[0]->prox = aux;
    }
    else {
        no* aux = *lista;
        *lista = id_location[0];
        id_location[1]->prox = id_location[0]->prox;
        id_location[0]->prox = aux;
    }
    return cost + 1;
}

int count (no** lista, int id){

    if (lista == NULL || *lista == NULL){
        return 0;
    }

    if ((*lista)->id == id){
        ++array_cost[0];
        ++(*lista)->requisitions;
        return 1;
    }

    if (((*lista)->prox)->id == id){
        if(array_cost[0] == array_cost[1] || array_cost[0] == array_cost[1]+1){
            no **ponteiro_aux2, **ponteiro_aux3;
            no* aux, *aux1, *aux2;
            ponteiro_aux2 = &((*lista)->prox);
            ponteiro_aux3 = &(((*lista)->prox)->prox);
            aux = *lista;
            aux1 = (*lista)->prox;
            aux2 = ((*lista)->prox)->prox;
            *lista = aux1;
            *ponteiro_aux2 = aux2;
            *ponteiro_aux3 = aux;
            ++(*lista)->requisitions;
            int auxt = array_cost[0];
            array_cost[0] = array_cost[1] + 1;
            array_cost[1] = auxt;
        }
        else {
            ++((*lista)->prox)->requisitions;
            ++array_cost[1];
        }
        return 2;
    }

    no** id_location = malloc(2*sizeof(no*));
    no** pre_id = lista;

    id_location[0] = *lista;

    int position = 0;

    for (cost = 0;id_location[0]; id_location[0] = id_location[0]->prox) {
        ++position;
        if (id_location[0]->id == id){
            break;
        }
        id_location[1] = id_location[0];
        ++cost;
    }

    ++array_cost[position-1];
    int flag = 0;
    no** aux = calloc(1,sizeof(no*));
    *aux = *pre_id;
    no** aux2 = calloc(1,sizeof(no*));
    *aux2 = *pre_id;

    int i = 0;
    for (;;*aux = (*aux)->prox) {
        ++i;
        if(array_cost[position-1] >= (*aux)->requisitions){
            break;
        }
        aux2 = &((*aux)->prox);
        flag = 1;
        if (*aux == NULL){
            return 0;
        }
    }

//    free(aux);
    aux = malloc(sizeof(no*));

    if(flag){
        pre_id = aux2;
    }

    *aux = *pre_id;
    *pre_id = id_location[1]->prox;
    id_location[1]->prox = id_location[0]->prox;
    ++id_location[0]->requisitions;
    id_location[0]->prox = *aux;

    int auxiliar;
    int j;
    if (i) {
        for (j = position - 1; j > i - 1; --j) {
            auxiliar = array_cost[j];
            array_cost[j] = array_cost[j - 1];
            array_cost[j - 1] = auxiliar;

        }
    }
    else {
        return 0;
    }
//    free (aux);
    return cost+1;
}

int main() {
    int requisitions, requested_id;
    int mtf_cost = 0, tr_cost = 0, c_cost = 0;
    int i;
    no* lista_mtf, *lista_tr, *lista_c;
    no* aux, *auxtr, *aux_c;

    scanf("%d", &length);
    scanf("%d", &requisitions);

    array_cost = calloc(length, sizeof(int));

    lista_mtf = calloc(1,sizeof(no));
    lista_mtf->id = 1;
    aux = lista_mtf;

    lista_tr = calloc(1,sizeof(no));
    lista_tr->id = 1;
    auxtr = lista_tr;

    lista_c = calloc(1,sizeof(no));
    lista_c->id = 1;
    aux_c = lista_c;

    for (i = 1; i < length; ++i) {
        aux->prox = calloc(1,sizeof(no));
        aux = aux->prox;
        aux->id = i+1;

        auxtr->prox = calloc(1,sizeof(no));
        auxtr = auxtr->prox;
        auxtr->id = i+1;

        aux_c->prox = calloc(1,sizeof(no));
        aux_c = aux_c->prox;
        aux_c->id = i+1;
    }

    i = 0;
    while (i < requisitions){
        scanf("%d", &requested_id);
        if(requested_id > length || requested_id < 1){
            return 0;
        }
        no** ponteiro = &lista_mtf;
        mtf_cost += move_to_front(ponteiro, requested_id);
        ponteiro = &lista_tr;
        tr_cost += transpose(ponteiro, requested_id);
        ponteiro = &lista_c;
        c_cost += count(ponteiro, requested_id);
        ++i;
    }

    printf("%d %d %d\n", mtf_cost, tr_cost, c_cost);

//    free(lista_c);
//    free(lista_mtf);
//    free(lista_tr);
//    free(aux);
//    free(aux_c);
//    free(auxtr);
    return 0;
}