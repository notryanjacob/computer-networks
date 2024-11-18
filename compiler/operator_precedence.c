#include <stdio.h>
#include <string.h>
//GENERATE OPERATOR PRECEDENCE TABLE

#define SIZE 6 // Number of terminals

// Terminals used in the grammar
char operators[] = {'i', '+', '*', '(', ')', '$'}; // 'i' is for 'id', '$' is end marker

// Precedence table - manually constructed based on the grammar
char precedenceTable[SIZE][SIZE];

// Get index of the operator in the precedence table
int getOperatorIndex(char op)
{
    switch (op)
    {
    case 'i':
        return 0; // id
    case '+':
        return 1; // +
    case '*':
        return 2; // *
    case '(':
        return 3; // (
    case ')':
        return 4; // )
    case '$':
        return 5; // End marker
    default:
        return -1;
    }
}

// Initialize the precedence table based on the precedence rules
void generatePrecedenceTable()
{
    int i, j;

    // Initialize all cells with ' ' (no relation)
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            precedenceTable[i][j] = ' ';
        }
    }

    // Define precedence rules:
    // 'i' = id, '$' = end marker

    // Relations with id ('i')
    precedenceTable[getOperatorIndex('i')][getOperatorIndex('+')] = '>';
    precedenceTable[getOperatorIndex('i')][getOperatorIndex('*')] = '>';
    precedenceTable[getOperatorIndex('i')][getOperatorIndex(')')] = '>';
    precedenceTable[getOperatorIndex('i')][getOperatorIndex('$')] = '>';

    // Relations with '+'
    precedenceTable[getOperatorIndex('+')][getOperatorIndex('i')] = '<';
    precedenceTable[getOperatorIndex('+')][getOperatorIndex('+')] = '>';
    precedenceTable[getOperatorIndex('+')][getOperatorIndex('*')] = '<';
    precedenceTable[getOperatorIndex('+')][getOperatorIndex('(')] = '<';
    precedenceTable[getOperatorIndex('+')][getOperatorIndex(')')] = '>';
    precedenceTable[getOperatorIndex('+')][getOperatorIndex('$')] = '>';

    // Relations with '*'
    precedenceTable[getOperatorIndex('*')][getOperatorIndex('i')] = '<';
    precedenceTable[getOperatorIndex('*')][getOperatorIndex('+')] = '>';
    precedenceTable[getOperatorIndex('*')][getOperatorIndex('*')] = '>';
    precedenceTable[getOperatorIndex('*')][getOperatorIndex('(')] = '<';
    precedenceTable[getOperatorIndex('*')][getOperatorIndex(')')] = '>';
    precedenceTable[getOperatorIndex('*')][getOperatorIndex('$')] = '>';

    // Relations with '('
    precedenceTable[getOperatorIndex('(')][getOperatorIndex('i')] = '<';
    precedenceTable[getOperatorIndex('(')][getOperatorIndex('+')] = '<';
    precedenceTable[getOperatorIndex('(')][getOperatorIndex('*')] = '<';
    precedenceTable[getOperatorIndex('(')][getOperatorIndex('(')] = '<';
    precedenceTable[getOperatorIndex('(')][getOperatorIndex(')')] = '=';

    // Relations with ')'
    precedenceTable[getOperatorIndex(')')][getOperatorIndex('+')] = '>';
    precedenceTable[getOperatorIndex(')')][getOperatorIndex('*')] = '>';
    precedenceTable[getOperatorIndex(')')][getOperatorIndex(')')] = '>';
    precedenceTable[getOperatorIndex(')')][getOperatorIndex('$')] = '>';

    // Relations with '$'
    precedenceTable[getOperatorIndex('$')][getOperatorIndex('i')] = '<';
    precedenceTable[getOperatorIndex('$')][getOperatorIndex('+')] = '<';
    precedenceTable[getOperatorIndex('$')][getOperatorIndex('*')] = '<';
    precedenceTable[getOperatorIndex('$')][getOperatorIndex('(')] = '<';
}

// Display the operator precedence parsing table
void displayPrecedenceTable()
{
    int i, j;

    // Print the header
    printf("  \t");
    for (i = 0; i < SIZE; i++)
    {
        printf("%c\t", operators[i]);
    }
    printf("\n");

    // Print the table with operators as row and column labels
    for (i = 0; i < SIZE; i++)
    {
        printf("%c\t", operators[i]);
        for (j = 0; j < SIZE; j++)
        {
            printf("%c\t", precedenceTable[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    // Generate the precedence table
    generatePrecedenceTable();

    // Display the generated precedence table
    printf("Operator Precedence Parsing Table:\n");
    displayPrecedenceTable();

    return 0;
}
