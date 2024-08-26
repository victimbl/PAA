#ifndef VETOR_H
#define VETOR_H

void vetor_alt(int **vetor, int tam) {
    // Aloca o vetor na memória
    *vetor = (int *)malloc(tam * sizeof(int));

    // Inicializa o gerador de números aleatórios com base no tempo atual
    srand(time(NULL));

    // Preenche o vetor com números aleatórios entre 0 e 65535
    for (int i = 0; i < tam; i++) {
        (*vetor)[i] = rand() % 65536; // rand() gera um número entre 0 e RAND_MAX, que é pelo menos 32767
    }
}

// Salvar vetor ordenado em um arquivo
void salvar_vetor_em_arquivo(int *vetor, int tam, const char *nome_arquivo, const char *algoritmo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < tam; i++) {
        fprintf(arquivo, "%d\n", vetor[i]);
    }
    
    fprintf(arquivo, "Vetor ordenado com o %s", algoritmo);
    fclose(arquivo);
    printf("Vetor salvo em %s\n", nome_arquivo);
}

#endif