/*
* @file :   "Hilos.c"
* @author : Luciano  Flores  Castillo
            Cristian Herrera Leizgold
* @date :   8/11/2020
* @brief :  Código para la parte B de la tarea 1 en ELO 321, semestre 2020-2
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define LENGTH 50
#define MAXVAL 100
#define N_THREADS 3

float avg_value_global;
int min_value_global;
int max_value_global;

int numArray[LENGTH];

void* returnAvgGlobal(void *arg);
void* returnMinGlobal(void *arg);
void* returnMaxGlobal(void *arg);

void* returnAvgLocal(void *arg);
void* returnMinLocal(void *arg);
void* returnMaxLocal(void *arg);

int main(int argc, char* argv[]){

    if(argc < 2){
        printf("Usage global variable: <executable> G \n");
        printf("Usage local variable: <executable> L \n");
        return 0;
    }

    int i;
    for(i=0; i<LENGTH; i++){
        numArray[i] = (rand() % MAXVAL) + 1;
    }
    pthread_t threadID[N_THREADS];
    pthread_attr_t attr[N_THREADS];

    if (*argv[1] == 'G'){ // Version Variables Globales --------------------
        printf("you chose global \n");

        for(i=0; i<N_THREADS; i++){
            pthread_attr_init(&attr[i]);
            switch (i)
            {
            case 0:
                pthread_create(&threadID[i], &attr[i], returnAvgGlobal, "");
                break;
            case 1:
                pthread_create(&threadID[i], &attr[i], returnMinGlobal, "");
                break;
            case 2:
                pthread_create(&threadID[i], &attr[i], returnMaxGlobal, "");
                break;

            default:
                break;
            }
        }
    } else if(*argv[1] == 'L'){ // Version Variables Locales ---------------
        printf("you chose local \n");

        float* avg_value_local = malloc(sizeof(float));
        int*   min_value_local = malloc(sizeof(int));
        int*   max_value_local = malloc(sizeof(int));

        for(i=0; i<N_THREADS; i++){
            pthread_attr_init(&attr[i]);
            switch (i){
            case 0:
                pthread_create(&threadID[i], &attr[i], returnAvgLocal, avg_value_local);
                break;
            case 1:
                pthread_create(&threadID[i], &attr[i], returnMinLocal, min_value_local);
                break;
            case 2:
                pthread_create(&threadID[i], &attr[i], returnMaxLocal, max_value_local);
                break;
            default:
                break;
            } 
        }

    }

    for(i=0; i<N_THREADS; i++){
        pthread_join(threadID[i], NULL);
    }

    return 0;

}

void* returnAvgGlobal(void *arg){
    int sum = 0;
    int i; 
    for(i=0; i< LENGTH; i++){
        sum += numArray[i];
        
    }
    avg_value_global = (float )sum / (float)LENGTH;
    pthread_t id = pthread_self();
    printf("THREAD ID: %lu calculó el promedio %f \n", id, avg_value_global);
    pthread_exit(0);
};

void* returnMinGlobal(void *arg){
    min_value_global = 101;
    int i;
    for(i=0; i< LENGTH; i++){
        if(numArray[i] < min_value_global)
            min_value_global = numArray[i];
    }
    pthread_t id = pthread_self();
    printf("THREAD ID: %lu calculó el minimo %d \n", id, min_value_global);
    pthread_exit(0);
};

void* returnMaxGlobal(void *arg){
    max_value_global = 0;
    int i;
    for(i=0; i< LENGTH; i++){
        if(numArray[i] > max_value_global)
            max_value_global = numArray[i];
    }
    pthread_t id = pthread_self();
    printf("THREAD ID: %lu calculó el máximo %d \n", id, max_value_global);
    pthread_exit(0);
};

void* returnAvgLocal(void *arg){
    int sum = 0;
    int i; 
    for(i=0; i< LENGTH; i++){
        sum += numArray[i];
    }
    float* avg_p = (float *) arg;
    *avg_p = (float )sum / (float)LENGTH;
    pthread_t id = pthread_self();
    printf("THREAD ID: %lu calculó el promedio %f \n", id, *avg_p);
    pthread_exit(0);
};

void* returnMinLocal(void *arg){
    int* min_p = (int *) arg;
    *min_p = 101;
    int i;
    for(i=0; i< LENGTH; i++){
        if(numArray[i] < *min_p)
            *min_p = numArray[i];
    }
    pthread_t id = pthread_self();
    printf("THREAD ID: %lu calculó el minimo %d \n", id, *min_p);
    pthread_exit(0);
};

void* returnMaxLocal(void *arg){
    int* max_p = (int *) arg;
    *max_p = 0;
    int i;
    for(i=0; i< LENGTH; i++){
        if(numArray[i] > *max_p)
            *max_p = numArray[i];
    }
    pthread_t id = pthread_self();
    printf("THREAD ID: %lu calculó el máximo %d \n", id, *max_p);
    pthread_exit(0);
};
