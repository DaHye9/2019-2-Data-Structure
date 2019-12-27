#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char* stack;
	int size;
	int top;
}Stack;

int isEmpty(Stack* pStack) {
	return pStack->top == -1 ? 1 : 0;
}

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

char Pop(Stack* pStack) {
	if (pStack->top < 0)
		return 0;
	return pStack->stack[pStack->top--];
}

char Stack_Top(Stack* pStack) {
	if (pStack->top < 0)
		return 0;
	return pStack->stack[pStack->top];
}

void DestroyStack(Stack* pStack) {
	if (pStack->size < 0)
		free(pStack->stack);
	free(pStack);
}

int CatStack(Stack* pStack1, Stack* pStack2) {
	if (pStack2->top < 0 || pStack1->size < pStack1->top + pStack2->top)
		return 0;
	Stack* temp = CreateStack(pStack2->size);
	while (pStack2->top >= 0)
		Push(temp, Pop(pStack2));
	while (temp->top >= 0)
		Push(pStack1, Pop(temp));
	DestroyStack(temp);
	return pStack1->stack[pStack1->top];
}

void PrintStack(Stack* pStack) {
	for (int i = 0; i <= pStack->top; i++) {
		printf("%d\n", pStack->stack[i]);
	}
}

int priority(char a) {
	if (a == '*' || a == '/')
		return 1;
	else return 0;
}

int isOperator(char a) {
	if (a == '+' || a == '-' || a == '*' || a == '/')
		return 1;
	return 0;
}

int isAlpha(char c) {
	if (c >= 'A' && c <= 'Z') return 1;
	return 0;
}

char* postfix(char* input) {
	char* result=(char*)malloc(sizeof(char)*101);
	Stack* temp = CreateStack(100);	
	int count = 0;

	int length = strlen(input);
	for (int i = 0; i < length; i++) {
		if (isAlpha(input[i])) {
			result[count] = input[i];
			count++;
		}
		else if (input[i] == '(') {
			Push(temp, input[i]);
		}
		else if (isOperator(input[i])) {
			while (priority(Stack_Top(temp)) > priority(input[i])) {
				result[count] = Pop(temp);
				count++;
			}
			Push(temp, input[i]);

		}
		else if (input[i] == ')') {
			char x = Pop(temp);
			while (x != '(') {
				result[count] = x;
				count++;
				x = Pop(temp);
			}
		}
	}
	while (!isEmpty(temp)) {
		result[count++] = Pop(temp);
	}
	result[count] = '\0';
	return result;
}

int main() {
	char input[101];
	scanf("%s", input);

	printf("%s", postfix(input));
	return 0;
}