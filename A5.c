#include <stdio.h>
#include <ctype.h>
#include <string.h>
int limit, x = 0;
char production[10][10], array[10];
void find_first(char ch);
void find_follow(char ch);
void Array_Manipulation(char ch);
int array_contains_epsilon(char ch);
int main()
{
    int count;
    char ch;
    printf("\nEnter Total Number of Productions:\t");
    scanf("%d", &limit);
    for (count = 0; count < limit; count++)
    {
        printf("\nValue of Production Number [%d]:\t", count + 1);
        scanf("%s", production[count]);
    }
    printf("\nEnter production Value to Find First And Follow:\t");
    scanf(" %c", &ch);
    find_first(ch);
    printf("\nFirst Value of %c:\t{ ", ch);
    for (count = 0; count < x; count++)
    {
        printf("%c ", array[count]);
    }
    printf("}\n");
    x = 0; // Reset the array for Follow sets
    find_follow(ch);
    printf("\nFollow Value of %c:\t{ ", ch);
    for (count = 0; count < x; count++)
    {
        printf("%c ", array[count]);
    }
    printf("}\n");
     return 0;
}
// Function to find Follow sets
void find_follow(char ch)
{
    if (production[0][0] == ch)
    {
        Array_Manipulation('$');
    }
    for (int i = 0; i < limit; i++)
    {
        for (int j = 2; j < strlen(production[i]); j++)
        {
            if (production[i][j] == ch)
            {
                if (j + 1 < strlen(production[i]))
                {
                    // If there are more symbols in the production
                    find_first(production[i][j + 1]);
                    // If the symbol after 'ch' has epsilon in its First set, follow the non-terminal
                    if (array_contains_epsilon(production[i][j + 1]))
                    {
                        find_follow(production[i][0]);
                    }
                }
                else if (j + 1 == strlen(production[i]) && ch != production[i][0])
                {
                    // If 'ch' is the last symbol in the production
                    find_follow(production[i][0]);
                }
            }
        }
    }
}
// Function to find First sets
void find_first(char ch)
{
    if (!(isupper(ch)))
    {
        Array_Manipulation(ch);
    }
    for (int k = 0; k < limit; k++)
    {
        if (production[k][0] == ch)
        {
            if (production[k][2] == '$')
            {
                // If the production derives epsilon, add epsilon to the First set
                Array_Manipulation('$');
            }
            else if (islower(production[k][2]))
                
                {
                    Array_Manipulation(production[k][2]);
                }
            else
            {
                // If the first symbol of the production is a non-terminal
                find_first(production[k][2]);
            }
        }
    }
}
// Function to check if epsilon is in the First set of a symbol
int array_contains_epsilon(char ch)
{
    for (int count = 0; count < x; count++)
    {
        if (array[count] == '$')
        {
            return 1;
        }
    }
    return 0;
}
// Function to manipulate the array
void Array_Manipulation(char ch)
{
    int count;
    for (count = 0; count < x; count++)
    {
        if (array[count] == ch)
        {
            return;
        }
    }
    array[x++] = ch;
}