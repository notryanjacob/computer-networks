// CODE TO ACCEPT A STRING USING OPERATOR PRECEDENCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define precedence relations
char precedence[7][7] = {
    //   id   +    *    (    )    $
    /*id*/ {' ', '>', '>', ' ', '>', '>'},
    /* + */ {'<', '>', '<', '<', '>', '>'},
    /* * */ {'<', '>', '>', '<', '>', '>'},
    /* ( */ {'<', '<', '<', '<', '=', ' '},
    /* ) */ {' ', '>', '>', ' ', '>', '>'},
    /* $ */ {'<', '<', '<', '<', ' ', 'A'}};

// Character indices for table lookup
int getIndex(char ch)
{
    switch (ch)
    {
    case 'i':
        return 0; // id is represented by 'i'
    case '+':
        return 1;
    case '*':
        return 2;
    case '(':
        return 3;
    case ')':
        return 4;
    case '$':
        return 5;
    default:
        return -1;
    }
}

// Stack implementation
char stack[100];
int top = -1;

void push(char ch)
{
    stack[++top] = ch;
}

char pop()
{
    return stack[top--];
}

char peek()
{
    return stack[top];
}

// Function to check precedence relation
char checkPrecedence(char a, char b)
{
    int i = getIndex(a);
    int j = getIndex(b);
    if (i == -1 || j == -1)
    {
        return ' '; // Invalid character
    }
    return precedence[i][j];
}

// Function to handle parsing
int operatorPrecedenceParsing(char *input)
{
    push('$'); // End marker on stack
    char *ip = input;
    char symbol = *ip;

    while (symbol != '\0')
    {
        char topSymbol = peek();
        char relation = checkPrecedence(topSymbol, symbol);

        if (relation == '<' || relation == '=')
        {
            // Shift the symbol
            push(symbol);
            ip++;
            symbol = *ip;
        }
        else if (relation == '>')
        {
            // Reduce (Pop from stack)
            while (peek() != '$' && checkPrecedence(peek(), symbol) == '>')
            {
                pop();
            }
        }
        else
        {
            // Invalid input
            return 0;
        }
    }

    // Check for valid expression at the end
    if (peek() != '$')
    {
        return 0; // Invalid expression if the stack is not empty
    }

    return 1;
}

int main()
{
    char input[100];

    printf("Enter an expression (without spaces): ");
    scanf("%s", input);

    // Append end marker
    strcat(input, "$");

    if (operatorPrecedenceParsing(input))
    {
        printf("The input expression is valid.\n");
    }
    else
    {
        printf("The input expression is invalid.\n");
    }

    return 0;
}
