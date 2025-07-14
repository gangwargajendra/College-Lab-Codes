#include <stdio.h>
#include <setjmp.h>

// Declare a jmp_buf to save the program state
jmp_buf env;

void risky_function(int value) {
    if (value == 0) {
        printf("Encountered an error: Division by zero is not allowed.\n");
        // Jump back to the saved state in main
        longjmp(env, 1);
    }
    printf("Result of 10 / %d = %d\n", value, 10 / value);
}

int main() {
    int val=7;
    // Save the current program state
    if (setjmp(env) == 0) {
        // First time execution will come here
        printf("Enter a non-zero integer: ");
        scanf("%d", &val);
        // Call a function that may cause an error
        risky_function(val);

        printf("Function completed successfully.\n");
    } else {
        // Execution comes here if longjmp is called
        printf("Recovered from an error. %d\n",val);
    }

    printf("Program continues execution after error handling.\n");
    return 0;
}