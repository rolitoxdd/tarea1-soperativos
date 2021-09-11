#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

int main(void)
{
    int K;
    printf("Introduzca el valor para K: ");
    scanf("%d", &K);

    printf(" ****  Opciones -> 0)Huerfano  1)Zombie   2)Morir  *** \n");
    pid_t padre_pid = getpid();
    printf("El id del proceso padre de padres es: %d\n", padre_pid);
    printf("\n");

    // Creacion de K procesos
    for (int i = 0; i < K; i++)
    {
        pid_t son_pid = fork();
        if (son_pid)
        {
            break;
        }
    }

    /* Para evitar problemas se evita trabajar directamente sobre
    el proceso padre de padres*/
    if (getpid() != padre_pid)
    {
        //Generacion de random para la eleccion de una opcion del proceso actual.
        srand(time(NULL) ^ (getpid() << 16));
        int r = random() % 3;

        printf("El proceso: %d Elige la opcion: %d\n", getpid(), r);

        pid_t parent_pid = getppid();

        if (r == 0) // OPCION 0 -> HUERFANO
        {
            if (parent_pid >= padre_pid)
            {
                kill(parent_pid, 9);
                sleep(5);
            }
            else
            {
                printf("OYE %d ya eres HUERFANO, no mates a tu padre (que es importante para el computador)\n", getpid());
            }
        }
        else if (r == 1) // OPCION 1 -> ZOMBIE
        {
            kill(parent_pid, SIGSTOP);
            exit(0);
        }
        else // OPCION 2 -> MUERE/ TERMINA
        {
            sleep(3);
            exit(0);
        }
    }

    //Este Else sirve para mantener el proceso principal ejecutando.
    else
    {
        while (1)
        {
            wait(NULL);
        }
    }
    return 0;
}