#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define NAME_LENGTH 20

// 노드 구조체 정의
typedef struct Node {
    char name[NAME_LENGTH];
    struct Node* next;
} Node;

// 해시 테이블: 각 버킷에 연결 리스트의 헤드 포인터
Node* hashTable[TABLE_SIZE];

// 해시 함수: 이름의 아스키코드 합을 테이블 크기로 나눈 나머지
int hash(char* name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += name[i];
    }
    return sum % TABLE_SIZE;
}

// 삽입 함수
void insert(char* name) {
    int idx = hash(name);
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->next = hashTable[idx]; // 새 노드를 헤드에 삽입
    hashTable[idx] = newNode;
    
    printf("'%s' 삽입됨. 해시 인덱스: %d\n", name, idx);
}

// 검색 함수
Node* search(char* name) {
    int idx = hash(name);
    Node* curr = hashTable[idx];
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

// 해시 테이블 출력 함수
void printTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node* curr = hashTable[i];
        while (curr != NULL) {
            printf("%s -> ", curr->name);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

// 메모리 해제
void freeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = hashTable[i];
        while (curr != NULL) {
            Node* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
}

int main() {
    insert("Alice");
    insert("Bob");
    insert("Charlie");
    insert("David");
    insert("Eve");

    printf("\n해시 테이블 상태:\n");
    printTable();

    printf("\n검색 테스트:\n");
    char* query = "Charlie";
    Node* result = search(query);
    if (result != NULL)
        printf("'%s' 찾음!\n", query);
    else
        printf("'%s' 없음.\n", query);

    freeTable();
    return 0;
}
