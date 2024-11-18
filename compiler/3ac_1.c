#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LEN 100
#define MAX_ADDR 50

typedef struct
{
    char op;
    char arg1[10];
    char arg2[10];
    char result[10];
} Quadruple;

typedef struct
{
    char op;
    char arg1[10];
    char arg2[10];
} Triple;

Quadruple quadruples[MAX_ADDR];
Triple triples[MAX_ADDR];
int indirectTriples[MAX_ADDR];
int quadCount = 0, tripleCount = 0;

int getPrecedence(char op)
{
    switch (op)
    {
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

void generateThreeAddressCode(char *expr)
{
    char opStack[MAX_EXPR_LEN];
    char argStack[MAX_EXPR_LEN][10];
    int opTop = -1, argTop = -1;
    int tempCount = 1;

    for (int i = 0; expr[i] != '\0'; i++)
    {
        if (isalnum(expr[i]))
        {
            char arg[2] = {expr[i], '\0'};
            strcpy(argStack[++argTop], arg);
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
        {
            while (opTop >= 0 && getPrecedence(opStack[opTop]) >= getPrecedence(expr[i]))
            {
                char op = opStack[opTop--];
                char arg2[10], arg1[10];
                strcpy(arg2, argStack[argTop--]);
                strcpy(arg1, argStack[argTop--]);

                char result[10];
                sprintf(result, "t%d", tempCount++);

                quadruples[quadCount].op = op;
                strcpy(quadruples[quadCount].arg1, arg1);
                strcpy(quadruples[quadCount].arg2, arg2);
                strcpy(quadruples[quadCount].result, result);

                triples[tripleCount].op = op;
                strcpy(triples[tripleCount].arg1, arg1);
                strcpy(triples[tripleCount].arg2, arg2);

                indirectTriples[tripleCount] = tripleCount;

                quadCount++;
                tripleCount++;

                strcpy(argStack[++argTop], result);
            }
            opStack[++opTop] = expr[i];
        }
    }

    while (opTop >= 0)
    {
        char op = opStack[opTop--];
        char arg2[10], arg1[10];
        strcpy(arg2, argStack[argTop--]);
        strcpy(arg1, argStack[argTop--]);

        char result[10];
        sprintf(result, "t%d", tempCount++);

        quadruples[quadCount].op = op;
        strcpy(quadruples[quadCount].arg1, arg1);
        strcpy(quadruples[quadCount].arg2, arg2);
        strcpy(quadruples[quadCount].result, result);

        triples[tripleCount].op = op;
        strcpy(triples[tripleCount].arg1, arg1);
        strcpy(triples[tripleCount].arg2, arg2);

        indirectTriples[tripleCount] = tripleCount;

        quadCount++;
        tripleCount++;

        strcpy(argStack[++argTop], result);
    }
}

void printQuadruples()
{
    printf("\nQuadruples:\n");
    printf("Op\tArg1\tArg2\tResult\tFull Expression\n");
    for (int i = 0; i < quadCount; i++)
    {
        printf("%c\t%s\t%s\t%s\t%s = %s %c %s\n",
               quadruples[i].op,
               quadruples[i].arg1,
               quadruples[i].arg2,
               quadruples[i].result,
               quadruples[i].result,
               quadruples[i].arg1,
               quadruples[i].op,
               quadruples[i].arg2);
    }
}

void printTriples()
{
    printf("\nTriples:\n");
    printf("Index\tOp\tArg1\tArg2\tFull Expression\n");
    for (int i = 0; i < tripleCount; i++)
    {
        printf("%d\t%c\t%s\t%s\tt%d = %s %c %s\n",
               i,
               triples[i].op,
               triples[i].arg1,
               triples[i].arg2,
               i + 1,
               triples[i].arg1,
               triples[i].op,
               triples[i].arg2);
    }
}

void printIndirectTriples()
{
    printf("\nIndirect Triples:\n");
    printf("Index\tTriple Index\tFull Expression\n");
    for (int i = 0; i < tripleCount; i++)
    {
        printf("%d\t%d\t\tt%d = %s %c %s\n",
               i,
               indirectTriples[i],
               i + 1,
               triples[i].arg1,
               triples[i].op,
               triples[i].arg2);
    }
}

int main()
{
    char expr[MAX_EXPR_LEN];
    printf("Enter an arithmetic expression: ");
    fgets(expr, MAX_EXPR_LEN, stdin);
    expr[strcspn(expr, "\n")] = 0; // Remove newline

    printf("\nInput Expression: %s\n", expr);

    generateThreeAddressCode(expr);
    printQuadruples();
    printTriples();
    printIndirectTriples();

    return 0;
}