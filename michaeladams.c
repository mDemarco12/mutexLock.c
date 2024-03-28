/*
Name: Michael Adams

Summary: Implement a solution to the critical section problem for 2 threads using mutex locks OR semaphore. 
The threads will increment a counter, when thread1's counter is divisible by 100, it gets a bonus of 100.
Thread2 doesn't get this bonus. 
Each thread will count till 2000000 and the parent counter should reach a max value of 4000000.
Each thread will display then exit.
The program must satisfies the 3 conditions of the critical section solution 
(Mutual exclusion, progress, and bounded wait). 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Declare max updates and max count global 
#define MAX_UPDATES 2000000
#define MAX_COUNT 4000000

/* Struct for a shared variable to store result */
struct shared_data {
    int value;
};

/* Global shared variable */
struct shared_data *counter;

/* Mutex lock */
pthread_mutex_t mutex;

/* Thread1 function */
void *thread1() {
    int i = 0;
    int update = 0; //Value of updates
    int bonus = 0; //Value for bonus
    int local = 0;; //Local variable for counter->value

    while (i < MAX_UPDATES && update < MAX_UPDATES) {
        //Entry section 
        if (pthread_mutex_lock(&mutex) == 0) {
            //Critical section
            if ((counter->value % 100) == 0 && counter->value < MAX_COUNT) {
            
                // Bonus Round!
                counter->value += 100;
                local++; 
                bonus++;
            } else if (counter->value < MAX_COUNT) {
                // If not a bonus round and still below the max limit, increment as usual
                counter->value++;
                //increment local value
                local++; 
            }
            //Exit section
            pthread_mutex_unlock(&mutex);
            local++; 
            update++;
        }
        i++;
    }

    // Remainder section for thread1
    printf("Im thread1, I did %d updates and I got the bonus for %d times, counter = %d\n", update, bonus, local);

    //Exit the chat...
    return NULL;
}

/* Thread2 function */
void *thread2() {
    int i = 0;
    int update = 0; //Diito 

    
    while (i < MAX_UPDATES && update < MAX_UPDATES) {
        //Entry section　
        if (pthread_mutex_lock(&mutex) == 0) {
            //Critical section 
            if (counter->value < MAX_COUNT) {
                // Increment
                counter->value++;
            }

            //Exit section　
            pthread_mutex_unlock(&mutex);
            update++;
        }
        i++;
    }

    // Remainder section for thread2
    printf("Im thread2, I did %d updates, counter = %d\n", update, counter->value);

    //Exit the chat...
    return NULL;
}

int main() {
    pthread_t tid[2];
    int rc;

    /* Allocate memory for shared data */
    counter = (struct shared_data *)malloc(sizeof(struct shared_data));
    counter->value = 0;

    /* Initialize mutex lock */
    if ((pthread_mutex_init(&mutex, NULL))) {
        printf("Error occurred when initializing mutex lock.\n");
        exit(0);
    }

    pthread_attr_t attr;
    if ((pthread_attr_init(&attr))) {
        printf("Error occurred when initializing pthread_attr_t.\n");
        exit(0);
    }

    /* Create thread1 */
    if ((rc = pthread_create(&tid[0], &attr, thread1, NULL))) {
        fprintf(stderr, "ERROR: pthread_create, rc: %d\n", rc);
        exit(0);
    }

    /* Create thread2 */
    if ((rc = pthread_create(&tid[1], &attr, thread2, NULL))) {
        fprintf(stderr, "ERROR: pthread_create, rc: %d\n", rc);
        exit(0);
    }

    /* Wait for threads to finish */
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);


    // Print the final counter value from the parent
    printf("From parent counter = %d\n", counter->value);

    /* Clean up */
    pthread_mutex_destroy(&mutex);
    free(counter);
    pthread_exit(NULL);

    return 0;
}