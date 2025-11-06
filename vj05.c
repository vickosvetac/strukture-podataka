#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//struct
typedef struct Node {
    int data;
    struct Node *next;
} Node;

//prototipi funkc
Node* push(Node *top, int value);
Node* pop(Node *top, int *value);
int evaluatePostfix(const char *filename);
int isOperator(char c);
int applyOperator(int a, int b, char op);

//funkc

//push element
Node* push(Node *top, int value) {
    Node *newNode;
    newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("error\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = top;
    top = newNode;
    return top;
}

// Pop element
Node* pop(Node *top, int *value) {
    Node *temp;
    if (top == NULL) {
        printf("Stack underflow!\n");
        exit(1);
    }
    *value = top->data;
    temp = top;
    top = top->next;
    free(temp);
    return top;
}

//provjeravanje operatora
int isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return 1;
    else
        return 0;
}

//postavljanje operatora na 2 elementa
int applyOperator(int a, int b, char op) {
    int result;
    if (op == '+') result = a + b;
    else if (op == '-') result = a - b;
    else if (op == '*') result = a * b;
    else if (op == '/') result = a / b;
    else {
        printf("Unknown operator: %c\n", op);
        exit(1);
    }
    return result;
}

//postfix expression from file
int evaluatePostfix(const char *filename) {
    FILE *f;
    Node *stackTop = NULL;
    char token[20];
    int a, b, result;

    f = fopen(filename, "r");
    if (f == NULL) {
        printf("error\n");
        exit(1);
    }

    while (fscanf(f, "%s", token) == 1) {
        if (isdigit(token[0]) || 
           (token[0] == '-' && isdigit(token[1]))) {
            // Token is a number
            stackTop = push(stackTop, atoi(token));
        } else if (isOperator(token[0]) && token[1] == '\0') {
            // Token is an operator
            stackTop = pop(stackTop, &b);
            stackTop = pop(stackTop, &a);
            result = applyOperator(a, b, token[0]);
            stackTop = push(stackTop, result);
        } else {
            printf("Invalid token: %s\n", token);
            fclose(f);
            exit(1);
        }
    }
    fclose(f);

    stackTop = pop(stackTop, &result);

    if (stackTop != NULL) {
        printf("previse brojeva\n");
        exit(1);
    }

    return result;
}

//glavna funkc
int main() {
    int result;
    result = evaluatePostfix("postfix.txt");
    printf("Result: %d\n", result);
    return 0;
}
