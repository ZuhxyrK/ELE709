#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

// Data structure to hold thread information
struct thread_info {
    int maxitr;
    char op;  // Operation to perform: '+', '-', '*', '/'
    double a, b, c;  // Input numbers and result
    double exec_time;  // Execution time per iteration in nanoseconds
};

typedef struct thread_info thread_info_t;

// Thread function
void *func(void *arg) {
    struct timespec time_1, time_2;
    thread_info_t *info;
    int i;

    info = (thread_info_t *)arg;
    info->c = 0.0;

    clock_gettime(CLOCK_REALTIME, &time_1);

    for (i = 0; i < info->maxitr; i++) {
        switch (info->op) {
            case '+':
                info->c = info->a + info->b;
                break;
            case '-':
                info->c = info->a - info->b;
                break;
            case '*':
                info->c = info->a * info->b;
                break;
            case '/':
                if (info->b != 0) {
                    info->c = info->a / info->b;
                }
                break;
            default:
                printf("Invalid operation\n");
                pthread_exit(NULL);
        }
    }

    clock_gettime(CLOCK_REALTIME, &time_2);

    info->exec_time = (time_2.tv_sec - time_1.tv_sec) * 1e9;  // Convert to nanoseconds
    info->exec_time += (time_2.tv_nsec - time_1.tv_nsec);
    info->exec_time /= info->maxitr;  // Execution time per iteration

    pthread_exit(NULL);
    return NULL; // Ensure proper handling of non-void return type
}

int main(void) {
    pthread_t threads[4];
    thread_info_t info[4];
    char operations[4] = {'+', '-', '*', '/'};
    double a = 2.3, b = 4.5;
    int maxitr = 500000000;  // Number of iterations

    // Initialize and create threads sequentially
    for (int i = 0; i < 4; i++) {
        info[i].a = a;
        info[i].b = b;
        info[i].op = operations[i];
        info[i].maxitr = maxitr;

        if (pthread_create(&threads[i], NULL, &func, &info[i]) != 0) {
            printf("Error in creating thread %d\n", i + 1);
            exit(1);
        }

        pthread_join(threads[i], NULL);

        printf("Thread %d (Operation %c):\n", i + 1, operations[i]);
        printf("Result: %lf\n", info[i].c);
        printf("Execution time per iteration: %.2lf ns\n\n", info[i].exec_time);
    }

    return 0; // Ensure proper termination of main function
}
