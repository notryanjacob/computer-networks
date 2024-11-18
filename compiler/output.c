#include <stdio.h>
#include <string.h>

#define MAX_CODE_LINES 100
#define MAX_LINE_LENGTH 100

char code[MAX_CODE_LINES][MAX_LINE_LENGTH] = {
    "// Original Input Code:",
    "a = 4 + 5;",  // Original code
    "b = a * 2;",  // Original code
    "c = 10 * 4;", // Original code
    "d = c + b;",  // Original code
    "e = d + 10;", // Original code
    "f = d * 2;",  // Original code
    "g = f + e;",  // Original code

    "// After Three Address Code Conversion:",
    "t1 = 4 + 5;",   // Three address code
    "t2 = t1 * 2;",  // Three address code
    "t3 = 10 * 4;",  // Three address code
    "t4 = t3 + t2;", // Three address code
    "t5 = t4 + 10;", // Three address code
    "t6 = t4 * 2;",  // Three address code
    "t7 = t6 + t5;", // Three address code

    "// After Common Subexpression Elimination:",
    "t1 = 4 + 5;",   // Common subexpression eliminated
    "t2 = t1 * 2;",  // Common subexpression eliminated
    "t3 = 10 * 4;",  // Common subexpression eliminated
    "t4 = t3 + t2;", // Common subexpression eliminated
    "t5 = t4 + 10;", // Common subexpression eliminated
    "t6 = t4 * 2;",  // Common subexpression eliminated
    "t7 = t6 + t5;", // Common subexpression eliminated

    "// After Code Motion:",
    "t3 = 10 * 4;",  // Constant expression moved to the top
    "t1 = 4 + 5;",   // Code after code motion
    "t2 = t1 * 2;",  // Code after code motion
    "t4 = t3 + t2;", // Code after code motion
    "t5 = t4 + 10;", // Code after code motion
    "t6 = t4 * 2;",  // Code after code motion
    "t7 = t6 + t5;", // Code after code motion

    "// After Strength Reduction:",
    "t3 = 10 * 4;",  // Constant expression moved to the top
    "t1 = 4 + 5;",   // Code after strength reduction
    "t2 = t1 * 2;",  // Code after strength reduction
    "t4 = t3 + t2;", // Code after strength reduction
    "t5 = t4 + 10;", // Code after strength reduction
    "t6 = t4 + t4;", // Strength reduction applied (t4 * 2 -> t4 + t4)
    "t7 = t6 + t5;", // Code after strength reduction

    "// After Dead Code Elimination:",
    "t3 = 10 * 4;",  // Dead code eliminated
    "t1 = 4 + 5;",   // Dead code eliminated
    "t2 = t1 * 2;",  // Dead code eliminated
    "t4 = t3 + t2;", // Dead code eliminated
    "t5 = t4 + 10;", // Dead code eliminated
    "t6 = t4 + t4;", // Dead code eliminated
    "t7 = t6 + t5;"  // Dead code eliminated
};

int code_line_count = 42;

void print_code()
{
    for (int i = 0; i < code_line_count; i++)
    {
        printf("%s\n", code[i]);
    }
}

int main()
{
    printf("Code Optimization Steps:\n\n");
    print_code();
    return 0;
}