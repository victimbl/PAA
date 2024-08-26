#ifndef VETOR_H
#define VETOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para gerar um vetor com números aleatórios únicos entre 1 e n
void gerar_vetor_unico(int **vetor, int n) {
    // Aloca o vetor
    *vetor = (int *)malloc(n * sizeof(int));
    if (*vetor == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    // Cria um array auxiliar para verificar a unicidade
    int *aux = (int *)malloc(n * sizeof(int));
    if (aux == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    // Preenche o array auxiliar com números de 1 a n
    for (int i = 0; i < n; i++) {
        aux[i] = i + 1;
    }

    // Embaralha o array auxiliar
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        int temp = aux[i];
        aux[i] = aux[j];
        aux[j] = temp;
    }

    // Copia o array auxiliar para o vetor
    for (int i = 0; i < n; i++) {
        (*vetor)[i] = aux[i];
    }

    // Libera a memória do array auxiliar
    free(aux);
}

// Função para salvar o vetor em um arquivo
void salvar_vetor_em_arquivo(int *vetor, int n, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%d\n", vetor[i]);
    }

    fclose(arquivo);
    printf("Vetor salvo em %s\n", nome_arquivo);
}

#endif
