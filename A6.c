#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

// Define the grammar rules
char prod[3][10] = {"A->aBa", "B->bB", "B->&"};

// Define the non-terminals
char non_terminals[3] = {'A', 'B'};

// Define the terminals
char terminals[3] = {'a', '$'};

// Define the First and Follow sets
int first[3][3] = {{1, 0, 0}, {1, 0, 1}, {0, 0, 1}};
int follow[3][3] = {{0, 1, 1}, {0, 0, 1}, {0, 0, 0}};

// Define the parsing table
int parse_table[3][3] = {{1, 2, 0}, {3, 3, 0}, {0, 0, 0}};

char stack[MAX_STACK_SIZE];
int top = -1;

// Push an item onto the stack
void push(char item) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = item;
    printf("Pushing %c onto the stack\n", item);
}

// Pop an item from the stack
char pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    char item = stack[top--];
    printf("Popping %c from the stack\n", item);
    return item;
}

// Check if the stack is empty
int is_empty() {
    return top == -1;
}

// Parse the input string
void parse(char *input) {
    stack[++top] = '$';
    stack[++top] = '#';
    stack[++top] = 'A'; // Start symbol

    while (*input != '\0') {
        char token = *input++;

        if (token == stack[top]) {
            pop();
        } else {
            int row = -1, col = -1;
            for (int i = 0; i < 3; i++) {
                if (stack[top] == non_terminals[i]) {
                    row = i;
                    break;
                }
            }
            for (int j = 0; j < 3; j++) {
                if (token == terminals[j]) {
                    col = j;
                    break;
                }
            }
            if (row != -1 && col != -1) {
                int rule = parse_table[row][col];
                if (rule != 0) {
                    pop();
                    char production[10];
                    strcpy(production, prod[rule - 1]);
                    for (int i = strlen(production) - 1; i >= 3; i--) {
                        if (production[i] != '&') {
                            push(production[i]);
                        }
                    }
                } else {
                    printf("Error: Invalid input string\n");
                    return;
                }
            } else {
                printf("Error: Invalid input string\n");
                return;
            }
        }
    }

    if (is_empty() && stack[top] == '#') {
        printf("The input string is valid\n");
    } else {
        printf("Error: Invalid input string\n");
    }
}

int main() {
    char input[10];
    printf("Enter the input string: ");
    scanf("%s", input);
    parse(input);
    return 0;
}
