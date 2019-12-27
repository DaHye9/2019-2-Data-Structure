#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int* stack;
	int size;
	int top;
}Stack;

Stack* CreateStack(int size) {
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL)
		return NULL;

	pStack->stack = (int*)malloc(size * sizeof(int));
	if (pStack->stack == NULL)
		return NULL;

	pStack->size = size;
	pStack->top = -1;

	return pStack;
}

int Push(Stack* pStack, int push_item) {
	if (pStack->top == pStack->size - 1)
		return 0;
	pStack->stack[++pStack->top] = push_item;
	return 1;
}

int Pop(Stack* pStack) {
	if (pStack->top < 0)
		return 0;
	return pStack->stack[pStack->top--];
}

int Stack_Top(Stack* pStack) {
	if (pStack->top < 0)
		return 0;
	return pStack->stack[pStack->top];
}

void DestroyStack(Stack* pStack) {
	if (pStack->size < 0)
		free(pStack->stack);
	free(pStack);
}

void CheckBrace(Stack* pStack) {
	if (pStack->top < 1)
		return;
	if (pStack->stack[pStack->top] == '}' && pStack->stack[pStack->top - 1] == '{'
		|| pStack->stack[pStack->top] == ']' && pStack->stack[pStack->top - 1] == '['
		|| pStack->stack[pStack->top] == ')' && pStack->stack[pStack->top - 1] == '(') {
		Pop(pStack);
		Pop(pStack);
		return;
	}
}

void PrintStack(Stack* pStack) {
	for (int i = 0; i <= pStack->top; i++) {
		printf("%d\n", pStack->stack[i]);
	}
}

int main() {
	char input[1000];
	Stack* stack = CreateStack(100);
	gets(input);
	for (int i = 0; input[i] != NULL; i++) {
		if (input[i] == '(' || input[i] == ')' || input[i] == '{' || input[i] == '}' || input[i] == '[' || input[i] == ']') {
			Push(stack, input[i]);
			CheckBrace(stack);
		}
	}
	if (stack->top == -1)
		printf("yes");
	else
		printf("no");
	DestroyStack(stack);
}