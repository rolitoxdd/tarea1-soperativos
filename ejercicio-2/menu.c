#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
    int x = -1;
    while (1)
    {
        printf("PID MENU%d:\n", getpid());
        printf("MENU:\n\t1 - canal 1\n\t2 - canal 2\n\t3 - canal 3\n\t0 - Apagar televisor\nElija una opcion: ");
        scanf("%d", &x);
        //printf("%d", x);

        if (x == 0)
        {
            exit(0);
        }

        else if (!fork())
        {
            if (x == 1)
            {
                execlp("./canal1", "", NULL);
            }
            else if (x == 2)
            {
                execlp("./canal2", "", NULL);
            }
            else if (x == 3)
            {
                execlp("./canal3", "", NULL);
            }

            else
            {
                printf("Elija una opción correcta ...");
                exit(0);
            }
        }
        else
        {
            wait(NULL);
        }
    }
}