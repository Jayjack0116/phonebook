#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook_opt.h"
#define MAX_HASH_SIZE 3673 /* prime number*/

entry hash_table[MAX_HASH_SIZE];
/* FILL YOUR OWN IMPLEMENTATION HERE! */
long sfold(char lastname[])
{
    int length = strlen(lastname) / 4;
    long sum = 0;
    for (int j = 0; j < length; j++) {
        int size = (j * 4) + 4;
        char c[size];
        strncpy(c, lastname + j * 4, size);
        long mult = 1;
        int k;
        for (k = 0; k < strlen(c); k++) {
            sum += c[k] * mult;
            mult *= 256;
        }
    }
    char p[length * 4];
    strncpy(p, lastname, length * 4);
    long mult = 1;
    for (int k = 0; k < strlen(p); k++) {
        sum += p[k] * mult;
        mult *= 256;
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
            } else {
                break;
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
