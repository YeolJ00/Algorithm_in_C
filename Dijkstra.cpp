#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INT_MAX 2000000000

typedef struct graph G;
typedef struct graph {
	char v;
	G* link;
	int d;
	int w;
}G;


int heapsize=0;
int Heap_Max(G heap[]);
G Heap_Extract_Min(G heap[]);
void Heap_decrease_Key(G heap[], int i, G item);
void Min_Heapify(G heap[], int i);
void Build_MinHeap(G heap[]);
void Relax(G heap[], G graph[], char u, char v,int Vnum);

int main() {
	char Ver[100];//initial input buffer
	G graph[100];
	int Vnum=0;
	scanf("%s", Ver);
	char *ptr = strtok(Ver, ",");
	while (ptr != NULL) {
		graph[Vnum].v = *ptr;
		graph[Vnum].d = INT_MAX;
		graph[Vnum++].link = NULL;
		ptr = strtok(NULL, ",");
	}
	heapsize = Vnum;

	int Enum, w;
	char v1, v2;//v1= v_from  v1=v_to
	scanf("%d", &Enum);
	getchar();
	for (int i = 0; i < Enum; i++) {
		scanf("%c,%c,%d",&v1, &v2,&w);
		int j =0;
		for (j = 0; j < Vnum; j++) {// find index of v1
			if (graph[j].v == v1) break;
		}
		G* temp = (G*)malloc(sizeof(G));//add G with weight and vertex information in graph[v1]'s linked list
		temp->v = v2;
		temp->w = w;
		temp->link = graph[j].link;
		graph[j].link = temp;
		getchar();
		/*
		G debug1 = graph[j];
		G* debug = graph[j].link;
		printf("Vertex %c has links ", graph[j].v);
		while (debug) {
			printf("(%c, %d)", debug->v, debug->w);
			debug = debug->link;
		}
		*/
	}
	graph[0].d = 0;
	G *queue = (G*)malloc(sizeof (G) * heapsize);

	for (int i = 0; i < Vnum; i++) {
		queue[i].v = graph[i].v;
		queue[i].d = graph[i].d;
	}
	Build_MinHeap(queue);
	/*
	for (int i = 0; i < heapsize; i++) {
		printf("(%c, %d)", queue[i].v, queue[i].d);
	}*/

	while (heapsize) {
		G u = Heap_Extract_Min(queue);
		/*
		printf("Heap after extracting %c: ",u.v);
		for (int i = 0; i < heapsize; i++) {
			printf("(%c,%d) ", queue[i].v,queue[i].d);
		}
		printf("\n");
		*/

		int j;
		for (j = 0; j < Vnum; j++) {// find u node in graph, index will be j
			if (graph[j].v == u.v) break;
		}
		G* adj_node = graph[j].link;//adj_node will point to all linked node in graph[j] respectively
		while (adj_node) {
			char v = adj_node->v;
			Relax(queue, graph, u.v, v, Vnum);
			adj_node = adj_node->link;
		}
		/*
		printf("Queue after relax\n");
		for (int i = 0; i < heapsize; i++) {
			printf("(%c,%d) ", queue[i].v, queue[i].d);
		}
		printf("\n");
		*/
	}
	for (int i = 0; i < Vnum; i++) {
		printf("%d\n",graph[i].d);
	}
	system("PAUSE");
}

void Relax(G queue[], G graph[], char u, char v, int size) {//size == Vnum
	int u_index;
	for (u_index = 0; u_index < size; u_index++) {//find index of u in graph
		if (graph[u_index].v == u) break;
	}
	int v_index;
	for (v_index = 0; v_index < size; v_index++) {//find index of v in graph
		if (graph[v_index].v == v) break;
	}
	G* weight = graph[u_index].link;//weight points (u,v)
	while (weight) {
		if (weight->v == v) break;//this will always break before weight==NULL
		weight = weight->link;
	}
	if (graph[v_index].d > graph[u_index].d + weight->w) {
		graph[v_index].d = graph[u_index].d + weight->w;
		int queue_index;
		for (queue_index = 0; queue_index < heapsize; queue_index++) {//find queue index of v and change so that we resort the queue
			if (queue[queue_index].v == v) break;
		}
		G item;
		item.d = graph[v_index].d;
		item.v = v;
		Heap_decrease_Key(queue, queue_index, item);
	}
}
int Heap_Max(G heap[]) {
	return heap[0].d;
}
G Heap_Extract_Min(G heap[]) {
	G max = heap[0];
	heap[0] = heap[--heapsize];
	Min_Heapify(heap, 0);
	return max;
}
void Heap_decrease_Key(G heap[], int i, G item) {
	if (item.d > heap[i].d) return;
	heap[i] = item;
	while ((i > 0 && heap[i / 2].d > heap[i].d) || (i>0 && heap[i/2].d == heap[i].d && heap[i/2].v > heap[i].v)) {
		G temp = heap[i];
		heap[i] = heap[i / 2];
		heap[i / 2] = temp;
		i /= 2;
	}
}

void Min_Heapify(G heap[], int i) {
	int l = 2 * (i + 1) - 1;
	int r = 2 * (i + 1);
	int smallest;
	if (l < heapsize && heap[l].d < heap[i].d) smallest = l;
	else if (l < heapsize && heap[l].d == heap[i].d && heap[l].v < heap[i].v)  smallest = l;
	else smallest = i;

	if (r < heapsize && heap[r].d < heap[smallest].d) smallest = r;
	else if (r<heapsize && heap[r].d == heap[smallest].d && heap[r].v < heap[smallest].v) smallest = r;

	if (smallest != i) {
		G temp = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = temp;
		Min_Heapify(heap, smallest);
	}
}

void Build_MinHeap(G heap[]) {
	for (int i = (heapsize / 2) - 1; i >= 0; i--) {
		Min_Heapify(heap, i);
	}
}
