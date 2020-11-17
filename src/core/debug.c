#include <stdio.h>
#include "structure.h"
#include "constants.h"
#include <stdarg.h>

void _dp(char *seq)
{
    if (DEBUG)
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf(seq);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }
}
void dp_train(void *v)
{
    Train *t = (Train *)v;
    char s[40];
    sprintf(s, "train - id : %s, time : %d", t->id, t->remainingTime);
    _dp(s);
}
