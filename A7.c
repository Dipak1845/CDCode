#include <stdio.h>
#include <string.h>

int main() {
    int i, j, k, n, top = 0, col, row;
    char stack[20], ip[10], opt[5][5][2], ter[10];
    for (i = 0; i < 5; i++) {
        stack[i] = '\0';
        ip[i] = '\0';
        for (j = 0; j < 5; j++) {
            opt[i][j][0] = '\0';
            opt[i][j][1] = '\0';
        }
    }
    printf("Enter the terminals (in the order they appear in the table):\n");
    scanf("%s", ter);
    
    printf("\nEnter the table values (Enter 'a' for error):\n");
    for (i = 0; i < strlen(ter); i++) {
        for (j = 0; j < strlen(ter); j++) {
            printf("Enter the value for %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }
    
    printf("\n**** OPERATOR PRECEDENCE TABLE ****\n");
    printf("\t");
    for (i = 0; i < strlen(ter); i++) {
        printf("\t%c", ter[i]);
    }
    printf("\n");
    for (i = 0; i < strlen(ter); i++) {
        printf("%c", ter[i]);
        for (j = 0; j < strlen(ter); j++) {
            printf("\t%s", opt[i][j]);
        }
        printf("\n");
    }
    
    stack[top] = '$';
    printf("\nEnter the input string: ");
    scanf("%s", ip);
    
    i = 0;
    printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n");
    printf("\n%s\t\t\t%s\t\t\t", stack, ip);
    
    while (i <= strlen(ip)) {
        for (k = 0; k < strlen(ter); k++) {
            if (stack[top] == ter[k])
                col = k;
            if (ip[i] == ter[k])
                row = k;
        }
        if ((stack[top] == '$') && (ip[i] == '$')) {
            printf("String is accepted\n");
            break;
        } else if ((opt[col][row][0] == '<') || (opt[col][row][0] == '=')) {
            stack[++top] = ip[i];
            stack[++top] = opt[col][row][0];
            printf("Shift %c", ip[i]);
            i++;
        } else {
            if (opt[col][row][0] == '>') {
                while (stack[top] != '<') {
                    --top;
                }
                top = top - 1;
                printf("Reduce");
            } else {
                printf("\nString is not accepted");
                break;
            }
        }
        printf("\n");
        for (k = 0; k <= top; k++) {
            printf("%c", stack[k]);
        }
        printf("\t\t\t");
        for (k = i; k < strlen(ip); k++) {
            printf("%c", ip[k]);
        }
        printf("\t\t\t");
    }
    
    return 0;
}
