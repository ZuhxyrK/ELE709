#include <stdio.h>       /* for fprintf() */
#include <stdlib.h>      /* for exit() */
#include <unistd.h>      /* for sleep() */
#include <pthread.h>     /* for pthreads functions */

#define NTHREADS 3

int string_index = 0;

char string_to_print[] = "0123456789";

pthread_mutex_t fast_mutex = PTHREAD_MUTEX_INITIALIZER;


void *func(void *arg)
{
   int tmp_index;
   int pthread_mutex__lock(pthread_mutex_t *mutex);
   sleep(1);   /* sleep 1 sec to allow all threads to start */

   while (1) {
	   
	  pthread_mutex_lock(&fast_mutex);
	   
      tmp_index = string_index;

      if (!(tmp_index+1 > sizeof(string_to_print))) {
         printf("%c", string_to_print[tmp_index]);
         usleep(100);   /* sleep 1 usec */
      }
      
      string_index = tmp_index + 1;

      if (tmp_index+1 > sizeof(string_to_print)) {
         printf("\n");
         string_index = 0;   /* wrap around */
      }
      
     pthread_mutex_unlock(&fast_mutex);	   
   }
 

}


int main(void)
{
   pthread_t threads[NTHREADS];
   int k;

   for (k = 0; k < NTHREADS; k++) {
      printf("Starting Thread %d\n", k+1);
      if (pthread_create(&threads[k], NULL, &func, NULL) != 0) {
            printf("Error creating thread %d\n", k+1);
            exit(-1);
      }
   }

   sleep(20);   /* sleep 20 secs to allow time for the threads to run */
                /* before terminating them with pthread_cancel()      */

   for (k = 0; k < NTHREADS; k++) {
      pthread_cancel(threads[k]);
   }

   pthread_exit(NULL);
}
