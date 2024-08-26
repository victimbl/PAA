#ifndef HEAP_SORT_H
#define HEAP_SORT_H

// Função para trocar dois elementos
void swap_h(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Função para ajustar um heap para manter a propriedade do heap
void heapify(int arr[], int n, int i) {
    int largest = i; // Inicializa o maior como raiz
    int left = 2 * i + 1; // Filho à esquerda
    int right = 2 * i + 2; // Filho à direita

    // Se o filho à esquerda é maior que a raiz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Se o filho à direita é maior que o maior até agora
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Se o maior não é a raiz
    if (largest != i) {
        swap_h(&arr[i], &arr[largest]);

        // Recursivamente ajusta o sub-heap afetado
        heapify(arr, n, largest);
    }
}

// Função principal do Heap Sort
void heap_sort(int arr[], int tam) {
    // Constrói o heap (rearranja o array)
    for (int i = tam / 2 - 1; i >= 0; i--)
        heapify(arr, tam, i);

    // Um por um extrai um elemento do heap
    for (int i = tam - 1; i > 0; i--) {
        // Move a raiz atual para o final
        swap_h(&arr[0], &arr[i]);

        // Chama heapify na heap reduzida
        heapify(arr, i, 0);
    }
}

#endif