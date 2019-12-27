#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	double* stack;
	int size;
	int top;
}Stack;

Stack* CreateStack(int size) {
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL)
		return NULL;

	pStack->stack = (double*)malloc(size * sizeof(double));
	if (pStack->stack == NULL)
		return NULL;

	pStack->size = size;
	pStack->top = -1;

	return pStack;
}

int Push(Stack* pStack, double push_item) {
	if (pStack->top == pStack->size - 1)
		return 0;
	pStack->stack[++pStack->top] = push_item;
	return 1;
}

double Pop(Stack* pStack) {
	if (pStack->top < 0)
		return 0;
	return pStack->stack[pStack->top--];
}

double Stack_Top(Stack* pStack) {
	if (pStack->top < 0)
		return 0;
	return pStack->stack[pStack->top];
}

void DestroyStack(Stack* pStack) {
	if (pStack->size < 0)
		free(pStack->stack);
	free(pStack);
}

void PrintStack(Stack* pStack) {
	for (int i = 0; i <= pStack->top; i++) {
		printf("%c\n", pStack->stack[i]);
	}
}

int is_operator(char item) {
	char oper[4] = { '+', '-', '*', '/' };
	for (int i = 0; i < 4; i++) {
		if (item == oper[i]) return 1;
	}
	return 0;
}

int priority(char item) {
	if (item == '*' || item == '/')
		return 2;
	else if (item == '+' || item == '-')
		return 3;
	return 0;
}

void change(Stack* pStack, Stack* temp_operator, char item) {
	if (isdigit(item)) {
		Push(pStack, item);
	}
	else if (is_operator(item)) {
		while (priority(Stack_Top(temp_operator)) == 2 && priority(item) == 3) {
			Push(pStack, Pop(temp_operator));
		}
		Push(temp_operator, item);
	}
	else if (item == '(') {
		Push(temp_operator, item);
	}
	else if (item == ')') {
		while (Stack_Top(temp_operator) != '(') {
			Push(pStack, Pop(temp_operator));
		}
		Pop(temp_operator);
	}
}

void re(Stack* pStack, Stack* reverse) {
	while (Stack_Top(pStack)) {
		Push(reverse, Pop(pStack));
	}
}

int calculate(Stack* pStack) {
	Stack* temp = CreateStack(100);
	while (!is_operator(Stack_Top(pStack) || pStack->top != -1)) {
		Push(temp, Pop(pStack));
	}
	char oper = Pop(pStack);
	if (is_operator(Stack_Top(pStack))) {
		return 0;
	}
	double b = Pop(temp) - '0';
	double a = Pop(temp) - '0';
	switch ((int)oper) {
	case '+':
		Push(pStack, a + b + '0');
		break;
	case '-':
		Push(pStack, a - b + '0');
		break;
	case '/':
		if (b == 0)
			return -1;
		Push(pStack, a / b + '0');
		break;
	case '*':
		Push(pStack, a * b + '0');
		break;
	}
	while (Stack_Top(temp)) {
		Push(pStack, Pop(temp));
	}
	DestroyStack(temp);
	return 1;
}



int main() {
	Stack* postfix = CreateStack(100);
	Stack* oper = CreateStack(100); 
	Stack* reverse = CreateStack(100);
	Stack* ans = CreateStack(100);
	char input[500];
	gets(input);
	if (strlen(input) == 0) return 0;
	int length = strlen(input);
	for (int i = 0; i < length - 1; i++) {
		if (is_operator(input[i]) && is_operator(input[i + 1])) {
			printf("INVALID_FORMULA");
			return 0;
		}
	}
	for (int i = 0; i < length; i++) {
		change(postfix, oper, input[i]);
	}
	while (Stack_Top(oper)) {
		Push(postfix, Pop(oper));
	}
	re(postfix, reverse);
	while (Stack_Top(reverse)) {
		int tmp = Pop(reverse);
		if (is_operator(tmp)) {
			double b = Pop(ans);
			double a = Pop(ans);
			if (tmp == '+') Push(ans, a + b);
			if (tmp == '-') Push(ans, a - b);
			if (tmp == '*') Push(ans, a * b);
			if (tmp == '/') if (b == 0) { printf("DIVIDED_BY_ZERO"); return 0; }
			else Push(ans, a / b);
		}
		else {
			Push(ans, tmp - '0');
		}
	}
	printf("%f", Pop(ans));
	DestroyStack(postfix);
	DestroyStack(oper);
	DestroyStack(reverse);
	DestroyStack(ans);
	return 0;
}