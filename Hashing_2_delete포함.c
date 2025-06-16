#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 10
#define NAME_LEN 30

typedef struct {
    char name[NAME_LEN];
    int is_occupied; // 1: 사용중, 0: 비어 있음, -1: 삭제된 자리
} HashSlot;

HashSlot hash_table[TABLE_SIZE];

int hash(char *str) {
    int sum = 0;
    for (int i = 0; str[i]; i++) {
        sum += str[i];
    }
    return sum % TABLE_SIZE;
}

void insert(char *name) {
    int idx = hash(name);
    int original_idx = idx;
    int attempts = 0;

    while (hash_table[idx].is_occupied == 1 && attempts < TABLE_SIZE) {
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

void search(char *name) {
    int idx = hash(name);
    int original_idx = idx;
    int attempts = 0;

    while (hash_table[idx].is_occupied != 0 && attempts < TABLE_SIZE) {
        if (hash_table[idx].is_occupied == 1 && strcmp(hash_table[idx].name, name) == 0) {
            printf("'%s' 찾음 (위치: %d)\n", name, idx);
            return;
        }
        idx = (idx + 1) % TABLE_SIZE;
        attempts++;
        if (idx == original_idx) break;
    }

    printf("'%s'는 해시 테이블에 없음\n", name);
}

void delete(char *name) {
    int idx = hash(name);
    int original_idx = idx;
    int attempts = 0;

    while (hash_table[idx].is_occupied != 0 && attempts < TABLE_SIZE) {
        if (hash_table[idx].is_occupied == 1 && strcmp(hash_table[idx].name, name) == 0) {
            hash_table[idx].is_occupied = -1;  // 삭제된 자리 표시
            printf("'%s' 삭제 완료 (위치: %d)\n", name, idx);
            return;
        }
        idx = (idx + 1) % TABLE_SIZE;
        attempts++;
        if (idx == original_idx) break;
    }

    printf("'%s'는 삭제할 수 없음 (존재하지 않음)\n", name);
}

void display_table() {
    printf("\n[해시 테이블 상태]\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i].is_occupied == 1) {
            printf("[%d] %s\n", i, hash_table[i].name);
        } else if (hash_table[i].is_occupied == -1) {
            printf("[%d] (삭제됨)\n", i);
        } else {
            printf("[%d] (비어 있음)\n", i);
        }
    }
    printf("\n");
}

int main() {
    insert("Alice");
    insert("Bob");
    insert("Charlie");
    insert("David");

    display_table();

    search("Charlie");
    search("Eve");

    delete("Charlie");
    delete("Eve");

    display_table();

    return 0;
}
