#include "header.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>

#define WORDS 1001


unsigned int simple_n(int n)
{

    const int SIZE = 100000;
    const int N = 9500;

    if (n < 0 || n > N)
        return 0;

    int* a = (int*)malloc(SIZE * sizeof(int));
    for (int i = 2; i < SIZE; ++i)
        a[i] = 1;

    int k = 1;
    int p = 2;
    while (k < n) 
    {

        for (int i = 2 * p; i < SIZE; i += p)
            a[i] = 0;

        for (int i = p + 1; i < SIZE; ++i)
            if (a[i] == 1) 
            {
                p = i;
                break;
            }
        ++k;
    }
    free(a);
    return p;
}

unsigned int hesh_cod(char* word, int coliz)
{
	int len = strlen(word);
	int hesh = 0;
	for (int i = 0; i < len; i++)
	{
		hesh += (((unsigned int)word[i] * simple_n(i)) % (WORDS / 2));
	}
    hesh %= WORDS;
    return hesh;
}

unsigned int hesh_codk(char* word, unsigned int coli)
{
    int len = strlen(word);
    int hesh = 0;
    if (coli == 0)
    {
        for (int i = 0; i < len; i++)
        {
            hesh += (((((unsigned int)word[i] * simple_n(i)) % (WORDS / 2))));
        }
        hesh %= WORDS;
        return hesh;
    }
    if (coli != 0)
    {
        for (int i = 0; i < len; i++)
        {
            hesh += (((((unsigned int)word[i] * simple_n(i) + coli) * coli) % (WORDS / 2)));
        }
        hesh %= WORDS;
        return hesh;
    }
}

char* addstruck(char* now_str, int index, HESH struckt)
{
    int len = strlen(now_str);
    struckt.word = (char*)malloc(sizeof(char) * len + 1);
    struckt.word = strcpy(struckt.word, now_str);
    return struckt.word;
}

int IsIn(HESH* mass, char* word)
{
    unsigned int kod = hesh_cod(word, 0);
    if (mass[kod].kod == kod && !strcmp(mass[kod].word, word))
        return 1;
    else 
        return 0;
}

unsigned int Max_len(unsigned int prv_max, char* str)
{
    unsigned int len = strlen(str);
    if (prv_max > len)
        return prv_max;
    else
        return len;
}


int IsInCh(HESHCHAIR* mass, char* word)
{
    unsigned int kod = hesh_cod(word, 0);

    if (mass[kod].kod == kod && !strcmp(mass[kod].word, word))
    {
        printf("\nYes! Word finded! Koliz = %d\n", mass[kod].kol);
        return 1;
    }
    HESHCHAIR* chek = &mass[kod];
    while (chek->pnext != 0)
    {
        chek = chek->pnext;
        if (chek->kod == kod && !strcmp(chek->word, word))
        {
            printf("\nYes! Word finded! Koliz = %d\n", chek->kol);
            return 1;
        }
    }
    printf("\nWord NOT finded!\n");
    return 0;
}

int IsInOp(HESHOPEN* mass, char* word, unsigned int mko)
{
    unsigned int kod = hesh_codk(word, 0);
    if (mass[kod].kod == kod && !strcmp(mass[kod].word, word))
    {
        printf("\nYes! Word finded! Koliz = %d\n", 0);
        return 1;
    }
    else
    {
        unsigned int ko = 1;
        while (!(mass[kod].kod == kod && !strcmp(mass[kod].word, word)) && ko <= mko)
        {
            kod = hesh_codk(word, ko);
            if (mass[kod].kod == kod && !strcmp(mass[kod].word, word))
            {
                printf("\nYes! Word finded! Koliz = %d\n", ko);
                return 1;
            }
            ko++;
        }
    }
    printf("\nWord NOT finded! Kol chek = %d\n", WORDS);
    return 0;
}