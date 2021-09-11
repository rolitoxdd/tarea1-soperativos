#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#define K 5

int main(void)
{
    pid_t padre_pid = getpid();
    for (int i = 0; i < K; i++)
    {
        pid_t son_pid = fork();
        if (son_pid)
        {
            break;
        }
    }
    if (getpid() != padre_pid)
    {

        srand(time(NULL) ^ (getpid() << 16));
        int r = random() % 3;
        printf("%d\t%d\n", r, getpid());
        //0
        if (r == 0) // huerfano
        {
            pid_t parent_pid = getppid(); // obtiene la pid del proceso padre
            kill(parent_pid, 9);          // mata al padre
            printf("");
            sleep(5);
        }
        else if (r == 1) // zombie
        {
            pid_t parent_pid = getppid();
            kill(parent_pid, SIGSTOP);
            exit(0);
        }
        else // <--muere
        {
            sleep(5);
            exit(0);
        }
    }
    else
    {
        while (1)
        {
            wait(NULL);
        }
    }

    return 0;
}