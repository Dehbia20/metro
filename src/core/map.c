#include "structure.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * datastructure key pair value
 * this method allows to iterate over a linkedList<KeyPairValue> and try to find node with specified
 * key
 */
Sprite *find_by_key(Sprite *node, char *searched)
{
    if (node == NULL)
    {
        return NULL;
    }
    Sprite *actual = node;
    printf("\n");
    do
    {
        printf("actual %s - searched: %s", actual->key, searched);
        if (strcmp(actual->key, searched) == 0)
        {
            printf("#####found!!!");
            return actual;
        }
        actual = actual->next;
    } while (actual != NULL);
    return NULL;
}

void push(Sprite **node, char *key, SDL_Surface *surface)
{
    if (*node == NULL)
    {
        *node = (Sprite *)malloc(sizeof(Sprite));

        (*node)->key = key;
        (*node)->surface = surface;
        (*node)->next = NULL;
        printf("\nadded first %s", (*node)->key);
    }
    else
    {
        printf("\nkey - else : %s\n", key);
        Sprite **actual = node;
        while ((*actual)->next != NULL)
        {
            printf("####### actual key: %s, received key : %s", (*actual)->key, key);
            actual = &((*actual)->next);
        }
        (*actual)->next = (Sprite *)malloc(sizeof(Sprite));
        (*actual)->next->key = key;
        (*actual)->next->surface = surface;
        (*actual)->next->next = NULL;
    }
}

int size(Sprite *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int i = 0;
    while (node != NULL)
    {
        i++;
        node = node->next;
    }
    return i;
}

void free_sprites(Sprite *node)
{
    if (node == NULL)
    {
        return;
    }
    while (node != NULL)
    {
        Sprite *previous = node;
        node = node->next;
        SDL_FreeSurface(previous->surface);
        free(previous);
    }
}
