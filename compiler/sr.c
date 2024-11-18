#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 100
#define MAX_PRODUCTIONS 10
#define MAX_SYMBOLS 10
#define MAX_STATES 10

typedef struct
{
    char left;
    char right[10];
} Production;

Production productions[MAX_PRODUCTIONS];
int num_productions = 0;

char stack[MAX_STACK_SIZE];
int top = -1;

char input[MAX_INPUT_SIZE];
int input_pos = 0;

char symbols[MAX_SYMBOLS];
int num_symbols = 0;

typedef enum
{
    ACTION_SHIFT,
    ACTION_REDUCE,
    ACTION_ACCEPT,
    ACTION_ERROR
} Action;

typedef struct
{
    Action action;
    int value; // State for shift, production number for reduce
} TableEntry;

TableEntry sr_table[MAX_STATES][MAX_SYMBOLS];

// Stack operations
void push(char item)
{
    if (top >= MAX_STACK_SIZE - 1)
    {
        printf("Stack overflow\n");
        exit(1);
    }
    stack[++top] = item;
}

char pop()
{
    if (top < 0)
    {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

void add_symbol(char symbol)
{
    for (int i = 0; i < num_symbols; i++)
    {
        if (symbols[i] == symbol)
            return;
    }
    symbols[num_symbols++] = symbol;
}

void add_production(char left, const char *right)
{
    if (num_productions < MAX_PRODUCTIONS)
    {
        productions[num_productions].left = left;
        strcpy(productions[num_productions].right, right);
        num_productions++;
        add_symbol(left);
        for (int i = 0; right[i] != '\0'; i++)
        {
            add_symbol(right[i]);
        }
    }
    else
    {
        printf("Max productions reached\n");
        exit(1);
    }
}

int symbol_index(char symbol)
{
    for (int i = 0; i < num_symbols; i++)
    {
        if (symbols[i] == symbol)
            return i;
    }
    return -1;
}

void generate_sr_table()
{
    // Initialize table with errors
    for (int i = 0; i < MAX_STATES; i++)
    {
        for (int j = 0; j < MAX_SYMBOLS; j++)
        {
            sr_table[i][j].action = ACTION_ERROR;
            sr_table[i][j].value = -1;
        }
    }

    // Populate SR table with shift/reduce actions (example for the grammar)
    // You would need to adapt this table to match your grammar

    // State 0
    sr_table[0][symbol_index('a')].action = ACTION_SHIFT;
    sr_table[0][symbol_index('a')].value = 1;

    // State 1
    sr_table[1][symbol_index('b')].action = ACTION_SHIFT;
    sr_table[1][symbol_index('b')].value = 2;

    // State 2
    sr_table[2][symbol_index('c')].action = ACTION_SHIFT;
    sr_table[2][symbol_index('c')].value = 3;
    sr_table[2][symbol_index('A')].action = ACTION_SHIFT;
    sr_table[2][symbol_index('A')].value = 5;

    // State 3
    sr_table[3][symbol_index('d')].action = ACTION_REDUCE;
    sr_table[3][symbol_index('d')].value = 1; // A -> bc
    sr_table[3][symbol_index('$')].action = ACTION_REDUCE;
    sr_table[3][symbol_index('$')].value = 1; // A -> bc

    // State 4
    sr_table[4][symbol_index('$')].action = ACTION_ACCEPT;

    // State 5
    sr_table[5][symbol_index('c')].action = ACTION_SHIFT;
    sr_table[5][symbol_index('c')].value = 6;

    // State 6
    sr_table[6][symbol_index('d')].action = ACTION_REDUCE;
    sr_table[6][symbol_index('d')].value = 2; // A -> bAc
    sr_table[6][symbol_index('$')].action = ACTION_REDUCE;
    sr_table[6][symbol_index('$')].value = 2; // A -> bAc
}

void print_sr_table()
{
    printf("\nSR Table:\n");
    printf("State\t");
    for (int i = 0; i < num_symbols; i++)
    {
        printf("%c\t", symbols[i]);
    }
    printf("\n");

    for (int i = 0; i < MAX_STATES; i++)
    {
        printf("%d\t", i);
        for (int j = 0; j < num_symbols; j++)
        {
            switch (sr_table[i][j].action)
            {
            case ACTION_SHIFT:
                printf("s%d\t", sr_table[i][j].value);
                break;
            case ACTION_REDUCE:
                printf("r%d\t", sr_table[i][j].value);
                break;
            case ACTION_ACCEPT:
                printf("acc\t");
                break;
            case ACTION_ERROR:
                printf("  \t");
                break;
            }
        }
        printf("\n");
    }
}

void parse()
{
    int state = 0;
    push('$'); // End marker
    push('0'); // Initial state (as a char)

    while (1)
    {
        char current_symbol = (input[input_pos] != '\0') ? input[input_pos] : '$';
        int symbol_idx = symbol_index(current_symbol);

        TableEntry entry = sr_table[state][symbol_idx];

        // Print stack
        for (int i = 0; i <= top; i++)
        {
            printf("%c", stack[i]);
        }
        printf("\t");

        // Print input
        for (int i = input_pos; input[i] != '\0'; i++)
        {
            printf("%c", input[i]);
        }
        printf("$\t");

        // Parse actions
        switch (entry.action)
        {
        case ACTION_SHIFT:
            printf("Shift %d\n", entry.value);
            push(current_symbol);
            push(entry.value + '0'); // Convert state to char
            state = entry.value;
            input_pos++;
            break;
        case ACTION_REDUCE:
            printf("Reduce %d\n", entry.value);
            for (int i = 0; i < strlen(productions[entry.value - 1].right) * 2; i++)
            {
                pop(); // Pop twice for each symbol (symbol and state)
            }
            int prev_state = stack[top] - '0';
            push(productions[entry.value - 1].left);
            int goto_state = sr_table[prev_state][symbol_index(productions[entry.value - 1].left)].value;
            push(goto_state + '0'); // Convert state to char
            state = goto_state;
            break;
        case ACTION_ACCEPT:
            printf("Accept\n");
            return;
        case ACTION_ERROR:
            printf("Reject\n");
            return;
        }
    }
}

int main()
{
    // Define grammar
    add_production('S', "aAd");
    add_production('A', "bc");
    add_production('A', "bAc");
    add_symbol('$'); // End of input symbol

    generate_sr_table();
    print_sr_table();

    printf("Enter input string: ");
    scanf("%s", input);

    printf("Stack\tInput\tAction\n");
    parse();

    return 0;
}
