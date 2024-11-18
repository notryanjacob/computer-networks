#include <stdio.h>
#include <string.h>

struct instruction
{
    char opcode[10];
    char operand1[10];
    char operand2[10];
};

void peephole_optimization(struct instruction code[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (strcmp(code[i].opcode, "MOV") == 0 && strcmp(code[i + 1].opcode, "MOV") == 0)
        {
            if (strcmp(code[i].operand1, code[i + 1].operand2) == 0 && strcmp(code[i].operand2, code[i + 1].operand1) == 0)
            {
                for (int j = i + 1; j < n - 1; j++)
                {
                    code[j] = code[j + 1];
                }
                n--;
            }
        }

        if (strcmp(code[i].opcode, "JMP") == 0 && strcmp(code[i + 1].opcode, "LABEL") == 0)
        {
            if (strcmp(code[i].operand1, code[i + 1].operand1) == 0)
            {
                for (int j = i; j < n - 1; j++)
                {
                    code[j] = code[j + 1];
                }
                n--;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%s %s, %s\n", code[i].opcode, code[i].operand1, code[i].operand2);
    }
}

int main()
{
    struct instruction code[] = {
        {"MOV", "A", "B"},
        {"MOV", "B", "A"},
        {"JMP", "LABEL1", ""},
        {"LABEL", "LABEL1", ""},
        {"MOV", "C", "D"}};

    int n = 5;

    for (int i = 0; i < n; i++)
    {
        printf("%s %s, %s\n", code[i].opcode, code[i].operand1, code[i].operand2);
    }

    peephole_optimization(code, n);

    return 0;
}