#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_SIZE 100

typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(char data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

Node *buildExpressionTree(char *expression, int *index, int isPrefix)
{
    if (*index >= strlen(expression))
    {
        return NULL;
    }

    Node *root = createNode(expression[*index]);

    if (isOperator(expression[*index]))
    {
        if (isPrefix)
        {
            (*index)++;
            root->left = buildExpressionTree(expression, index, isPrefix);
            (*index)++;
            root->right = buildExpressionTree(expression, index, isPrefix);
        }
        else
        {
            (*index)--;
            root->right = buildExpressionTree(expression, index, isPrefix);
            (*index)--;
            root->left = buildExpressionTree(expression, index, isPrefix);
        }
    }

    return root;
}

void inorderTraversal(Node *root)
{
    if (root)
    {
        if (isOperator(root->data))
            printf("(");
        inorderTraversal(root->left);
        printf("%c", root->data);
        inorderTraversal(root->right);
        if (isOperator(root->data))
            printf(")");
    }
}

void preorderTraversal(Node *root)
{
    if (root)
    {
        printf("%c", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(Node *root)
{
    if (root)
    {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%c", root->data);
    }
}

int main()
{
    char expression[MAX_EXPR_SIZE];
    printf("Enter an expression (infix, prefix, or postfix): ");
    fgets(expression, MAX_EXPR_SIZE, stdin);
    expression[strcspn(expression, "\n")] = 0;

    int len = strlen(expression);
    int index = 0;
    Node *root;

    if (isOperator(expression[0]))
    {
        // Prefix expression
        root = buildExpressionTree(expression, &index, 1);
        printf("\nPrefix expression: ");
        preorderTraversal(root);
        printf("\nInfix expression: ");
        inorderTraversal(root);
        printf("\nPostfix expression: ");
        postorderTraversal(root);
    }
    else if (isOperator(expression[len - 1]))
    {
        // Postfix expression
        index = len - 1;
        root = buildExpressionTree(expression, &index, 0);
        printf("\nPrefix expression: ");
        preorderTraversal(root);
        printf("\nInfix expression: ");
        inorderTraversal(root);
        printf("\nPostfix expression: ");
        postorderTraversal(root);
    }
    else
    {
        // Infix expression (not implemented in this example)
        printf("Infix to tree conversion not implemented in this example.\n");
        return 1;
    }

    printf("\n");
    return 0;
}