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

	while (cstr != 0)
	{
		max_word_len = Max_len(max_word_len, cstr);
		unsigned int test = hesh_cod(cstr, 0);
		if (table[test].kod == test)
			coliz++;
		table[test].kod = test;
		table[test].word = addstruck(cstr, test, table[test]);
		//printf("%d    %s\n", table[test].kod, table[test].word);
		cstr = strtok(NULL, " ,.-\n\r\t");
	}
	printf("\nCloiz all = %d\n", coliz);


	printf("\n\nInput Word for Finding\n\n");
	char* find = (char*)malloc(sizeof(char) * max_word_len);
	scanf("%s", find);

	if (IsIn(table, find))
		printf("\nYes!\n");
	else 
		printf("\nNo!\n");

	free(table);
	
	coliz = 0;
	//HESH* table = (HESH*)calloc(WORDS, sizeof(HESH));


	return 0;
}