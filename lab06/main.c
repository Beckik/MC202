#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node;


node* search_parent (node* tree, int data) {
    if (!tree) { return NULL;}
    node* percorre = tree;
    while (percorre){
        if (data > percorre->data){
            tree = percorre;
            percorre = percorre->right;
        }
        else if (data < percorre->data){
            tree = percorre;
            percorre = percorre->left;
        }
        else if (percorre->data == data){
            return tree;
        }
    }
    return NULL;
}

int insert (node** root, int data) {

    if (!(*root)){
        *root = calloc(1,sizeof(node));
        if (!*root){
            return 0;
        }
        (*root)->data = data;
        return 1;
    }

    if ((*root)->data == data || search_parent(*root, data)) {
        return 69;
    }

    if (data > (*root)->data) {
        return (insert( &(*root)->right , data));
    }
    else if (data < (*root)->data) {
        return (insert( &(*root)->left , data));
    }
    else if ((*root)->data == data){
        return 1;
    }
    return 0;
}

void breadth (node* root, int depth, int* nodes_printed) {
    if (!root) {
        return;
    }
    if (!depth) {
        printf("%d ", root->data);
        ++nodes_printed[0];
    }
    else {
        breadth(root->left, depth-1, nodes_printed);
        breadth(root->right, depth-1, nodes_printed);
    }
}

void inorder_print (node* root) {
    if(root->left){
        inorder_print(root->left);
    }

    printf("%d ", root->data);

    if (root->right){
        inorder_print(root->right);
    }
}

void preorder_print (node* root) {
    if (!root) {
        return;
    }
    printf("%d ", root->data);

    if(root->left) {
        preorder_print(root->left);
    }
    if (root->right) {
        preorder_print(root->right);
    }
}

void postorder_print (node* root) {
    if (!root) {
        return;
    }
    if(root->left){
        postorder_print(root->left);
    }
    if (root->right){
        postorder_print(root->right);
    }
    printf("%d ", root->data);
}

int maximum (node* root) {
    int max = 0;
    while (root->right){
        max = root->data;
        root = root->right;
    }
    return max;
}

int minimum (node* root) {
    int min = 0;
    while (root->left){
        min = root->data;
        root= root->left;
    }
    return min;
}

void terminate (node* root) {
    if (!root) {
        return;
    }

    terminate(root->left);
    terminate(root->right);

    free (root);
}

int delete (node** tree, int data) {

    if (!*tree) {
        return 0;
    }

    if ((*tree)->data == data){
        if (!(*tree)->right && !(*tree)->left) {
            free(*tree);
            *tree = NULL;
            return 1;
        }
        else if (!(*tree)->right) {
            node* aux = *tree;
            *tree = (*tree)->left;
            free(aux);
            return 1;
        }
        else if (!(*tree)->left) {
            node* aux = *tree;
            *tree = (*tree)->right;
            free(aux);
            return 1;
        }

        else {
            node* successor_father = (*tree)->right;
            if (successor_father->left){
                node* aux = successor_father->left->left;
                while (aux) {
                    successor_father = successor_father->left;
                    aux =  aux->left;
                }

                aux = *tree;
                *tree = successor_father->left;
                successor_father->left->left = aux->left;
                successor_father->left = successor_father->left->right;
                (*tree)->right = aux->right;
                free(aux);
            }

            else {
                successor_father->left = (*tree)->left;
                node* aux = *tree;
                *tree = (*tree)->right;
                free(aux);
            }
            return 1;
        }

    }

    node* del_father = search_parent(*tree, data);
    if (!del_father) {
        return 0;
    }
    node* to_be_del;
    node** pointer;
    if (data > del_father->data){
        to_be_del = del_father->right;
        pointer = &del_father->right;
    }
    else {
        to_be_del = del_father->left;
        pointer = &del_father->left;
    }


    if (!to_be_del->left && !to_be_del->right) {
        free(to_be_del);
        *pointer = NULL;
        return 1;
    }
    else if (!to_be_del->left) {
        node* aux = *pointer;
        *pointer = to_be_del->right;
        free(aux);
        return 1;
    }

    else if (!to_be_del->right) {
        node* aux = to_be_del;
        *pointer = to_be_del->left;
        free(aux);
        return 1;
    }

    else {
        node* successor_father = to_be_del;
        node* aux = successor_father->right->left;
        if (aux) {
            successor_father = successor_father->right;
            aux = aux->left;
        }
        while (aux) {
            successor_father = successor_father->left;
            aux = aux->left;
        }

        if (to_be_del == successor_father) {
            aux = *pointer;
            *pointer = to_be_del->right;
            to_be_del->right->left = to_be_del->left;
            free(aux);
            return 1;
        }
        else {
            aux = *pointer;
            node* helper = successor_father->left->right;
            successor_father->left->right = to_be_del->right;
            *pointer = successor_father->left;
            successor_father->left->left = aux->left;
            successor_father->left = helper;
            free(aux);
            return 1;
        }
    }
}

int main() {
    char command[9];
    node* binary_search_tree = NULL;
    int data, amount_of_nodes = 0;

    while (scanf("%s", command)) {

        if (command[0] == 'i') {
            scanf("%d", &data);
            int what = insert(&binary_search_tree, data);
            if(!what) {
                printf("memoria insuficiente\n");
            }
            else if (what == 1){// há retorno diferente de 1, se retornar 69, "data" ja está na BST
                ++amount_of_nodes;
            }
        }

        else if (command[1] == 'm') {
            if (binary_search_tree) {
                inorder_print(binary_search_tree);
                printf("\n");
            } else {
                printf("vazia\n");
            }
        }

        else if (command[1] == 'r') {
            if (binary_search_tree) {
                preorder_print(binary_search_tree);
                printf("\n");
            } else {
                printf("vazia\n");
            }
        }

        else if(command[1] == 'o') {
            if (binary_search_tree) {
                postorder_print(binary_search_tree);
                printf("\n");
            } else {
                printf("vazia\n");
            }
        }

        else if (command[1] == 'x') {
            scanf("%d", &data);
            if (delete(&binary_search_tree, data)) {
                --amount_of_nodes;
            }
        }

        else if (command[1] == 'i') {
            binary_search_tree ? printf("%d", minimum(binary_search_tree)) : printf("vazia\n");
        }

        else if (command[0] == 'l') {

            if (!binary_search_tree) {
                printf("vazia\n");
            }

            else {
                int* nodes_printed = calloc(1, sizeof(int));
                printf("%d ", binary_search_tree->data);
                ++nodes_printed[0];
                int i = 1;
                for (; *nodes_printed < amount_of_nodes; ++i) {
                    breadth(binary_search_tree, i, nodes_printed);
                }
                printf("\n");
                free(nodes_printed);
            }
        }

        else if (command[1] == 'a') {
            binary_search_tree ? printf("%d", maximum(binary_search_tree)) : printf("vazia\n");
        }

        else if (command[0] == 'b') {
            scanf("%d", &data);
            printf(search_parent(binary_search_tree, data) ? "pertence\n" : "nao pertence\n");
        }

        else if (command[0] == 't') {
            if (binary_search_tree) {
                terminate(binary_search_tree);
                binary_search_tree = NULL;
            }
            return 0;
        }

    }
    return 0;
}
