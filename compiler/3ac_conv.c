#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_CODE_LINES 100
#define MAX_LINE_LENGTH 100
#define MAX_VAR_NAME 10

char code[MAX_CODE_LINES][MAX_LINE_LENGTH];
int code_line_count = 0;

// Function Prototypes
void convert_to_three_address_code();
void common_subexpression_elimination();
void dead_code_elimination();
void code_motion();
void strength_reduction();
void print_code();
bool is_arithmetic_op(char op);

int main()
{
    // Hardcoded input value for demonstration
    code_line_count = 1;
    strcpy(code[0], "x = (a + b) - (c * d);");

    printf("Original Code:\n");
    print_code();

    convert_to_three_address_code();
    printf("\nThree-Address Code:\n");
    print_code();

    common_subexpression_elimination();
    printf("\nAfter Common Subexpression Elimination:\n");
    print_code();

    dead_code_elimination();
    printf("\nAfter Dead Code Elimination:\n");
    print_code();

    code_motion();
    printf("\nAfter Code Motion:\n");
    print_code();

    strength_reduction();
    printf("\nAfter Strength Reduction:\n");
    print_code();

    return 0;
}

void convert_to_three_address_code()
{
    char temp_code[MAX_CODE_LINES][MAX_LINE_LENGTH];
    int temp_code_count = 0;

    for (int i = 0; i < code_line_count; i++)
    {
        char lhs[MAX_LINE_LENGTH], op1[MAX_LINE_LENGTH], op2[MAX_LINE_LENGTH], op3[MAX_LINE_LENGTH], op4[MAX_LINE_LENGTH];

        if (sscanf(code[i], "%[^ ] = (%[^ ] + %[^)]) - (%[^ ] * %[^)]);", lhs, op1, op2, op3, op4) == 5)
        {
            sprintf(temp_code[temp_code_count++], "t1 = %s + %s", op1, op2);
            sprintf(temp_code[temp_code_count++], "t2 = %s * %s", op3, op4);
            sprintf(temp_code[temp_code_count++], "t3 = t1 - t2");
            sprintf(temp_code[temp_code_count++], "%s = t3", lhs);
        }
        else
        {
            strcpy(temp_code[temp_code_count++], code[i]);
        }
    }

    code_line_count = temp_code_count;
    for (int i = 0; i < code_line_count; i++)
    {
        strcpy(code[i], temp_code[i]);
    }
}

void common_subexpression_elimination()
{
    for (int i = 0; i < code_line_count; i++)
    {
        for (int j = i + 1; j < code_line_count; j++)
        {
            char lhs1[MAX_VAR_NAME], op1[MAX_VAR_NAME], op2[MAX_VAR_NAME];
            char lhs2[MAX_VAR_NAME], op3[MAX_VAR_NAME], op4[MAX_VAR_NAME];
            char op;

            if (sscanf(code[i], "%[^ ] = %[^ ] %c %[^;];", lhs1, op1, &op, op2) == 4 &&
                sscanf(code[j], "%[^ ] = %[^ ] %c %[^;];", lhs2, op3, &op, op4) == 4)
            {
                if (strcmp(op1, op3) == 0 && strcmp(op2, op4) == 0)
                {
                    sprintf(code[j], "%s = %s;", lhs2, lhs1);
                }
            }
        }
    }
}

void dead_code_elimination()
{
    bool used[MAX_CODE_LINES] = {false};

    // Mark the last assignment as used
    used[code_line_count - 1] = true;

    // Iterate backwards to mark used variables
    for (int i = code_line_count - 1; i >= 0; i--)
    {
        if (used[i])
        {
            char lhs[MAX_VAR_NAME], rhs[MAX_LINE_LENGTH];
            if (sscanf(code[i], "%[^ ] = %[^;];", lhs, rhs) == 2)
            {
                // Mark all variables in rhs as used
                char *token = strtok(rhs, " ");
                while (token != NULL)
                {
                    for (int j = 0; j < i; j++)
                    {
                        if (strstr(code[j], token) != NULL)
                        {
                            used[j] = true;
                        }
                    }
                    token = strtok(NULL, " ");
                }
            }
        }
    }

    // Remove unused lines
    int new_count = 0;
    for (int i = 0; i < code_line_count; i++)
    {
        if (used[i])
        {
            strcpy(code[new_count++], code[i]);
        }
    }
    code_line_count = new_count;
}

void code_motion()
{
    // For simplicity, we'll just move constant computations to the beginning
    char temp_code[MAX_CODE_LINES][MAX_LINE_LENGTH];
    int temp_code_count = 0;
    int constant_count = 0;

    for (int i = 0; i < code_line_count; i++)
    {
        char lhs[MAX_VAR_NAME], op1[MAX_VAR_NAME], op2[MAX_VAR_NAME];
        char op;

        if (sscanf(code[i], "%[^ ] = %[^ ] %c %[^;];", lhs, op1, &op, op2) == 4)
        {
            if (isdigit(op1[0]) && isdigit(op2[0]))
            {
                sprintf(temp_code[constant_count++], "%s", code[i]);
            }
            else
            {
                strcpy(temp_code[temp_code_count++], code[i]);
            }
        }
        else
        {
            strcpy(temp_code[temp_code_count++], code[i]);
        }
    }

    // Copy constants back to the beginning
    for (int i = 0; i < constant_count; i++)
    {
        strcpy(code[i], temp_code[i]);
    }

    // Copy the rest of the code
    for (int i = 0; i < temp_code_count; i++)
    {
        strcpy(code[i + constant_count], temp_code[i + constant_count]);
    }

    code_line_count = constant_count + temp_code_count;
}

void strength_reduction()
{
    for (int i = 0; i < code_line_count; i++)
    {
        char lhs[MAX_VAR_NAME], op1[MAX_VAR_NAME], op2[MAX_VAR_NAME];
        char op;

        if (sscanf(code[i], "%[^ ] = %[^ ] %c %[^;];", lhs, op1, &op, op2) == 4)
        {
            if (op == '*' && strcmp(op2, "2") == 0)
            {
                sprintf(code[i], "%s = %s + %s;", lhs, op1, op1);
            }
            else if (op == '*' && strcmp(op2, "4") == 0)
            {
                sprintf(code[i], "%s = %s + %s;\n%s = %s + %s;", lhs, op1, op1, lhs, lhs, lhs);
                code_line_count++;
            }
        }
    }
}

void print_code()
{
    for (int i = 0; i < code_line_count; i++)
    {
        printf("%s\n", code[i]);
    }
}

bool is_arithmetic_op(char op)
{
    return op == '+' || op == '-' || op == '*' || op == '/';
}