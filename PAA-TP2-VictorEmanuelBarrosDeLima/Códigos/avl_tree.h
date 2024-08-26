#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>

// Definição do nó da árvore AVL
typedef struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Função para obter a altura de um nó
int avl_height(AVLNode *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Função para obter o valor máximo entre dois inteiros
int avl_max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó da árvore AVL
AVLNode* avl_create_node(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

// Função para rotacionar à direita a subárvore com raiz y
AVLNode *avl_right_rotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza as alturas
    y->height = avl_max(avl_height(y->left), avl_height(y->right)) + 1;
    x->height = avl_max(avl_height(x->left), avl_height(x->right)) + 1;

    // Retorna a nova raiz
    return x;
}

// Função para rotacionar à esquerda a subárvore com raiz x
AVLNode *avl_left_rotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza as alturas
    x->height = avl_max(avl_height(x->left), avl_height(x->right)) + 1;
    y->height = avl_max(avl_height(y->left), avl_height(y->right)) + 1;

    // Retorna a nova raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó
int avl_get_balance(AVLNode *N) {
    if (N == NULL)
        return 0;
    return avl_height(N->left) - avl_height(N->right);
}

// Função para inserir um novo nó na árvore AVL
AVLNode* avl_insert(AVLNode* node, int key) {
    // 1. Realiza a inserção normal de BST
    if (node == NULL)
        return(avl_create_node(key));

    if (key < node->key)
        node->left = avl_insert(node->left, key);
    else if (key > node->key)
        node->right = avl_insert(node->right, key);
    else // Chaves iguais não são permitidas em BST
        return node;

    // 2. Atualiza a altura deste nó ancestral
    node->height = 1 + avl_max(avl_height(node->left), avl_height(node->right));

    // 3. Obtém o fator de balanceamento deste nó ancestral
    int balance = avl_get_balance(node);

    // 4. Se o nó ficar desbalanceado, então existem 4 casos

    // Caso Esquerda Esquerda
    if (balance > 1 && key < node->left->key)
        return avl_right_rotate(node);

    // Caso Direita Direita
    if (balance < -1 && key > node->right->key)
        return avl_left_rotate(node);

    // Caso Esquerda Direita
    if (balance > 1 && key > node->left->key) {
        node->left = avl_left_rotate(node->left);
        return avl_right_rotate(node);
    }

    // Caso Direita Esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = avl_right_rotate(node->right);
        return avl_left_rotate(node);
    }

    return node;
}

// Função para realizar percurso in-order na árvore AVL
void avl_inorder(AVLNode *root) {
    if (root != NULL) {
        avl_inorder(root->left);
        printf("%d ", root->key);
        avl_inorder(root->right);
    }
}

// Função para buscar um nó na árvore AVL
AVLNode* avl_search(AVLNode* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return avl_search(root->left, key);

    return avl_search(root->right, key);
}

// Função para encontrar o nó com o menor valor
AVLNode* avl_min_value_node(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Função para remover um nó na árvore AVL
AVLNode* avl_remove(AVLNode* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key) {
        root->left = avl_remove(root->left, key);
    } else if (key > root->key) {
        root->right = avl_remove(root->right, key);
    } else {
        if (root->left == NULL) {
            AVLNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            AVLNode* temp = root->left;
            free(root);
            return temp;
        }

        AVLNode* temp = avl_min_value_node(root->right);
        root->key = temp->key;
        root->right = avl_remove(root->right, temp->key);
    }

    if (root == NULL)
        return root;

    root->height = 1 + (avl_height(root->left) > avl_height(root->right) ? avl_height(root->left) : avl_height(root->right));
    int balance = avl_get_balance(root);

    if (balance > 1 && avl_get_balance(root->left) >= 0)
        return avl_right_rotate(root);

    if (balance > 1 && avl_get_balance(root->left) < 0) {
        root->left = avl_left_rotate(root->left);
        return avl_right_rotate(root);
    }

    if (balance < -1 && avl_get_balance(root->right) <= 0)
        return avl_left_rotate(root);

    if (balance < -1 && avl_get_balance(root->right) > 0) {
        root->right = avl_right_rotate(root->right);
        return avl_left_rotate(root);
    }

    return root;
}

#endif
