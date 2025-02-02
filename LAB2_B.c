#include <stdio.h>
#include <time.h>

int main() {
    double a = 0, b = 0, c = 0; // Variables for the operation
    int maxitr = 500000000;         // Number of iterations
    char operation;                 // To store the chosen operation
    struct timespec start_time, stop_time;
    double elapsed_time, time_per_iteration;
 
     // Prompt users to select number 'a'
    printf("Choose a number for a: ");
    scanf(" %c", &a);
    
    // Prompt users to select number 'b'
    printf("Choose a number for b: ");
    scanf(" %c", &b);

    // Prompt user to select an operation
    printf("Choose an operation to time (+, -, *, /): ");
    scanf(" %c", &operation);

    // Start measuring time
    clock_gettime(CLOCK_REALTIME, &start_time);

    for (int i = 0; i < maxitr; i++) {
        switch (operation) {
            case '+':
                c = a + b;
                break;
            case '-':
                c = a - b;
                break;
            case '*':
                c = a * b;
                break;
            case '/':
                c = a / b;
                break;
            default:
                printf("Invalid operation. Please run the program again.\n");
                return 1;
        }
    }

    // Stop measuring time
    clock_gettime(CLOCK_REALTIME, &stop_time);

    // Calculate elapsed time in nanoseconds
    elapsed_time = (stop_time.tv_sec - start_time.tv_sec) * 1e9; // Seconds to nanoseconds
    elapsed_time += (stop_time.tv_nsec - start_time.tv_nsec);    // Add nanoseconds

    // Calculate time per iteration
    time_per_iteration = elapsed_time / maxitr;

    // Display results
    printf("Operation '%c' completed in %.2f nanoseconds per iteration.\n", operation, time_per_iteration);

    return 0;
}
