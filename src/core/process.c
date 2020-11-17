#define HAVE_STRUCT_TIMESPEC
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "structure.h"
#include "queue.h"
#include "handler.h"
#include "debug.h"

static char *rand_string(int size)
{
    char *str = malloc(size + 1);
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";
    if (size)
    {
        --size;
        for (size_t n = 0; n < size; n++)
        {

            int rand1 = rand() % (int)(sizeof charset - 1);
            int rand2 = rand() % (int)(sizeof charset - 1);

            str[n] = charset[(rand1 + rand2) / 2];
        }
        str[size] = '\0';
    }
    return str;
}

void send_signal(enum Signal_Type sig)
{
    pthread_t tid;
    switch (sig)
    {
    case UPDATE_DISPLAYED_TIME:
        break;

    case SHOW_TRAIN:
        printf("\n############sending signal");
        pthread_create(&tid, NULL, handle_ShowingTrain, NULL);
        pthread_join(tid, NULL);
        printf("apres le lancement #####");
        break;

    default:
        // unkown : do nothing
        break;
    }
}
void generate_new(Node **head)
{
    Train *t = (Train *)malloc(sizeof(Train));
    int i = size(head);
    t->id = rand_string(10);
    t->remainingTime = (i + 1) * 2 * MINUTE_AS_SEC;
    t->direction = RIGHT;
    char seq[80];
    sprintf(seq, "Generated new train with id: %s - remaining time: %d", t->id, t->remainingTime);
    _dp(seq);
    push_last(head, t);
}

void update_remainig_and_signal(Node **train_queue)
{
    for (int i = 0; i < size(train_queue); i++)
    {
        _dp("Updating remaining time trains...");
        void *data = get(*train_queue, i);
        if (data != NULL)
        {
            Train *t = (Train *)data;
            t->remainingTime = t->remainingTime - (int)MINUTE_AS_SEC;
            dp_train(t);
            if (t->remainingTime <= 0)
            {
                printf("time ellapsed !");
                send_signal(SHOW_TRAIN);
                //generate_new(train_queue);
            }
        }
    }
    send_signal(UPDATE_DISPLAYED_TIME);
}
void *start_background(Node **train_queue)
{
    _dp("Starting background task...");
    generate_new(train_queue);
    generate_new(train_queue);
    while (1)
    {

        sleep(MINUTE_AS_SEC);
        update_remainig_and_signal(train_queue);
    }
    return NULL;
}
