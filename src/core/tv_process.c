/**
 * *********************************************************************
 * ***** This file regroup code for handling travellers generation *****
 * *********************************************************************
 */
#define HAVE_STRUCT_TIMESPEC
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "context.h"
#include "constants.h"
#include "structure.h"
#include "pthread.h"
#include "queue.h"
#include "handler.h"
#include "debug.h"
#include "position_helper.h"

int rand_range(int, int);
void gen_andPush(Node **);
void consume(Node **head);
int calc_gatePosx(int, enum Train_Direction);
int remove_sign(signed int i);
void calc_nearestTrainGate(Passenger *);
int try_shift(Position *, enum P_Direction);
int search_pIdxByPos(Position *p);

void start_generation(Node **passengers)
{
    pthread_mutex_t mutex = get_cfgMutex();
    enum Mode mode = TRAIN_TRAVELLER;
    do
    {
        if (size(passengers) < MAX_WAITING_PASSENGER && mode == TRAIN_TRAVELLER)
        {

            gen_andPush(passengers);
        }
        consume(passengers);
        pthread_mutex_lock(mutex);
        Config *cfg = get_cfg();
        mode = cfg->mode;
        int pause = cfg->generationPauseTime * 1000;
        pthread_mutex_unlock(mutex);
        usleep(pause);
    } while (mode == TRAIN_TRAVELLER || size(passengers) > 0);
}

void consume(Node **head)
{
    int sz = size(head);
    for (int i = 0; i < sz; i++)
    {
        void *v = get(*head, i);

        if (v != NULL)
        {
            _dp("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            _dp("retrieved passenger handle draw");
            Passenger *p = (Passenger *)v;
            handle_drawPsnger(p);
            move_fwd(p);
            _dp("\n==============================================================");
            pretty_print();
        }
    }
    handle_refresh();

    _dp("\n###############################################################");
}
void gen_andPush(Node **head)
{
    enum Train_Direction dir = rand_range(0, 1);
    int gate = rand_range(1, 7);
    int pos_y, pos_x;

    pos_y = dir == LEFT ? 16 : 3;
    pos_x = (((7 * gate) + gate) * CELL_W);

    Position *src = (Position *)malloc(sizeof(Position));
    src->i = pos_x;
    src->j = pos_y * CELL_H;
    int idRes = rand_range(9, 12);
    Passenger *passenger = (Passenger *)malloc(sizeof(Passenger));
    passenger->pos = src;
    passenger->prevPos = NULL;
    passenger->idRes = idRes;
    passenger->destStatus = NOT_REACHED;
    passenger->dir = dir;

    calc_nearestTrainGate(passenger);
    push_last(head, passenger);
    char txt[60];
    sprintf(txt, "gen psngr : pos [%d, %d] - q size %d - des [%d, %d]", src->i, src->j, size(head), passenger->destPos->i, passenger->destPos->j);
    _dp(txt);
    mark_asFilled(passenger->pos);
}

void move_fwd(Passenger *p)
{
    // final row = train sliding row - 1
    int finalRow = p->dir == LEFT ? TRAIN_LEFT_ROW_IDX + 1 : TRAIN_RIGHT_ROW_IDX - 1;
    Position *pos = (Position *)malloc(sizeof(Position));
    int moved = 0, res = 0;
    pos->i = p->pos->i;
    pos->j = p->pos->j;
    signed int dist = p->destPos->i - p->pos->i;

    if (p->destStatus != REACHED)
    {

        if ((p->pos->j < CELL_H * finalRow && p->dir == RIGHT) || (p->pos->j) > CELL_H * finalRow && p->dir == LEFT)
        {
            int flag = try_shift(pos, p->dir == RIGHT ? P_UP : P_DOWN);
            if (!flag)
            {
                moved = try_shift(pos, dist > 0 ? P_RIGHT : P_LEFT);
            }
            else
            {
                moved = 1;
            }
        }
        else
        {
            res = try_shift(pos, dist > 0 ? P_RIGHT : P_LEFT);
            moved = moved || res;
        }

        // passenger moved
        if (moved)
        {
            p->prevPos = p->pos;
            p->pos = pos;
            if (is_free(p->pos))
            {
                mark_asFilled(pos);
                mark_asFree(p->prevPos);
            }
        }
        else // passenger still on same place free allocated pos
        {
            free(pos);
        }

        if (p->pos->i == p->destPos->i)
        {
            _dp("yataaaa ! positon reached");
            p->destStatus = REACHED;
        }
    }
    else
    {
        int idx = search_pIdxByPos(p);

        if (idx >= 0)
        {
            int res = handle_takeTrain(p);
            if (res)
            {
                mark_asFree(p->pos);
                q_remove(get_psngr(), idx);
            }
        }
    }
}
int try_shift(Position *pos, enum P_Direction d)
{
    // proceed by copy to avoid updating original pos

    Position copy = {pos->i, pos->j};
    switch (d)
    {
    case P_UP:
        copy.j += CELL_H;
        _dp("\n try shift up");
        break;
    case P_LEFT:
        _dp("\n try shift left");
        copy.i -= CELL_W;
        break;
    case P_RIGHT:
        _dp("\n try shift right");
        copy.i += CELL_W;
        break;
    case P_DOWN:
        _dp("\n try shift right");
        copy.j -= CELL_H;
        break;
    }

    if (is_free(&copy))
    {
        pos->i = copy.i;
        pos->j = copy.j;
        return 1;
    }
    return 0;
}

void calc_nearestTrainGate(Passenger *p)
{
    int trainGates = N_TRAIN_CELL / TRAIN_GATE_SPACING;
    int bestGatePosX = 0;
    int bestDist = 9999;

    for (int i = 0; i < trainGates; i++)
    {
        int gatePos = calc_gatePosx(i, p->dir);
        int dist = remove_sign(p->pos->i - gatePos);
        if (dist < bestDist)
        {
            bestDist = dist;
            bestGatePosX = gatePos;
        }
    }
    Position *dest = (Position *)malloc(sizeof(Position));
    dest->i = bestGatePosX;
    dest->j = CELL_H * (p->dir == RIGHT ? TRAIN_RIGHT_ROW_IDX : TRAIN_LEFT_ROW_IDX);
    p->destPos = dest;
}

int calc_gatePosx(int i, enum Train_Direction dir)
{
    if (dir == RIGHT)
    {
        return ((TRAIN_RIGHT_STOP_CELL - N_TRAIN_CELL) + (i * TRAIN_GATE_SPACING)) * CELL_W;
    }
    else
    {
        return ((TRAIN_LEFT_STOP_CELL + N_TRAIN_CELL) - (i * TRAIN_GATE_SPACING)) * CELL_W;
    }
}
int remove_sign(signed int i)
{
    return i < 0 ? -i : i;
}

int rand_range(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int search_pIdxByPos(Position *p)
{
    Node **head = get_psngr();
    int sz = size(head);
    for (int i = 0; i < sz; i++)
    {
        void *d = get(*head, i);
        if (d != NULL)
        {
            Position *_p = (Position *)d;
            if (_p->i == p->i && _p->j == p->j)
            {
                return i;
            }
        }
    }
    return -1;
}