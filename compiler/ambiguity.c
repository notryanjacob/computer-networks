#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to check if the string follows the unambiguous grammar
bool checkUnambiguousGrammar(char *str, int n)
{
    int i = 0, j = n - 1;

    // Check if the string follows the pattern "a...b"
    while (i < j)
    {
        if (str[i] == 'a' && str[j] == 'b')
        {
            i++;
            j--;
        }
        else
        {
            return false; // Not matching the pattern
        }
    }

    // Check if the middle is reached and string is balanced
    if (i == j || i > j)
    {
        return true;
    }
    return false;
}

int main()
{
    char str[100];

    printf("Enter a string: ");
    scanf("%s", str);

    int n = strlen(str);

    if (checkUnambiguousGrammar(str, n))
    {
        printf("The string belongs to the unambiguous grammar.\n");
    }
    else
    {
        printf("The string does not belong to the unambiguous grammar.\n");
    }

    return 0;
}
