#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_SIZE 100
#define MAX_HEIGHT 10
#define MAX_WIDTH 100

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
    if (*index >= strlen(expression) || *index < 0)
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

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getHeight(Node *root)
{
    if (root == NULL)
        return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

void printTree(Node *root, int space[], int height, int depth)
{
    if (root == NULL)
        return;

    printTree(root->right, space, height, depth + 1);

    for (int i = 0; i < depth; i++)
    {
        if (i == depth - 1)
        {
            printf("|");
        }
        else if (space[i] == 1)
        {
            printf("|");
        }
        else
        {
            printf(" ");
        }
        printf("   ");
    }
    printf("%c\n", root->data);

    if (depth < height - 1)
    {
        space[depth] = 1;
    }

    printTree(root->left, space, height, depth + 1);

    if (depth < height - 1)
    {
        space[depth] = 0;
    }
}

void displayTree(Node *root)
{
    int height = getHeight(root);
    int space[MAX_HEIGHT] = {0};
    printf("\nSyntax Tree:\n");
    printTree(root, space, height, 0);
}

int main()
{
    char expression[MAX_EXPR_SIZE];
    printf("Enter an expression (prefix or postfix): ");
    fgets(expression, MAX_EXPR_SIZE, stdin);
    expression[strcspn(expression, "\n")] = 0;

    int len = strlen(expression);
    int index = 0;
    Node *root;

    if (isOperator(expression[0]))
    {
        // Prefix expression
        root = buildExpressionTree(expression, &index, 1);
    }
    else if (isOperator(expression[len - 1]))
    {
        // Postfix expression
        index = len - 1;
        root = buildExpressionTree(expression, &index, 0);
    }
    else
    {
        printf("Invalid expression. Please enter a valid prefix or postfix expression.\n");
        return 1;
    }

    printf("\nPrefix expression: ");
    preorderTraversal(root);
    printf("\nInfix expression: ");
    inorderTraversal(root);
    printf("\nPostfix expression: ");
    postorderTraversal(root);
    printf("\n");

    displayTree(root);

    return 0;
}