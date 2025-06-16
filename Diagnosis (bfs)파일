#include <stdio.h>
#include <stdlib.h>

#define DISEASE_COUNT 3
#define MAX_QUEUE_SIZE 1000

typedef struct {
    int diseases[DISEASE_COUNT]; // 질병 포함 여부 (0/1)
    int level;                   // 트리 깊이 (현재 선택한 질병 인덱스)
    double pD;                   // p(D') 확률
    double pSgivenD;             // p(S|D')
    double upper_bound;          // 상한 (우선순위 기준)
} Node;

// 사전확률 p(d_i)
double p_d[DISEASE_COUNT] = { 0.3, 0.1, 0.05 };

// p(S) - 증상 발생 확률 (가정)
double p_S = 0.4;

// p(S|d_i) 임의 가정
double pS_vals[DISEASE_COUNT] = { 0.6, 0.9, 0.5 };

// 큐를 위한 구조체
typedef struct {
    Node nodes[MAX_QUEUE_SIZE];
    int size;
} PriorityQueue;

void pq_init(PriorityQueue* pq) {
    pq->size = 0;
}

void pq_swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// 최대 힙(우선순위 큐) - 상한 기준으로 노드 정렬
void pq_push(PriorityQueue* pq, Node node) {
    if (pq->size >= MAX_QUEUE_SIZE) {
        printf("Queue overflow\n");
        return;
    }
    pq->nodes[pq->size] = node;
    int i = pq->size++;
    while (i > 0 && pq->nodes[(i - 1) / 2].upper_bound < pq->nodes[i].upper_bound) {
        pq_swap(&pq->nodes[(i - 1) / 2], &pq->nodes[i]);
        i = (i - 1) / 2;
    }
}

Node pq_pop(PriorityQueue* pq) {
    Node top = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    int i = 0;
    while (1) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < pq->size && pq->nodes[left].upper_bound > pq->nodes[largest].upper_bound) largest = left;
        if (right < pq->size && pq->nodes[right].upper_bound > pq->nodes[largest].upper_bound) largest = right;
        if (largest == i) break;
        pq_swap(&pq->nodes[i], &pq->nodes[largest]);
        i = largest;
    }
    return top;
}

// p(D') 계산 (독립 가정)
double calc_pD(int diseases[]) {
    double prob = 1.0;
    for (int i = 0; i < DISEASE_COUNT; i++) {
        if (diseases[i] == 1) prob *= p_d[i];
        else prob *= (1 - p_d[i]);
    }
    return prob;
}

// p(S|D') 계산: 포함된 질병 중 최대 p(S|d_i) 사용
double calc_pSgivenD(int diseases[]) {
    double max_pS = 0.0;
    for (int i = 0; i < DISEASE_COUNT; i++) {
        if (diseases[i] == 1 && pS_vals[i] > max_pS) {
            max_pS = pS_vals[i];
        }
    }
    return max_pS;
}

void print_node(Node node) {
    printf("Level %d, Diseases: {", node.level);
    for (int i = 0; i < DISEASE_COUNT; i++) {
        if (node.diseases[i] == 1) printf("d%d ", i + 1);
    }
    printf("} p(D')=%.5f p(S|D')=%.2f upper_bound=%.5f\n",
        node.pD, node.pSgivenD, node.upper_bound);
}

int main() {
    PriorityQueue pq;
    pq_init(&pq);

    // 초기 노드: 질병 없음, 레벨 0
    Node root = { {0,0,0}, 0, 0.0, 0.0, 0.0 };
    root.pD = calc_pD(root.diseases);
    root.pSgivenD = calc_pSgivenD(root.diseases);
    root.upper_bound = root.pD / p_S;  // 상한 계산

    pq_push(&pq, root);

    double best_solution = 0.0;

    while (pq.size > 0) {
        Node current = pq_pop(&pq);

        // 가지치기: 현재 상한이 최적해보다 작으면 무시
        if (current.upper_bound < best_solution) {
            continue;
        }

        // 최종 깊이 노드: p(D'|S) 계산 및 최적해 갱신
        if (current.level == DISEASE_COUNT) {
            double pDgivenS = (current.pSgivenD * current.pD) / p_S;
            if (pDgivenS > best_solution) {
                best_solution = pDgivenS;
                printf("New best solution found:\n");
                print_node(current);
                printf("p(D'|S) = %.5f\n\n", pDgivenS);
            }
            continue;
        }

        // 자식 노드 생성: 질병 포함하지 않음
        Node child0 = current;
        child0.level = current.level + 1;
        child0.diseases[current.level] = 0;
        child0.pD = calc_pD(child0.diseases);
        child0.pSgivenD = calc_pSgivenD(child0.diseases);
        child0.upper_bound = child0.pD / p_S;

        if (child0.upper_bound >= best_solution) {
            pq_push(&pq, child0);
        }

        // 자식 노드 생성: 질병 포함함
        Node child1 = current;
        child1.level = current.level + 1;
        child1.diseases[current.level] = 1;
        child1.pD = calc_pD(child1.diseases);
        child1.pSgivenD = calc_pSgivenD(child1.diseases);
        child1.upper_bound = child1.pD / p_S;

        if (child1.upper_bound >= best_solution) {
            pq_push(&pq, child1);
        }
    }

    printf("Best posterior probability p(D'|S) found: %.5f\n", best_solution);
    return 0;
}
