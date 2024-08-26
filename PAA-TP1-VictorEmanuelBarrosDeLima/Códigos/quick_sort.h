#ifndef QUICK_SORT_H
#define QUICK_SORT_H

// Função para trocar dois elementos
void swap_q(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Função para encontrar o índice do pivô
int partition(int *vetor, int low, int high) {
    int pivot = vetor[high]; // Pivô
    int i = (low - 1); // Índice do menor elemento

    for (int j = low; j <= high - 1; j++) {
        // Se o elemento atual é menor ou igual ao pivô
        if (vetor[j] <= pivot) {
            i++; // Incrementa o índice do menor elemento
            swap_q(&vetor[i], &vetor[j]);
        }
    }
    swap_q(&vetor[i + 1], &vetor[high]);
    return (i + 1);
}

// Função principal do Quick Sort
void quick_sort(int *vetor, int low, int high) {
    if (low < high) {
        // p é o índice do pivô, vetor[p] está agora no lugar certo
        int p = partition(vetor, low, high);

        // Separadamente ordena os elementos antes e depois do pivô
        quick_sort(vetor, low, p - 1);
        quick_sort(vetor, p + 1, high);
    }
}

#endif