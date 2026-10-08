#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>

void *task(void *arg)
{
	
	int id = *(int *)arg;
	printf("T%d running\n",id);
	char name[16];
	snprintf(name, sizeof(name), "T%d", id);
	pthread_setname_np(pthread_self(), name);

    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);

    if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0) {
        perror("pthread_setaffinity_np");
    }

    while (1) {
        printf("Thread running\n");
        sleep(1);
    }

    return NULL;
}

int main(void)
{
    pthread_t threads[3];
    int priorities[3] = {80, 60, 40};
	int ids[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        struct sched_param param;

        if (pthread_create(&threads[i], NULL, task, &ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }

        param.sched_priority = priorities[i];

        if (pthread_setschedparam(threads[i], SCHED_FIFO, &param) != 0) {
            perror("pthread_setschedparam");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
