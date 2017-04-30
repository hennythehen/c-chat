#include "pipesem.h"

void signal(int* pd)
{
    int a = 1;
    write(pd[1], &a, sizeof(int));
}

void wait(int* pd)
{
    int a;
    read(pd[0], &a, sizeof(int));
}


