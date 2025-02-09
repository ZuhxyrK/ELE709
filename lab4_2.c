#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_INDEX 10

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int string_index = 0;

void *thread_A(void *arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        
        while (string_index % 2 != 0) {
            pthread_cond_wait(&cond, &lock);
        }
        
        if (string_index >= MAX_INDEX) {
            pthread_mutex_unlock(&lock);
            break;
        }
        
        printf("A%c ", '0' + string_index);
        string_index++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thread_B(void *arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        
        while (string_index % 2 == 0) {
            pthread_cond_wait(&cond, &lock);
        }
        
        if (string_index >= MAX_INDEX) {
            pthread_mutex_unlock(&lock);
            break;
        }
        
        printf("B%c ", '0' + string_index);
        string_index++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void) {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_A, NULL);
    pthread_create(&thread2, NULL, thread_B, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    
    return 0;
}
