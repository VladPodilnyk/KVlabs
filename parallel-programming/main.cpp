#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 10

pthread_t thread_consumer1;
pthread_t thread_consumer2;
pthread_t thread_producer1;
pthread_t thread_producer2;
pthread_t thread_producer3;

sem_t sem1, sem2, SCR1;
pthread_mutex_t MCR1 = PTHREAD_MUTEX_INITIALIZER;

int common_resource[MAX_BUFFER_SIZE];
int value = 0;
int counter = 0;
FILE *cfile = fopen("BlackBox.log", "w");

void* producer(void* arg) {
    int id = *(int*)arg;
    int sem_value;
    while(1) {
        int flag = 0;
        if (id == 1) {
            sem_post(&sem2);
            flag = sem_trywait(&sem1);
        }

        if (id == 5) {
            sem_post(&sem1);
            sem_wait(&sem2);
        }

        sem_getvalue(&SCR1, &sem_value);
        if (counter == 0 && sem_value == MAX_BUFFER_SIZE) ++counter;
        else if (counter == 1 && sem_value == 0) ++counter;
        else if (counter == 2 && sem_value == MAX_BUFFER_SIZE) ++counter;
        else if (counter == 3 && sem_value == 0) break;

        if(sem_value < MAX_BUFFER_SIZE && flag == 0) {
            if (pthread_mutex_trylock(&MCR1) == 0) {
                common_resource[sem_value] = value++;
                sem_getvalue(&SCR1, &sem_value);
                fprintf(cfile, "Producer thread %d: semaphore = %d; element %d CREATED\n", id, sem_value, value - 1);
                pthread_mutex_unlock(&MCR1);
                sem_post(&SCR1);
            }
            else
                usleep(1);
        }
        else if (flag == -1)
            //fprintf(cfile, "Producer thread %d does some useful work.\n", id);
            usleep(2);

    }
    //usleep(1);
    pthread_cancel(thread_consumer1);
    pthread_cancel(thread_consumer2);
    if (id == 1)
        pthread_cancel(thread_producer3);
    if (id == 5)
        pthread_cancel(thread_producer1);
    fprintf(cfile, "Producer thread %d stopped!\n", id);
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    int sem_value;
    int temp;
    while(1) {
        if (sem_trywait(&SCR1) == 0) {
            if (pthread_mutex_trylock(&MCR1) == 0) {
                sem_getvalue(&SCR1, &sem_value);
                temp = common_resource[sem_value];
                fprintf(cfile, "Consumer thread %d: semaphore = %d; element %d TAKEN\n", id, sem_value, temp);
                pthread_mutex_unlock(&MCR1);
            }
            else
                //fprintf(cfile, "Consumer thread %d does some useful work.\n", id);
                usleep(1);
        }
        else
            //fprintf(cfile, "Consumer thread %d does some useful work.\n", id);
            usleep(1);
        usleep(2);
    }
    //printf("Consumer thread &d stopped!\n", id);
    return NULL;
}


int main() {
    int sem_value;
    /* Оголошення змінних для нумерації потоків */
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    sem_init(&SCR1, 0, 0);

    for (int i = 0; i < 5; ++i, ++value) {
        common_resource[i] = value;
        sem_post(&SCR1);
    }


    sem_getvalue(&SCR1, &sem_value);
    //printf("%i\n", sem_value);

    int thread1_number = 1;
    int thread2_number = 2;
    int thread3_number = 3;
    int thread4_number = 4;
    int thread5_number = 5;

    pthread_create(&thread_producer1, NULL, &producer, (void*)&thread1_number);
    pthread_create(&thread_producer2, NULL, &producer, (void*)&thread2_number);
    pthread_create(&thread_consumer1, NULL, &consumer, (void*)&thread3_number);
    pthread_create(&thread_consumer2, NULL, &consumer, (void*)&thread4_number);
    pthread_create(&thread_producer3, NULL, &producer, (void*)&thread5_number);

    pthread_join(thread_producer1, NULL);
    pthread_join(thread_producer2, NULL);
    pthread_join(thread_producer3, NULL);
    pthread_join(thread_consumer1, NULL);
    pthread_join(thread_consumer2, NULL);
    fclose(cfile);
    return 0;
}