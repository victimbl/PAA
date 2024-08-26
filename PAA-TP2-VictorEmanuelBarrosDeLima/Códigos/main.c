#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "auxiliar.h"
#include "avl_tree.h"
#include "rb_tree.h"

int main() {
    int *vetor;
    int tam, escolha_arvore, numero_busca, numero_remocao;
    clock_t start, end;
    double tempo_insercao, tempo_busca, tempo_remocao;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);
    if (tam > 100000000) {
        printf("O tamanho inserido é muito grande. Insira um valor entre 0 e 100000000.\n");
        exit(0);
    }

    printf("Escolha o tipo de árvore: \n(1) AVL\n(2) Rubro-Negra\n");
    scanf("%d", &escolha_arvore);

    printf("Digite o número a ser buscado: ");
    scanf("%d", &numero_busca);

    printf("Digite o número a ser removido: ");
    scanf("%d", &numero_remocao);

    gerar_vetor_unico(&vetor, tam);

    AVLNode *avl_root = NULL;
    RBNode *rb_root = NULL;
    int arvore_criada = 0;

    // Medir o tempo de inserção
    start = clock();
    switch (escolha_arvore) {
        case 1:
            for (int i = 0; i < tam; i++) {
                avl_root = avl_insert(avl_root, vetor[i]);
                if (avl_root == NULL) {
                    printf("Erro ao inserir %d na AVL.\n", vetor[i]);
                    exit(1);
                }
            }
            arvore_criada = avl_root != NULL;
            break;
        case 2:
            for (int i = 0; i < tam; i++) {
                rb_insert(&rb_root, vetor[i]);
                if (rb_root == NULL) {
                    printf("Erro ao inserir %d na Rubro-Negra.\n", vetor[i]);
                    exit(1);
                }
            }
            arvore_criada = rb_root != NULL;
            break;
        default:
            printf("Escolha inválida.\n");
            exit(1);
    }
    end = clock();
    tempo_insercao = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (arvore_criada) {
        printf("A árvore foi criada com sucesso.\n");
    } else {
        printf("A árvore não foi criada.\n");
    }

    // Medir o tempo de busca
    int encontrado = 0;
    start = clock();
    switch (escolha_arvore) {
        case 1: {
            AVLNode *resultado = avl_search(avl_root, numero_busca);
            encontrado = resultado != NULL;
            break;
        }
        case 2: {
            RBNode *resultado = rb_search(rb_root, numero_busca);
            encontrado = resultado != NULL;
            break;
        }
    }
    end = clock();
    tempo_busca = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (encontrado) {
        printf("Número %d encontrado com sucesso.\n", numero_busca);
    } else {
        printf("Número %d não foi encontrado.\n", numero_busca);
    }

    // Medir o tempo de remoção
    int removido = 0;
    start = clock();
    switch (escolha_arvore) {
        case 1: {
            AVLNode *nodo_remocao = avl_search(avl_root, numero_remocao);
            if (nodo_remocao != NULL) {
                avl_root = avl_remove(avl_root, numero_remocao);
                removido = 1;
            } else {
                printf("Número %d não foi encontrado para remoção na AVL.\n", numero_remocao);
            }
            break;
        }
        case 2: {
            RBNode *nodo_remocao = rb_search(rb_root, numero_remocao);
            if (nodo_remocao != NULL) {
                rb_delete(&rb_root, nodo_remocao);
                removido = 1;
            } else {
                printf("Número %d não foi encontrado para remoção na Rubro-Negra.\n", numero_remocao);
            }
            break;
        }
    }
    end = clock();
    tempo_remocao = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (removido) {
        printf("Número %d removido com sucesso.\n", numero_remocao);
    }

    printf("Tempo de inserção: %f segundos\n", tempo_insercao);
    printf("Tempo de busca: %f segundos\n", tempo_busca);
    printf("Tempo de remoção: %f segundos\n", tempo_remocao);

    salvar_vetor_em_arquivo(vetor, tam, "arvore.txt");

    free(vetor);

    return 0;
}
