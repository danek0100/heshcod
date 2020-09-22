#include "header.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 256



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


	int k = 0;
	int firstnum = 0;
	int m = k;
	while ((res[m] != ' ') && (res[m] >= '0') && (res[m] <= '9') && (m < length))
		m++;
	m = m - k;
	int s = 1;
	for (int i = 0; i < m - 1; i++)
		s *= 10;
	for (int i = k; i < k + m; i++)
	{
		firstnum += (res[i] - '0') * s;
		s /= 10;
	}


	k = k + m + 1;
	int secondnumber = 0;
	m = k;
	while ((res[m] != ' ') && (res[m] >= '0') && (res[m] <= '9') && (m < length))
		m++;
	m = m - k;
	s = 1;
	for (int i = 0; i < m - 1; i++)
		s *= 10;
	for (int i = k; i < k + m; i++)
	{
		secondnumber += (res[i] - '0') * s;
		s /= 10;
	}

	k = k + m + 1;


	while ((res[k] != ' ') && (res[k] != '*') && (res[k] != 'k') && (res[k] != 'e'))
		k++;

	int MX = firstnum;
	int MH = secondnumber;


	int** array;
	array = (int**)malloc(MX * sizeof(int*));

	unsigned int** array2;
	array2 = (unsigned int**)malloc(MX * sizeof(unsigned int*));


	int walls = 0;

	for (int i = 0; i < MX; i++)
	{
		array[i] = (int*)malloc(MH * sizeof(int));
		array2[i] = (unsigned int**)malloc(MH * sizeof(unsigned int*));

		for (int j = 0; j < MH; j++)
		{
			if ((res[k] != ' ') && (res[k] != '*') && (res[k] != 'k') && (res[k] != 'e'))
			{

				printf("Edit lab! %d %d", res[k], k);
				return 0;
			}


			if (res[k] == ' ')
			{
				array[i][j] = 0;
				array2[i][j] = 0;

			}
			if (res[k] == '*')
			{
				array[i][j] = -1;
				array2[i][j] = 0;
				walls++;
			}
			if (res[k] == 'k')
			{
				array[i][j] = 1;
				array2[i][j] = 1;
			}
			if (res[k] == 'e')
			{
				array[i][j] = -2;
				array2[i][j] = 0;
			}
			k++;
			if (k == length)
				break;
		}
		while ((res[k] != ' ') && (res[k] != '*') && (res[k] != 'k') && (res[k] != 'e'))
		{
			k++;
			if (k == length)
				break;
		}
	}




	for (int i = 0; i < MX; i++)
	{
		for (int j = 0; j < MH; j++)
		{
			if (array[i][j] != -1 && array[i][j] != -2)
			{
				if (checkgr(MX, MH, i, j - 1))
				{
					if (array[i][j - 1] != -1)
					{
						array2[i][j] += array2[i][j - 1];
						array2[i][j] %= 100000;
					}
				}
				if (checkgr(MX, MH, i - 1, j))
				{
					if (array[i - 1][j] != -1)
					{
						array2[i][j] += array2[i - 1][j];
						array2[i][j] %= 100000;
					}
				}
			}
			if (array[i][j] == -2)
			{
				if (checkgr(MX, MH, i, j - 1))
				{
					if (array[i][j - 1] != -1)
					{
						array2[i][j] += array2[i][j - 1];
						array2[i][j] %= 100000;
					}
				}
				if (checkgr(MX, MH, i - 1, j))
				{
					if (array[i - 1][j] != -1)
					{
						array2[i][j] += array2[i - 1][j];
						array2[i][j] %= 100000;
					}
				}
				if (array2[i][j] != -2)
					printf("All paths = %d\n\n", array2[i][j]);
				else
					printf("Bug din't find exit!!!\n\n");
			}
		}
	}

	for (int i = 0; i < MX; i++)
	{
		for (int j = 0; j < MH; j++)
		{
			printf("%d\t", array2[i][j]);
		}
		printf("\n");
	}



	for (int i = 0; i < MX; i++)
		free(array[i]);
	free(array);


	return 0;
}