#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define NAME_LEN 30

typedef struct {
    char name[NAME_LEN];
    int is_occupied;  // 0이면 비어 있음, 1이면 사용 중
} HashSlot;

HashSlot hash_table[TABLE_SIZE];

// 간단한 해시 함수: 문자열의 아스키값 합을 테이블 크기로 나눈 나머지
int hash(char *str) {
    int sum = 0;
    for (int i = 0; str[i]; i++) {
        sum += str[i];
    }
    return sum % TABLE_SIZE;
}

// 선형 탐사로 이름 삽입
void insert(char *name) {
    int idx = hash(name);
    int original_idx = idx;
    int attempts = 0;

    while (hash_table[idx].is_occupied && attempts < TABLE_SIZE) {
        idx = (idx + 1) % TABLE_SIZE;
        attempts++;
        if (idx == original_idx) {
            printf("삽입 실패: 해시 테이블이 가득 찼습니다.\n");
            return;
        }
    }

    strcpy(hash_table[idx].name, name);
    hash_table[idx].is_occupied = 1;
    printf("'%s' 삽입 완료 (위치: %d)\n", name, idx);
}

// 이름 검색
void search(char *name) {
    int idx = hash(name);
    int original_idx = idx;
    int attempts = 0;

    while (hash_table[idx].is_occupied && attempts < TABLE_SIZE) {
        if (strcmp(hash_table[idx].name, name) == 0) {
            printf("'%s' 찾음 (위치: %d)\n", name, idx);
            return;
        }
        idx = (idx + 1) % TABLE_SIZE;
        attempts++;
        if (idx == original_idx) break;
    }

    printf("'%s'는 해시 테이블에 없음\n", name);
}

// 테이블 출력
void display_table() {
    printf("\n[해시 테이블 상태]\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i].is_occupied) {
            printf("[%d] %s\n", i, hash_table[i].name);
        } else {
            printf("[%d] (비어 있음)\n", i);
        }
    }
    printf("\n");
}

// 메인 함수
int main() {
    insert("Alice");
    insert("Bob");
    insert("Charlie");
    insert("David");

    display_table();

    search("Charlie");
    search("Eve");

    return 0;
}
