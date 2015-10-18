#ifndef BLOOM_H
#define BLOOM_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define HASH_NUM 11
#define MAX_INDEX 268435456

typedef struct BloomFilter
{
	char * table;
	unsigned int(*hash[11])(char *, unsigned int);
	
}BF;
typedef struct BloomFilter * bf;

int initFilter(bf  s);

int insertData_b(bf s,char * key);

int find_b(bf s, char * key);

#endif
