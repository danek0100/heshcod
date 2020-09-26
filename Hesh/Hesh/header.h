#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>

typedef struct hesh
{
	unsigned int kod;
	char* word;
}HESH;


typedef struct heshchair
{
	unsigned int kod;
	char* word;
	struct HESHCHAIR* pnext;

}HESHCHAIR;

#endif