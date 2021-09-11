#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#define N 10

//MATRIZ PIPE
int channel[N][2];

// THREAD ESCRITURA:
void *escribir(void *tid)
{
    char msg[15];
    long index = (long)tid;
    close(channel[index][0]);
    srand(time(NULL) ^ (index << 16));
    int num = rand() % 100;
    sprintf(msg, "[%li]: %d\n", index, num);
    write(channel[index][1], msg, sizeof(msg));
    return NULL;
}

// THREAD LECTURA:
void *leer(void *tid)
{
    long index = (long)tid;
    close(channel[index][1]);
    char res[15];
    read(channel[index][0], &res, sizeof(res));
    printf("%s", res);
    return NULL;
}

int main(int argc, char *argv[])
{
    // Inicializacion arreglo de threads.
    pthread_t t[N + 1];

    // Creacion de Pipe
    for (int i = 0; i < N; i++)
    {
        pipe(channel[i]);
    }

    if (!fork()) // HIJO
    {
        // Creacion Threads de escritura.
        for (long i = 0; i < N; i++)
        {
            pthread_create(&t[i], NULL, escribir, (void *)i);
        }

        // Espera para la finalizacion de cada Thread de escritura.
        for (long i = 0; i < N; i++)
        {
            pthread_join(t[i], NULL);
        }

        // Muere el proceso.
        exit(0);
    }
    else // PADRE
    {
        // Creacion Threads de lectura.
        for (long i = 0; i < N; i++)
        {
            pthread_create(&t[i], NULL, leer, (void *)i);
        }

        // Espera para la finalizacion de cada Thread de lectura.
        for (long i = 0; i < N; i++)
        {
            pthread_join(t[i], NULL);
        }

        // Espera a que proceso hijo termine.
        wait(NULL);
    }

    return 0;
}