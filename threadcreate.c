#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10
#define NUM_THREADS 2

int A[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9,10};
int B[ARRAY_SIZE] = {10,20,30,40,50,60,70,80,90,100};
int C[ARRAY_SIZE];

typedef struct{
    int thread_id;
} ThreadData;

void sum_array(void* arg){
    ThreadData *data = (ThreadData*) arg;
    int id = data->thread_id;

    int chunk_size = ARRAY_SIZE/ NUM_THREADS;
    int start = id*chunk_size;
    int end = start + chunk_size;

    if(id==NUM_THREADS - 1){
        end = ARRAY_SIZE;
    }

    printf("Thread %d processing indices %d to %d\n", id, start, end-1);
    for(int i = start ; i< end, i++){
        C[i] = A[i] + B[i];

    }
    pthread_exit(NULL);
}


int main(){
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    for(int i = 0; i< NUM_THREADS, i++){
        thread_Data[i].thread_id = i;
        int rc = pthread_create(&threads[i], NULL, sum_arrays, (void*)&thread_data[i]);

        if(rc){
            printf("ERROR: Unable to create thread, %d\n", rc);
            exit(-1);        }
    }
    for(int i = 0; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);

    }

    printf("\nResults:\n");
    printf("Array A: ");
    for(int i = 0; i< ARRAY_SIZE; i++){
        printf("%d", A[i]);
    }
    printf("\nArray B: ");
    for(int i = 0; i<ARRAY_SIZE; i++){
        printf("%d", B[i]);
    }
    
    printf("\nSum C:   ");
    for(int i = 0; i < ARRAY_SIZE; i++){ printf("%d ", C[i]);
    }
    printf("\n");

    return 0;
}