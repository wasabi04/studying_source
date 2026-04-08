#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct {
    int data[MAX_SIZE];
    int front;  // 꺼낼 위치
    int rear;   // 넣을 위치
} Queue;

void init(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue* q) {
    return q->front == q->rear;  // front == rear면 빈 상태
}

int isFull(Queue* q) {
    // (rear + 1) % MAX_SIZE == front면 꽉 찬 상태
    return (q->rear + 1) % MAX_SIZE == q->front;
}

void enqueue(Queue* q, int data) {
    if (isFull(q)) {
        printf("큐가 가득 찼습니다!\n");
        return;
    }
    q->data[q->rear] = data;
    q->rear = (q->rear + 1) % MAX_SIZE;  // 원형으로 이동!
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("큐가 비어있습니다!\n");
        return -1;
    }
    int val = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;  // 원형으로 이동!
    return val;
}
