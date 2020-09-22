#include "header.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>


int checkgr(int l, int h, int i, int j)
{
	if ((i >= 0) && (i < l) && (j >= 0) && (j < h))
		return 1;
	return 0;
}
