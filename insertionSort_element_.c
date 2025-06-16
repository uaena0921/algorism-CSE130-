#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 8

typedef struct {
	int key;
}element;

void insertionSort(element list[], int n);

int main() {

	//element data[] = { 10, 30, 20, 40, 80, 60, 70, 50 };
	element data[] = { {10}, {30}, {20}, {40}, {80}, {60}, {70}, {50} };

	insertionSort(data, MAX_SIZE);

	printf("Result : ");
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("%d   ", data[i].key);
	}

	printf("\n\n");

	return 0;
}

void insertionSort(element list[], int n)
/* perform a insertion sort on the list */
{
	int i, j;
	element next;

	for (i = 1; i < n; i++)
	{
		next = list[i];    /* save list [i] */

		for (j = i - 1; j >= 0 && next.key < list[j].key; j--)
			list[j + 1] = list[j];     /* shift operation */

		list[j + 1] = next;
	}
}

/* °á°ú

Result : 10   20   30   40   50   60   70   80

*/