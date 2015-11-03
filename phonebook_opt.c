#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook_opt.h"
#define MAX_HASH_SIZE 15607 /* prime number */

entry hash_table[MAX_HASH_SIZE];
/* FILL YOUR OWN IMPLEMENTATION HERE! */
long sfold(char lastname[])
{
    int len_name = strlen(lastname);
    int length = len_name >> 2;
    long sum = 0;
    long mult;
    int size;
    int loop;
    for (int j = 0; j < length; j++) {
        size = (j << 2);
        loop = (size << 2) + 4 ;
        mult = 1;
        for (int k = size; k < loop; k++) {
            sum += lastname[k] * mult;
            mult = mult << 8;
        }
    }

    mult = 1;
    for (int k = 0; k < len_name; k++) {
        sum += lastname[k] * mult;
        mult = mult << 8 ;
    }

    return (abs(sum) % MAX_HASH_SIZE);
}

int hash(char lastname[])
{
    int len = strlen(lastname);
    int i, sum = 0;
    for (i = 0; i < len; i++)
        sum += lastname[i];
    return sum % MAX_HASH_SIZE;
}

entry *findName(char lastname[], entry *pHead)
{
    long key = sfold(lastname);
    if (strcasecmp(lastname, hash_table[key].lastName) == 0) {
        return &hash_table[key];
    } else {
        entry *temp = hash_table[key].pNext;
        if (temp == NULL) {
            return NULL;
        }

        while (strcasecmp(lastname, temp->lastName)) {
            if (temp->pNext != NULL) {
                temp = temp->pNext;
            }
        }
        return temp;
    }
    return NULL;
}

entry *append(char lastname[], entry *e)
{
    long key = sfold(lastname);
    if (strcasecmp(hash_table[key].lastName, "") == 0) {
        strncpy(hash_table[key].lastName , lastname, strlen(lastname));
        hash_table[key].pNext = NULL;
    } else { /* using single link list if collision happens */
        e = hash_table[key].pNext;
        if (e == NULL) {
            e = (entry *) malloc(sizeof(entry));
            strncpy(e->lastName, lastname, strlen(lastname));
            e->pNext = NULL;
            hash_table[key].pNext = e;
        }
        while ( e->pNext != NULL)
            e = e -> pNext;
        entry *temp = (entry *) malloc(sizeof(entry));
        strncpy(temp->lastName, lastname, strlen(lastname));
        temp->pNext = NULL;
        e->pNext = temp;
    }
    return NULL;
}

void free_all(entry* pHead)
{
    int i;
    for (i = 0; i < MAX_HASH_SIZE; i++) {
        if (!(strcasecmp(hash_table[i].lastName, "") == 0)) {
            /* the entry is in used */
            entry* temp = hash_table[i].pNext;
            if (temp != NULL) {
                while (temp->pNext != NULL) {
                    entry *temp_next = temp;
                    temp = temp->pNext;
                    free(temp_next);
                }
                free(temp);
            }
        }
    }
}
