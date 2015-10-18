#ifndef TRIE_H
#define TRIE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DATA_NUM 21000000
#define NODE_NUM 42000000

int bincode[123][6];
struct mempool * pool;
struct pat_trie{
	struct pat_trie * child[2];//true
	char * val;//if it's end of word,that's true;//not nes
	int num;
};

struct mempool{
	char * stringpool;
	struct pat_trie * triepool;
	unsigned long long int offset_c;//length of the stringpool
	unsigned long long int offset_s;//num of node ;
	long long int count;//the num of string
};


struct pat_trie * createT(int num);
//inline int compare(int * bin1, int * bin2, int num);
//inline int stringtobin(char * key, int  *bin);
int compare(int * bin1, int * bin2, int num);
int stringtobin(char * key, int  *bin);
struct mempool * init(long long int filesize, long long int nodenum);
void insert_node(struct pat_trie * root, char * key, int * bin, int * temp1);
void init_root(struct pat_trie * root, char * key, int * bin);
int find(struct pat_trie * root, char * key, int *bin, int * temp1);
#endif
