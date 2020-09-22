#include "header.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 256
#define WORDS 1000


int main(int argc, char* argv[])
{
	FILE* fr = fopen(argv[1], "rb");
	if (!fr)
		return;
	fseek(fr, 0L, SEEK_END);
	long length = ftell(fr);
	fseek(fr, 0, SEEK_SET);

	unsigned char* res;
	res = (unsigned char*)malloc(sizeof(unsigned char) * (length + 1));
	for (int i = 0; i < length; i++)
	{
		res[i] = fgetc(fr);
	}
	res[length] = '\0';
	fclose(fr);


	unsigned int test = hesh_cod(res, 0);

	HESH* table = (HESH*)malloc(sizeof(HESH) * WORDS);
	table[test].kod = test;
	table[test].word = addstruck(res, test, table[test]);
	printf("%d    %s", table[test].kod, table[test].word);
	return 0;
}