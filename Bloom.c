#include"Bloom.h"
#include"Hash.h"
const int mask[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };
int initFilter(bf s)
{
	s->table = calloc((MAX_INDEX >>3) + 1,sizeof(char));
	s->hash[0] = RSHash;
	s->hash[1] = JSHash;
	s->hash[2] = PJWHash;
	s->hash[3] = ELFHash;
	s->hash[4] = BKDRHash;
	s->hash[5] = SDBMHash;
	s->hash[6] = DJBHash;
	s->hash[7] = DEKHash;
	s->hash[8] = BPHash;
	s->hash[9] = FNVHash;
	s->hash[10] = APHash;
	return 0;
}

int insertData_b(bf s,char * key)
{
	unsigned int t,i;
	int len = strlen(key);
	for (i = 0; i < HASH_NUM; i++)
	{
		t = s->hash[i](key, len) &(MAX_INDEX-1) ;
		s->table[t >>3 ] |=  mask[t &7];
	}
	return 0;
}
//22 126 901
int find_b(bf s, char * key)
{
	unsigned int t, i,found = 1;
	int len = strlen(key);
	for (i = 0; found && i < HASH_NUM; i++)
	{
		t = s->hash[i](key, len) &(MAX_INDEX - 1);
		if (0 == (s->table[t>>3] & mask[t&7]))//ÕâÒ»¾ä¿ÉÒÔ¸Ä
			found = 0;
	}
	return found;
}
