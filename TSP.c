#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 10  // 도시 최대 개수

int n;           // 도시 개수
int W[MAX][MAX]; // 비용 행렬 (거리)

// 우선순위 큐(힙)를 위한 노드 구조체
typedef struct Node {
    int level;          // 방문한 도시 수
    int path[MAX];      // 현재 경로
    int visited[MAX];   // 방문 여부
    int cost;           // 현재까지 경로 비용
    int bound;          // 비용의 하한 (lower bound)
} Node;

Node* heap[1000];   // 최소 힙 배열
int heap_size = 0;
int best_cost = INT_MAX;
int best_path[MAX];

// 힙에 노드 삽입
void push(Node* node) {
    int i = ++heap_size;
    while (i > 1 && node->bound < heap[i/2]->bound) {
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = node;
}

// 힙에서 최소 bound 노드 추출
Node* pop() {
    Node* min_node = heap[1];
    Node* last = heap[heap_size--];
    int parent = 1, child = 2;

    while (child <= heap_size) {
        if (child < heap_size && heap[child]->bound > heap[child+1]->bound)
            child++;
        if (last->bound <= heap[child]->bound) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = last;
    return min_node;
}

// bound 계산 함수 (현재 상태에서 앞으로 필요한 최소 추가 비용 계산)
int bound(Node* node) {
    int bound_cost = node->cost;
    int min_edge;
    int last = node->path[node->level];

    // 아직 방문하지 않은 도시 중에서 최소 비용 간선 더하기 (대략적인 하한)
    for (int i = 0; i < n; i++) {
        if (!node->visited[i]) {
            min_edge = INT_MAX;
            for (int j = 0; j < n; j++) {
                if (i != j && (!node->visited[j] || j == 0)) { 
                    if (W[i][j] < min_edge) min_edge = W[i][j];
                }
            }
            bound_cost += min_edge;
        }
    }
    return bound_cost;
}

void print_solution(int path[], int cost) {
    printf("최적 경로: ");
    for (int i = 0; i < n; i++) printf("%d -> ", path[i]);
    printf("0\n"); // 출발점 복귀
    printf("최소 비용: %d\n", cost);
}

void tsp_branch_bound() {
    // 초기 루트 노드 생성
    Node* root = (Node*)malloc(sizeof(Node));
    root->level = 0;
    root->cost = 0;
    for (int i = 0; i < n; i++) {
        root->visited[i] = 0;
        root->path[i] = -1;
    }
    root->path[0] = 0;     // 출발 도시는 0번
    root->visited[0] = 1;  // 방문 표시
    root->bound = bound(root); // bound 계산
    push(root);            // 힙에 삽입

    // 탐색 시작
    while (heap_size > 0) {
        Node* current = pop(); // bound가 가장 작은 노드 선택

        // 현재 bound가 최적값보다 크면 더 이상 탐색하지 않음
        if (current->bound >= best_cost) {
            free(current);
            continue;
        }

        // 모든 도시 방문 완료하면 출발 도시로 돌아가는 경로 확인
        if (current->level == n - 1) {
            int last = current->path[current->level];
            if (W[last][0] != 0) {
                int total_cost = current->cost + W[last][0];
                if (total_cost < best_cost) {
                    best_cost = total_cost;
                    for (int i = 0; i < n; i++) best_path[i] = current->path[i];
                }
            }
            free(current);
        }
        else {
            // 아직 방문 안한 도시 방문 후보 생성
            for (int i = 0; i < n; i++) {
                if (!current->visited[i] && W[current->path[current->level]][i] != 0) {
                    Node* child = (Node*)malloc(sizeof(Node));
                    *child = *current; // 상태 복사
                    child->level = current->level + 1;
                    child->path[child->level] = i;
                    child->visited[i] = 1;
                    child->cost += W[current->path[current->level]][i];
                    child->bound = bound(child);

                    if (child->bound < best_cost) push(child);
                    else free(child);
                }
            }
            free(current);
        }
    }

    print_solution(best_path, best_cost);
}

int main() {
    // 예시 도시 및 비용 설정 (대칭행렬)
    n = 4;
    W[0][1] = 10; W[0][2] = 15; W[0][3] = 20;
    W[1][0] = 10; W[1][2] = 35; W[1][3] = 25;
    W[2][0] = 15; W[2][1] = 35; W[2][3] = 30;
    W[3][0] = 20; W[3][1] = 25; W[3][2] = 30;

    tsp_branch_bound();
    return 0;
}
