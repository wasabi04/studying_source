#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void stack_push(Node** head, int data) {
	Node* newNode = createNode(data);
	newNode->next = *head;
	*head = newNode;
}

void stack_pop(Node** head) {
	if (*head == NULL) {
		printf("list is empty!");
		return;
	}
	Node* temp = *head;
	*head = (*head)->next;
	free(temp);
}

typedef struct Queue {
	Node* head;
	Node* tail;
} Queue;

void enqueue(Queue* queue, int data) {
	Node* newNode = createNode(data);
	queue->tail->next = newNode;
	queue->tail = newNode;
}

void dequeue(Queue* queue) {
	if (queue->head == NULL) {
		printf("list is empty!");
		return;
	}
	if (queue->head->next == NULL) {
		free(queue->head);
		queue->head = NULL;
		queue->tail = NULL;
		printf("now list is empty!");
		return;
	}
	Node* temp = queue->head;
	queue->head = queue->head->next;
	free(temp);
}