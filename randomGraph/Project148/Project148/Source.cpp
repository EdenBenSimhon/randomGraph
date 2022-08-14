#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <math.h>
#include <time.h>
#define SIZE 1000
static int counter = 1;
static bool* visited;
/*##################################################*/
typedef struct Node
{
	int NumVertex;
	struct Node* next;
} Node;
/*##################################################*/
struct queue
{
	int items[SIZE];
	int front;
	int rear;
};
/*##################################################*/
bool Isolated_Is(Node**);
int push_front(Node**, int);
void pushBack(Node**, int);
void output(Node**);
void Create(Node**);
Node** graph_random_build(int, float);
void display(Node**, size_t);
int bfs(Node**, int);
struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);
struct Node* createNode(int);
Node** graph_random_build(int, float);

/*The function add a value to the top of linked list
##################################################*/
int push_front(Node** head, int NumVertex)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	int success = new_node != NULL;

	if (success)
	{
		new_node->NumVertex = NumVertex;
		new_node->next = *head;
		*head = new_node;
	}

	return success;
}
/*The function add a value to the bottom of linked list
##################################################*/
void pushBack(Node** head, int value)
{
	while (*head)
	{
		head = &(*head)->next;
	}

	*head = (Node*)malloc(sizeof(**head));
	(*head)->NumVertex = value;
	(*head)->next = NULL;
}
/*The display and output function prints the graph
/*##################################################*/
void output(Node** head)
{

	for (Node* current = *head; current != NULL; current = current->next)
	{
		//printf("%d->", current->NumVertex);
	}
	//printf("%s", "NULL");
}
/*The function set NULL in linked list
##################################################*/
void Create(Node** queue)
{
	for (int i = 0; i < 1; i++)
	{
		queue[i] = NULL;
	}
}
/*The function cerate random graph
######################################################*/
Node** graph_random_build(int V, float P)
{
	Node** Graph = (Node**)malloc(V * sizeof(Node*));
	for (int i = 0; i < V; i++)
	{

		Create(&Graph[i]);
		pushBack(&Graph[i], i);
	}
	int j;
	int i;
	srand(time(NULL));
	for (i = 0; i < V; i++)
	{
		for (j = 0; j < V && j != i; j++)
		{
			float r = (float)rand() / (float)RAND_MAX;
			if (r <= P)
			{
				pushBack(&Graph[i], j);
				pushBack(&Graph[j], i);
			}
		}
	}
	visited = (bool*)calloc(V, sizeof(int));
	return Graph;
}
/*##################################################*/
void display(Node** set, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		//printf("Number of Vertex:%d\n", i);
		output(set++);
		putchar('\n');
	}
}
/*BFS algorithm in C
##################################################*/
int bfs(Node** graph, int startVertex)
{
	//dynmaic memory
	struct queue* q = createQueue();
	int* distance = (int*)malloc(counter * sizeof(int));
	//int distance[1000];
	visited[startVertex] = 1;
	enqueue(q, startVertex);
	int i = 0;
	int max = 0;
	distance[startVertex] = 0;
	while (!isEmpty(q))
	{
		printQueue(q);
		int currentVertex = dequeue(q);
		//printf("\nVisited %d\n", currentVertex);
		struct Node* temp = graph[currentVertex];
		while (temp)
		{
			int adjVertex = temp->NumVertex;
			if (visited[adjVertex] == 0)
			{
				visited[adjVertex] = 1;
				enqueue(q, adjVertex);
				distance[adjVertex] = distance[currentVertex] + 1;
				if (max <= distance[adjVertex])
				{
					max = distance[adjVertex];
				}
			}
			temp = temp->next;
		}
	}
	free(q);
	free(distance);
	return max;
}

/*Creating a node
##################################################*/
struct Node* createNode(int v)
{
	struct Node* newNode = (Node*)malloc(sizeof(struct Node));
	newNode->NumVertex = v;
	newNode->next = NULL;
	return newNode;
}
/*Create a queue
##################################################*/
struct queue* createQueue()
{
	struct queue* q = (queue*)malloc(sizeof(struct queue));
	q->front = -1;
	q->rear = -1;
	return q;
}


/*Check if the queue is empty
##################################################*/
int isEmpty(struct queue* q) {
	if (q->rear == -1)
		return 1;
	else
		return 0;
}
/*The function set NULL in visted array
##################################################*/
void cleanvisted()
{
	for (int i = 0; i < counter; i++)
	{
		visited[i] = false;
	}
}


/*Adding elements into queue
##################################################*/
void enqueue(struct queue* q, int value) {
	if (q->rear == SIZE - 1)
		printf("\nQueue is Full!!");
	else
	{
		if (q->front == -1)
			q->front = 0;
		q->rear++;
		q->items[q->rear] = value;
	}
}

// Removing elements from queue
int dequeue(struct queue* q) {
	int item;
	if (isEmpty(q)) {
		//printf("Queue is empty");
		item = -1;
	}
	else {
		item = q->items[q->front];
		q->front++;
		if (q->front > q->rear) {
			//printf("Resetting queue");
			q->front = q->rear = -1;
		}
	}
	return item;
}


