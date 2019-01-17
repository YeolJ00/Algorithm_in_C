#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2000000000

typedef struct hp intH;
typedef struct hp {
	int element;
	int freq;
	intH* lchild;
	intH* rchild;
}intH;

int Heap_Max(intH heap[]);
intH Heap_Extract_Min(intH heap[]);
void Heap_Increase_Key(intH heap[], int i, intH key);
void Min_Heap_Insert(intH heap[], intH item);
void Min_Heapify(intH heap[], int i);
void Build_MinHeap(intH heap[]);
void Search(intH root, int i, int top, int text[]);

int heapsize;

int main() {
	int c;
	scanf("%d", &c);
	intH* ptr = (intH*)malloc(sizeof(intH)*c);
	heapsize = c;
	for (int i = 0; i < c; i++) {
		ptr[i].element = i;
		scanf("%d", &ptr[i].freq);
		ptr[i].lchild = NULL;
		ptr[i].rchild = NULL;
	}
	Build_MinHeap(ptr);
	for (int i = 0; i < c - 1; i++) {
		intH* leftnode = (intH*)malloc(sizeof(intH));
		*leftnode = Heap_Extract_Min(ptr);
		intH *rightnode = (intH*)malloc(sizeof(intH));
		*rightnode = Heap_Extract_Min(ptr);
		intH temp;
		temp.freq = leftnode->freq + rightnode->freq;
		temp.element = -1;
		temp.lchild = leftnode;
		temp.rchild = rightnode;
		Min_Heap_Insert(ptr, temp);
	}
	int text[100];
	for (int i = 0; i < c; i++) {
		Search(ptr[0],  i, 0, text);
	}
	system("PAUSE");
}
void Search(intH root, int i, int top, int text[]) {
	if (root.lchild != NULL) {
		text[top] = 0;
		Search(*(root.lchild), i, top+1,text);
	}
	if (root.rchild != NULL) {
		text[top] = 1;
		Search(*(root.rchild), i, top+1, text);
	}
	if (root.element == i && root.rchild == NULL && root.lchild == NULL) {
		for (int j = 0; j < top; j++) {
			printf("%d", text[j]);
		}
		printf("\n");
	}
}
int Heap_Max(intH heap[]) {
	return heap[0].freq;
}
intH Heap_Extract_Min(intH heap[]) {
	intH max = heap[0];
	heap[0] = heap[--heapsize];
	Min_Heapify(heap, 0);
	return max;
}
void Heap_Increase_Key(intH heap[], int i, intH item) {
	if (item.freq > heap[i].freq) return;
	heap[i] = item;
	while (i > 0 && heap[i / 2].freq > heap[i].freq) {
		intH temp = heap[i];
		heap[i] = heap[i / 2];
		heap[i / 2] = temp;
		i /= 2;
	}
}
void Min_Heap_Insert(intH heap[], intH item) {
	heap[heapsize++].freq = INT_MAX;
	Heap_Increase_Key(heap, heapsize - 1, item);
}

void Min_Heapify(intH heap[], int i) {
	int l = 2 * (i + 1) - 1;
	int r = 2 * (i + 1);
	int smallest;
	if (l < heapsize && heap[l].freq < heap[i].freq) smallest = l;
	else smallest = i;
	if (r < heapsize && heap[r].freq < heap[smallest].freq) smallest = r;
	if (smallest != i) {
		intH temp = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = temp;
		Min_Heapify(heap, smallest);
	}
}

void Build_MinHeap(intH heap[]) {
	for (int i = (heapsize / 2) - 1; i >= 0; i--) {
		Min_Heapify(heap, i);
	}
}
