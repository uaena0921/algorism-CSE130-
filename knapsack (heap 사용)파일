#include <stdio.h>
#include <stdlib.h>

#define MAX_ITEMS 100
#define MAX_HEAP 1000

typedef struct {
    int level;
    int profit;
    int weight;
    float bound;
} Node;

typedef struct {
    int weight;
    int profit;
    float ratio;
} Item;

int n = 4;
int W = 16;
Item items[MAX_ITEMS];

// ====== Heap (Max-Heap based on bound) ======
Node heap[MAX_HEAP];
int heap_size = 0;

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent].bound < heap[index].bound) {
            swap(&heap[parent], &heap[index]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapify_down(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap_size && heap[left].bound > heap[largest].bound)
        largest = left;
    if (right < heap_size && heap[right].bound > heap[largest].bound)
        largest = right;

    if (largest != index) {
        swap(&heap[index], &heap[largest]);
        heapify_down(largest);
    }
}

void push(Node node) {
    if (heap_size >= MAX_HEAP) return;
    heap[heap_size] = node;
    heapify_up(heap_size);
    heap_size++;
}

Node pop() {
    Node top = heap[0];
    heap[0] = heap[--heap_size];
    heapify_down(0);
    return top;
}

int is_empty() {
    return heap_size == 0;
}
// ============================================

int cmp(const void* a, const void* b) {
    Item* i = (Item*)a;
    Item* j = (Item*)b;
    return (j->ratio > i->ratio) - (j->ratio < i->ratio);
}

float bound(Node u) {
    if (u.weight >= W) return 0;
    float result = u.profit;
    int total_weight = u.weight;
    int i = u.level + 1;

    while (i < n && total_weight + items[i].weight <= W) {
        total_weight += items[i].weight;
        result += items[i].profit;
        i++;
    }

    if (i < n) {
        result += (W - total_weight) * items[i].ratio;
    }

    return result;
}

int knapsack() {
    Node u, v;
    int maxProfit = 0;

    v.level = -1;
    v.profit = 0;
    v.weight = 0;
    v.bound = bound(v);
    push(v);

    while (!is_empty()) {
        v = pop();
        if (v.bound <= maxProfit)
            continue;

        u.level = v.level + 1;

        // 포함하는 경우
        u.weight = v.weight + items[u.level].weight;
        u.profit = v.profit + items[u.level].profit;

        if (u.weight <= W && u.profit > maxProfit)
            maxProfit = u.profit;

        u.bound = bound(u);
        if (u.bound > maxProfit)
            push(u);

        // 포함하지 않는 경우
        u.weight = v.weight;
        u.profit = v.profit;
        u.bound = bound(u);
        if (u.bound > maxProfit)
            push(u);
    }

    return maxProfit;
}

int main() {
    int raw_weights[4] = {2, 5, 10, 5};
    int raw_profits[4] = {40, 30, 50, 10};

    for (int i = 0; i < n; i++) {
        items[i].weight = raw_weights[i];
        items[i].profit = raw_profits[i];
        items[i].ratio = (float)raw_profits[i] / raw_weights[i];
    }

    qsort(items, n, sizeof(Item), cmp);

    int maxProfit = knapsack();
    printf("최대 이익: %d\n", maxProfit);
    return 0;
}
