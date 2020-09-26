#include "header.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>




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
		hesh += (((unsigned int)word[i] * simple_n(i)) % 500);
	}
    hesh %= 1000;
    return hesh;
}

char* addstruck(char* now_str, int index, HESH struckt)
{
    int len = strlen(now_str);
    struckt.word = (char*)malloc(sizeof(char) * len + 1);
    struckt.word = strcpy(struckt.word, now_str);
    return struckt.word;
}


