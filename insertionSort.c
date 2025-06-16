#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 8

void insertionSort(int *data, int n);


int main() {
	int data[] = {10, 30, 20, 40, 80, 60, 70, 50 }; 

	insertionSort(data, MAX_SIZE);

	printf("Result : ");
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("%d   ", data[i]);
	}

	printf("\n\n");

	return 0;
}

void insertionSort(int *data, int n)
{
	int i, j, key;

	for (i = 1; i < n; i++)
	{
		key = data[i];

		for (j = i - 1; j >= 0 && key < data[j]; j--)  // 오름차순 정렬
			data[j + 1] = data[j];

		data[j + 1] = key;
	}
}

/* 결과

Result : 10   20   30   40   50   60   70   80

*/