/* Print the queue
##################################################*/
void printQueue(struct queue* q) {
	int i = q->front;

	if (isEmpty(q)) {
		//printf("Queue is empty");
	}
	else {
		//printf("\nQueue contains \n");
		for (i = q->front; i < q->rear + 1; i++) {
			//printf("%d ", q->items[i]);
		}
	}
}
/* The function checks if the graph is connected
##################################################*/
int connectivity(Node** graph)
{
	if (Isolated_Is(graph) == 1)
	{
		return 2;
	}
	bfs(graph, 0);
	int i = 0;
	for (i = 0; i < counter; i++)//counter=Vertex  
	{
		if (visited[i] != 1)
		{
			cleanvisted();
			return 0;
		}
	}
	cleanvisted();
	return 1;
}
/* The function print the result connectivity function
##################################################*/
void PrintConnected(int result)
{
	if (result == 1)
	{
		printf("The Graph is connected\n");
	}
	else
	{
		printf("The Graph is not connected\n");
	}
}
/* The function checks there is a vertex without neighbors
##################################################*/
bool Isolated_Is(Node** Graph)
{
	int i = 0;
	for (i = 0; i < counter; i++)
	{
		if (Graph[i]->next == NULL)
		{

			return true;
		}
	}
	return false;
}
/* The function print the result Isolated_Is function
##################################################*/
void PrintIsolated_Is(bool result)
{
	if (result == 1)
	{
		printf("\nYES\n%d", result);
	}
	else
	{
		printf("\nNO\n%d", result);
	}
}
/* The function checks the length of diamter of the graph
##################################################*/
int diameter(Node** graph)
{
	int i = 0;
	int max = 0;
	bfs(graph, 0);
	int diam = 0;
	if (connectivity(graph) == 0)
	{
		return -1;
	}
	cleanvisted();
	for (i = 0; i < counter; i++)
	{

		int diam = bfs(graph, i);
		cleanvisted();
		if (diam >= max)
		{
			max = diam;
		}
	}
	return max;
}
/* The deleteList and free_graph functions release dynamic memory
##################################################*/
void deleteList(Node** head_ref)
{
	Node* current = *head_ref;
	Node* next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
void free_graph(Node** Graph)
{
	int i;
	for (i = 0; i < counter; i++)
	{
		deleteList(&Graph[i]);
	}
	cleanvisted();
}
/* The function write to csv file
##################################################*/
void writetocsv(float* pr1, float* Pro, int* diamter, int* connect, int* isloted, int Amountofrun)
{
	FILE* fp;
	int i;
	float a=(float)Amountofrun;
	printf("%f", a);
	fp = fopen("12.csv", "w");
	fprintf(fp, "Test result:\n\n\nNO,probability,connected,isolated\n");

	for (i = 0; i < 10; i++)
	{
		fprintf(fp, "%d,%f,%f,%f\n", i, Pro[i], connect[i] / a, isloted[i] / a);
		printf("%f\n", connect[i] / a);
	}
	fprintf(fp, "\n\n\nTest result:\n\n\nNO,probability,diameter\n");
	for (i = 0; i < 10; i++)
	{
		fprintf(fp,"%d,%f,%f\n", i, pr1[i], diamter[i] / a);
	}
	fclose(fp);

}
/* The function	analyze the random graph
##################################################*/
void details()
{
	Node** Graph;
	int i, j, count, r = 0;
	float Threshold1[10] = {0.00338,0.00590,0.00640,0.00670,0.00680,0.007,0.0075,0.00899,0.0094,0.138};
	float Threshold2[10] = { 0.01,0.05,0.07,0.08,0.09,0.118,0.12,0.125,0.13,0.15};
	int resultdiamter[10] = { 0 };
	int resultIsloted[10] = { 0 };
	int resultconnect[10] = { 0 };
	int diamer = 0;
	int Amountofrun = 500;
	int result = 0;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < Amountofrun; j++)
		{
			Graph = graph_random_build(counter, Threshold1[i]);
			result = connectivity(Graph);
			if (result == 2) 
			{
				resultIsloted[i]++;
			}
			else if (result != -1)
			{
				resultconnect[i]++;
			}
			free_graph(Graph);
			Graph = graph_random_build(counter, Threshold2[i]);
			diamer = diameter(Graph);
			if (diamer != -1 && diamer <= 2)
			{
				resultdiamter[i]++;
			}
			free_graph(Graph);

		}
		printf("\n%d\t%d", i, j);

	}
	writetocsv(Threshold2, Threshold1, resultdiamter, resultconnect, resultIsloted, Amountofrun);

}



void main()
{
	int v = 1000;
	counter = v;
	details();
	//PrintConnected(connectivity(Graph1));
	//display(Graph1, v);
	//printf("\n\n%d\n\n", diamer);
	//PrintIsolated_Is(Isolated_Is(Graph1));
	//display(Graph1, v);
	//cleanvisted();
}
