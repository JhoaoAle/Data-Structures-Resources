#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 10

typedef struct {
    int* array;      // index 0 unused
    size_t size;
    size_t capacity;
} Heap;

// ---------- Utility ----------

void resizeHeap(Heap* h, size_t newCapacity)
{
    int* newArray = realloc(h->array, (newCapacity + 1) * sizeof(int));
    if (!newArray) {
        printf("Reallocation failed\n");
        exit(1);
    }
    h->array = newArray;
    h->capacity = newCapacity;
}

// ---------- Heapify ----------

void maxHeapify(Heap* h, int index)
{
    int left = 2 * index;
    int right = 2 * index + 1;
    int largest = index;

    if (left <= h->size && h->array[left] > h->array[largest])
        largest = left;

    if (right <= h->size && h->array[right] > h->array[largest])
        largest = right;

    if (largest != index) {
        int temp = h->array[index];
        h->array[index] = h->array[largest];
        h->array[largest] = temp;

        maxHeapify(h, largest);
    }
}

// ---------- Creation ----------

// Empty heap
Heap* createEmptyHeap()
{
    Heap* h = malloc(sizeof(Heap));
    if (!h) exit(1);

    h->size = 0;
    h->capacity = INITIAL_CAPACITY;
    h->array = malloc((INITIAL_CAPACITY + 1) * sizeof(int));

    if (!h->array) exit(1);

    return h;
}

// Build heap from array
Heap* createHeap(int* numbers, size_t n)
{
    Heap* h = malloc(sizeof(Heap));
    if (!h) exit(1);

    h->size = n;
    h->capacity = (n > INITIAL_CAPACITY) ? n : INITIAL_CAPACITY;

    h->array = malloc((h->capacity + 1) * sizeof(int));
    if (!h->array) exit(1);

    // Copy input
    for (size_t i = 0; i < n; i++) {
        h->array[i + 1] = numbers[i];
    }

    // Build heap (bottom-up)
    for (int i = h->size / 2; i >= 1; i--) {
        maxHeapify(h, i);
    }

    return h;
}

// ---------- Insert ----------

void bubbleUp(Heap* h, int index)
{
    while (index > 1) {
        int parent = index / 2;

        if (h->array[parent] >= h->array[index])
            break;

        int temp = h->array[parent];
        h->array[parent] = h->array[index];
        h->array[index] = temp;

        index = parent;
    }
}

void insert(Heap* h, int value)
{
    if (h->size == h->capacity) {
        resizeHeap(h, h->capacity * 2);
    }

    h->size++;
    h->array[h->size] = value;
    bubbleUp(h, h->size);
}

// ---------- Extract ----------

int extractMax(Heap* h)
{
    if (h->size == 0) {
        printf("Heap is empty\n");
        return -999;
    }

    int max = h->array[1];

    h->array[1] = h->array[h->size];
    h->size--;

    maxHeapify(h, 1);

    // Optional shrink
    if (h->size > 0 && h->size <= h->capacity / 4) {
        resizeHeap(h, h->capacity / 2);
    }

    return max;
}

// ---------- Debug ----------

void printHeap(Heap* h)
{
    printf("Heap (size=%zu): ", h->size);
    for (size_t i = 1; i <= h->size; i++) {
        printf("%d ", h->array[i]);
    }
    printf("\n");
}

// ---------- Main ----------

int main()
{
    int inputArray[] = {1,2,3,4,5,6,7,8,9};
    size_t n = sizeof(inputArray) / sizeof(inputArray[0]);

    // Build from array
    Heap* h = createHeap(inputArray, n);

    printHeap(h);

    printf("Extract max: %d\n", extractMax(h));
    printHeap(h);

    printf("Insert 15\n");
    insert(h, 15);
    printHeap(h);

    printf("Extract max: %d\n", extractMax(h));
    printHeap(h);

    // Also demonstrate empty heap usage
    Heap* h2 = createEmptyHeap();
    insert(h2, 10);
    insert(h2, 20);
    insert(h2, 5);

    printf("\nSecond heap:\n");
    printHeap(h2);

    return 0;
}