// #include <stdio.h>
// #include <pthread.h>    // header file for multithreading
// #include <semaphore.h>
// #include <unistd.h>

// // sem_t struct is alreading defined inside of the <semaphore.h>

// sem_t mutex; 

// void* thread(void* arg)
// {
//     //wait
//     sem_wait(&mutex);   // lock or wait
//     printf("\nEntered...\n");

//     //important 
//     sleep(4); 

//     //signal - which we had discussed in the previous video also
//     printf("\n Just Exiting\n");
//     sem_post(&mutex); // this is used to release the signal. 
// }

// int main() {
//     sem_init(&mutex, 0, 1);
//     pthread_t t1, t2, t3; // let us create three threads
//     pthread_create(&t1, NULL, thread, NULL);
//     sleep(2);
//     pthread_create(&t2, NULL, thread, NULL);
//     sleep(2);
//     pthread_create(&t3, NULL, thread, NULL);
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
//     pthread_join(t3, NULL);
//     sem_destroy(&mutex);    // destroy the semaphore

//     return 0 ;
// }

/*
*   The Single Producer-Consumer Problem
*   1. Shared Buffer
*   2. Producer Thread
*   3. Consumer Thread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>        // we will use this to create the producer and consumer threads
#include <semaphore.h>
#include <unistd.h>         // this header file has the sleep() function definition.

#define MAX_SIZE 10

sem_t mutex;
int queue[MAX_SIZE];
int front = -1, rear = -1;

int isFull()
{
    return (rear+1)%MAX_SIZE == front;
}

int isEmpty()
{
    return front == -1;
}

// function to enqueue(insert) an element
void* enqueue(void* arg) {
    
    if(isFull()) {
        printf("Queue Overflow");
        return 0;
    }

    if(front == -1) {
        front = 0;
    }

    rear = (rear+1)%MAX_SIZE;
    printf("Buffer can be shared\n");
}

// function to dequeue(remove) an element
void* dequeue(void* arg) {
    
    if(isEmpty()) {
        printf("Queue underflow\n");
        printf("Buffer cannot be shared now");
        exit(1);
    }

    if(front == rear) {
        front = rear = -1;
    }else {
        front = (front+1)%MAX_SIZE;
    }
}



int main() {
    sem_init(&mutex, 0, 1);
    pthread_t thread_producer, thread_consumer;
    
    pthread_create(&thread_producer, NULL, enqueue, NULL);
    sleep(2);

    pthread_create(&thread_producer, NULL, enqueue, NULL);
    sleep(2);

    pthread_create(&thread_consumer, NULL, dequeue, NULL);
    sleep(2);

    pthread_create(&thread_consumer, NULL, dequeue, NULL);
    sleep(2);

    pthread_create(&thread_consumer, NULL, dequeue, NULL);
    pthread_join(thread_producer, NULL);
    pthread_join(thread_consumer, NULL);

    sem_destroy(&mutex);

    return 0;
}


