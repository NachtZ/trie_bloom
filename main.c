#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"Bloom.h"
#include"Hash.h"
#include"trie.h"

int trie_check(FILE* email, FILE* check, FILE *re)
{
	int pos = -1, len, i;
	long long int count = 0;
	long longBytes;
	char lines[321];
	char * string;
	int bin[321 * 6];
	int temp[321 * 6];
	fseek(email, 0, SEEK_SET);
	fseek(email, 0, SEEK_END);
	longBytes = ftell(email);
	fseek(email, 0, SEEK_SET);
	pool = init(longBytes, NODE_NUM);
	struct pat_trie * t = createT(-1);
	//	string = &pool -> stringpool[pool->offset_c];
	//	pool->offset_c += len + 1;
	//	strcpy(string, lines);
	//	init_root(t, string, bin);
	while (!feof(email))
	{
		count++;
		fgets(lines, 320, email);
		len = strlen(lines);
		if (lines[len - 1] == 10 || lines[len - 1] == 13)
		{
			lines[len - 1] = 0;
			len--;
		}
		string = &pool->stringpool[pool->offset_c];
		pool->offset_c += len + 1;
		strcpy(string, lines);
	}
	string = pool->stringpool;
	init_root(t, string, bin);
	string += strlen(string) + 1;
	while (--count)
	{
		insert_node(t, string, bin, temp);
		string += strlen(string) + 1;
	}
	while (!feof(check))
	{
		fgets(lines, 321, check);
		pos++;

		len = strlen(lines);
		for (i = len - 1; i >= 0; i--)
		if (lines[i] == 10 || lines[i] == 13)
			lines[i] = 0;
		if (!find(t, lines, bin, temp))
			fprintf(re, "%d\n", pos);
	}
	return 0;
}
int bloom_check(FILE* email, FILE* check, FILE *re)
{
	char lines[321];
	bf s = malloc(sizeof(BF));
	long long int count = 0;
	int len, pos = -1,i;
	initFilter(s);

	while (!feof(email))
	{
		fgets(lines, 321, email);
		len = strlen(lines);
		if (lines[len - 1] == 10 || lines[len - 1] == 13)
			lines[len -1] = 0;
		insertData_b(s, lines);
	}
	while (!feof(check))
	{
		fgets(lines, 321, check);
		pos++;
		len = strlen(lines);
		for (i = 0; i<len; i++)
		if (lines[i] == 13)
			lines[i] = 0;
		if (lines[len - 1] == 10 || lines[len - 1] == 13)
			lines[len - 1] = 0;
		if (!find_b(s,lines))
			fprintf(re, "%d\n", pos);
	}
	return 0;
}

int main(int argc, char* argv[])
{

	clock_t start;
	FILE * email, *check, *re;
	start = clock();
	
	if (argc < 4)
		exit(0);
	FILE * email = fopen(argv[1], "r");
	FILE * check = fopen(argv[2], "r");
	FILE * re = fopen(argv[3], "w");
	/*
	email = fopen("g:\\emaillist.dat", "r");
	check = fopen("g:\\checklist.dat", "r");
	re = fopen("g:\\result.dat", "w");*/
	trie_check(email, check, re);
	printf("time of trie: %f secs\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	start = clock();
	fprintf(re, "-----------------end of trie and start of bloom-----------------\n");
	fseek(email, 0, SEEK_SET);
	fseek(check, 0, SEEK_SET);
	bloom_check(email, check, re);
	printf("time of bloom: %f secs\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	fclose(email);
	fclose(check);
	fclose(re);
	//getch();
	return 0;

	/*
	clock_t start;
	start = clock();
	FILE * email = fopen("g:\\emaillist.dat", "r");
	char * string;
	char lines[321];
	long long int count = 0;
	long long int len = 0;
	while (!feof(email))
	{
	fgets(lines, 320, email);
	//len = strlen(lines);
	//malloc(sizeof(char)* (len+1));
	count++;
	if (count % 100000 == 1)
	printf("%lld\n", count);
	len += strlen(lines)+1;
	//malloc(sizeof(struct pat_trie) * 2);

	}

	malloc(sizeof(struct pat_trie) * 2*count);
	string = malloc(sizeof(char)* len);
	printf("length in total:%lld\n", len);
	printf("time: %f secs\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	getch();
	return 0;
	*/
	/*result941705635*/
	/**/
	/*
	FILE * fp = fopen("g:\\emaillist.dat", "r");
	fseek(fp, 0, SEEK_SET);
	fseek(fp, 0, SEEK_END);
	long longBytes = ftell(fp);
	printf("%lld\n", longBytes);
	fclose(fp);
	return 0;*/
}
