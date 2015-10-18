#include "trie.h"

inline int compare(int * bin1, int * bin2, int num)
{
	int i = 0;
	for (; i < num && bin1[i] == bin2[i]; i++);
	if (i == num && bin1[i]!=bin2[i])return -1;
	else return i;
}
inline int stringtobin(char * key, int  *bin)
{
	//to do 将程序改成debug的东西。
	//to do v2 delete \n and add end mask
	int length = 0, i,len;
	if (!key) return length;
	len = strlen(key);
	for (i = len -1;i>=0;i --)
	{
		memcpy(&bin[length], bincode[key[i]], 6 * sizeof(int));
		length += 6;
	}
	memcpy(&bin[length], bincode[40], 6 * sizeof(int));
	length += 6;
	return length;

}

 struct pat_trie * createT(int num)
{
	struct pat_trie * root = &pool->triepool[pool->offset_s ++];
	root->child[0] = NULL;
	root->child[1] = NULL;
	root->val = NULL;
	root->num = num;
	return root;
}

struct mempool * init(long long int filesize,long long int nodenum)
 {
	int i, k, j;
	struct mempool * pool = malloc(sizeof(struct mempool));
	
	pool->stringpool = malloc((filesize + DATA_NUM+DATA_NUM)*sizeof(char));
	pool->triepool = malloc(NODE_NUM*sizeof(struct pat_trie));
	if (pool->stringpool == NULL || pool->triepool==NULL)
	{
		printf("Out of Mem!\n");
		exit(-1);
	}
	pool->offset_c = 0;
	pool->offset_s = 0;
	/*init bin code here*/
	for (i = 0; i < 123; i++)
	{
		if (i <= 'z' && i >= 'a')
			k = i - 'a';
		else if (i <= 'Z' &&  i >= 'A')
			k = i - 'A';
		else if (i <= '9' && i >= '0')
			k = i - '0' + 26;
		else if (i == '.')
			k = 36;
		else if (i == '@')
			k = 37;
		else if (i == '-')
			k = 38;
		else if (i == '_')
			k = 39;
		else if (i == 10 || i == 13)
			k = 40;
		else
			continue;
		for (j = 0; j < 6; j++)
		{
			bincode[i][j] = (k >> j) & 1 ? 1 : 0;
		}
	}
	printf("Init done!\n");
	return pool;
 }
 

void init_root(struct pat_trie * root,  char * key, int  bin[])
{
	int len1 = stringtobin(key, bin);
	root->num = 0;
	root->child[bin[0]] = createT(-1);
	root->child[bin[0]]->val = key;
}
void insert_node(struct pat_trie * root, char * key, int  *bin, int *temp1)
{
	int len1 = stringtobin(key, bin);
	int i = 0;
	struct pat_trie *node = root ,*pre =root;

	while (1)
	{
	i = node ->num;
	if (i > len1 || i == -1 || node->child[bin[i]] == 0)
	{
		if (i<=len1 && i !=-1)
		{
			node->child[bin[i]] = createT(-1);
			node->child[bin[i]]->val = key;
			return;
		}
		int len2 = stringtobin(node->val,temp1);
		int t = compare(temp1, bin, len1 > len2 ? len2 : len1);
		if (t == -1) return;//the same,do not need to insert again.
		if (pre->num > t)
		{
			//rewind
			//make sure pre -> num < t < node -> num
			node = root;
			while (t>=node->num)
			{
				pre = node;
				node = node->child[bin[node->num]];
			}
		}
			pre->child[bin[pre->num]] = createT(t);
			pre->child[bin[pre->num]]->val = key;
			pre->child[bin[pre->num]]->child[bin[t]] = createT(-1);
			pre->child[bin[pre->num]]->child[bin[t]]->val = key;
			pre->child[bin[pre->num]]->child[!bin[t]] = node;
			return;
	}
	else
	{
		pre = node;
		node = node->child[bin[i]];
	}
	}
	
}


int find(struct pat_trie * root, char * key,int *bin,int * temp1)
{
	int len1 = stringtobin(key, bin);
	struct pat_trie *node = root, *pre = root;
	while (node)
	{
		if (node->num == -1)
		{
			if (node->val == NULL)return 0;
			return 0 == strcmp(node ->val,key);
		}
		pre = node;
		node = node->child[bin[node->num]];
	}
	return 0;
}
