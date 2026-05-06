#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
	char keyword[100];
	struct Node* next;
} Node;

Node* createNode(char keyword[100]) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	strcpy_s(newNode->keyword, 100, keyword);
	newNode->next = NULL;
	return newNode;
}

void addKeyword(Node** head, char* keyword, int maxSize) {
	Node* prev = NULL;
	Node* temp = *head;
	while (temp != NULL) {
		if (strcmp(temp->keyword, keyword) == 0) {
			if (prev == NULL)
				return;
			else {
				prev->next = temp->next;
				temp->next = *head;
				*head = temp;
				return;
			}
		}
		prev = temp;
		temp = temp->next;
	}

	Node* newNode = createNode(keyword);
	newNode->next = *head;
	*head = newNode;

	temp = *head;
	prev = NULL;
	int count = 1;
	while (temp != NULL) {
		if (count > maxSize) {
			prev->next = NULL;
			free(temp);
			return;
		}
		count += 1;
		prev = temp;
		temp = temp->next;
	}
}

void printKeywords(Node* head) {
	Node* temp = head;
	while (temp != NULL) {
		printf("%s  ", temp->keyword);
		temp = temp->next;
	}
	printf("\n");
	return;
}

void main() {
	Node* head = NULL;
	addKeyword(&head, "apple", 3);
	printKeywords(head);
	addKeyword(&head, "banana", 3);
	printKeywords(head);
	addKeyword(&head, "cheeze", 3);
	printKeywords(head);
	addKeyword(&head, "apple", 3);
	printKeywords(head);
	addKeyword(&head, "pear", 3);
	printKeywords(head);

}
