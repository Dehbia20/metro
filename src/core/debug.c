#include <stdio.h>
#include "structure.h"
#include "constants.h"
#include "context.h"
#include <stdarg.h>
#include <pthread.h>
void _dp(char *seq)
{
    pthread_mutex_t mutex = get_cfgMutex();
    pthread_mutex_lock(mutex);
    Config *cfg = get_cfg();
    if (cfg->trace == DEBUG)
    {
        printf(seq);
    }
    pthread_mutex_unlock(mutex);
}

void dp_train(void *v)
{
    Train *t = (Train *)v;
    char s[40];
    sprintf(s, "train - id : %s, time : %d", t->id, t->remainingTime);
    _dp(s);
}
