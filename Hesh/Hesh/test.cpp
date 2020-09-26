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

	char* cstr = strtok(res, " ,.-\n\r\t");
	//char* cstr2 = strtok(res, " ,.-\n\r\t");
	unsigned int max_word_len = 0;

	unsigned int coliz = 0;
	HESH* table = (HESH*)calloc(WORDS, sizeof(HESH));
	HESHCHAIR* tablec = (HESHCHAIR*)calloc(WORDS, sizeof(HESHCHAIR));

	while (cstr != 0)
	{
		max_word_len = Max_len(max_word_len, cstr);

		unsigned int test = hesh_cod(cstr, 0);

		if (table[test].kod == test)
			coliz++;


		table[test].kod = test;
		table[test].word = addstruck(cstr, test, table[test]);

		if (tablec[test].kod == 0)
		{
			tablec[test].kod = test;
			int len = strlen(cstr);
			tablec[test].word = (char*)malloc(sizeof(char) * len + 1);
			tablec[test].word = strcpy(tablec[test].word, cstr);
		}
		else if (tablec[test].kod == test)
		{
			HESHCHAIR* chek = &tablec[test];
			while (chek->pnext != 0)
			{
				chek = chek->pnext;
			}
			HESHCHAIR* chek2 = (HESHCHAIR*)calloc(1, sizeof(HESHCHAIR));
			chek2[0].kod = test;
			int len = strlen(cstr);
			chek2[0].word = (char*)malloc(sizeof(char) * len + 1);
			chek2[0].word = strcpy(chek2[0].word, cstr);
			chek->pnext = chek2;

		}

		//printf("%d    %s\n", table[test].kod, table[test].word);
		cstr = strtok(NULL, " ,.-\n\r\t");
	}
	printf("\nCloiz all = %d\n\n", coliz);

	coliz = 0;
	for (int i = 0; i < WORDS; i++)
	{
		if (tablec[i].kod != 0)
		{
			printf("\n%d    %s  ", table[i].kod, table[i].word);
			HESHCHAIR* chek = &tablec[i];
			while (chek->pnext != 0)
			{
				printf("  %s  ", chek->word);
				chek = chek->pnext;
			}
		}
	}

	printf("\n\nInput Word for Finding\n\n");
	char* find = (char*)malloc(sizeof(char) * max_word_len);
	scanf("%s", find);

	if (IsIn(table, find))
		printf("\nYes!\n");
	else 
		printf("\nNo!\n");

	free(table);
	free(tablec);

	coliz = 0;
	//HESH* table = (HESH*)calloc(WORDS, sizeof(HESH));


	return 0;
}