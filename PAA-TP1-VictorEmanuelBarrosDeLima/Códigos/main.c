#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "vetor.h"

int main() {
    int *vetor;
    int tam, alg, ver_vetor;
    clock_t start, end;
    double tempo;
    const char *nome_alg = "";

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tam);
    if (tam > 100000000) {
        printf("O tamanho inserido é muito grande. Insira um valor entre 0 e 100000000.\n");
        exit(0);
    }

    printf("Escolha o metodo de ordenação: \n(1) Heap Sort\n(2) Merge Sort\n(3) Quick Sort\n");
    scanf("%d", &alg);

    printf("Deseja ver o vetor ordenado? (1 para sim, 0 para não): ");
    scanf("%d", &ver_vetor);

    vetor_alt(&vetor, tam);
    start = clock();

    switch (alg) {
        case 1:
            nome_alg = "Heap Sort";
            heap_sort(vetor, tam);
            printf("Vetor ordenado com o Heap Sort\n");
            break;
        case 2:
            nome_alg = "Merge Sort";
            merge_sort(vetor, 0, tam - 1);
            printf("Vetor ordenado com o Merge Sort\n");
            break;
        case 3:
            nome_alg = "Quick Sort";
            quick_sort(vetor, 0, tam - 1);
            printf("Vetor ordenado com o Quick Sort\n");
            break;
        default:
            printf("Metodo Inválido\n");
            exit(1);
    }

    end = clock();
    tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de ordenação: %f segundos\n", tempo);

    if (ver_vetor) {
        char nome_arquivo[50];
        sprintf(nome_arquivo, "vetor_ordenado.txt");
        salvar_vetor_em_arquivo(vetor, tam, nome_arquivo, nome_alg);
    }

    free(vetor);

    return 0;
}