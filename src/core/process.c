#define HAVE_STRUCT_TIMESPEC
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "structure.h"
#include "queue.h"
#include "signal_handler.h"

void send_signal(enum Signal_Type sig)
{
    switch (sig)
    {
    case UPDATE_DISPLAYED_TIME:
        break;

    case SHOW_TRAIN:
        signal(SIGINT, handle_ShowingTrain);
        break;

    default:
        // unkown : do nothing
        break;
    }
}
void generate_new(Node **head)
{
    Train t = {"tchouu !", 20, LEFT};
    printf("generation d'un train %s", t.id);
    push_last(head, &t);
}

void update_remainig_and_signal(Node **train_queue)
{
    for (int i = 0; i < size(train_queue); i++)
    {
        Node **found = get(train_queue, i);
        if (*found != NULL && (*found)->data != NULL)
        {
            Train *t = (Train *)(*found)->data;
            t->remainingTime = t->remainingTime - MINUTE_AS_SEC;
            if (t->remainingTime <= 0)
            {
                send_signal(SHOW_TRAIN);
                generate_new(train_queue);
            }
        }
    }
    send_signal(UPDATE_DISPLAYED_TIME);
}
void *start_background(Node **train_queue)
{
    printf("\n start");
    generate_new(train_queue);
    generate_new(train_queue);
    printf("\n start background %d", size(train_queue));
    while (1)
    {
        Train *t = (Train *)first(train_queue);
        if (t != NULL)
        {
            sleep(MINUTE_AS_SEC);
            update_remainig_and_signal(train_queue);
        }
    }
    return NULL;
}
