#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100


typedef struct {
    int data[MAX_SIZE];  // 데이터 저장 공간
    int top;             // 맨 위 인덱스 (-1이면 비어있음)
} Stack;

void init(Stack* s) {
    s->top = -1;  // 비어있는 상태를 -1로 표현
}


int isEmpty(Stack* s) {
    return s->top == -1;
}


int isFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}


void push(Stack* s, int data) {
    if (isFull(s)) {
        printf("스택이 가득 찼습니다!\n");
        return;
    }
    s->data[++(s->top)] = data;  // top을 먼저 올리고 저장
}


int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("스택이 비어있습니다!\n");
        return -1;  // 오류 값
    }
    return s->data[(s->top)--];  // 꺼내고 top을 내림
}


int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("스택이 비어있습니다!\n");
        return -1;
    }
    return s->data[s->top];  // top을 바꾸지 않음!
}


int main() {
    Stack s;
    init(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("peek: %d\n", peek(&s));  // 30
    printf("pop:  %d\n", pop(&s));   // 30
    printf("pop:  %d\n", pop(&s));   // 20
    printf("pop:  %d\n", pop(&s));   // 10

    return 0;
}