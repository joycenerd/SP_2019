#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define size 10000
long table[size][size];
long col[size];
long row[size];
unsigned int g_seed;

// Used to seed the generator.           
inline void fast_srand(int seed) {
    g_seed = seed;
}

// Compute a pseudorandom integer.
inline int fast_rand(void) {
	//g_seed=(g_seed>>16)&0x7FFF;
    g_seed = (214013*g_seed+2531011);
    //return (g_seed>>16)&0x7FFF;
	return (g_seed>>2);
}

void initTable()
{
	int i, j;
	fast_srand(time(NULL));
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			table[i][j] = fast_rand();
}

void sumCol()
{
	int i, j;
	for (j = 0; j < size; j++)
		//for (i = 0; i < size; i++)
			col[j] = table[size-1][j];
}

void sumRow()
{
	int i, j;
	for (i = 0; i < size; i++)
		//for (j = 0; j < size; j++)
		row[i] = table[i][size-1];
}

void printResult()
{
	int i;
	printf("     RAW\tCol\n");
	for (i = 0; i < size; i++)
		printf("%8ld\t%8ld\n", row[i], col[i]);
}

int main()
{
	printf("hello\n");
	initTable();
	sumRow();
	sumCol();
	printResult();
	return 0;
}
