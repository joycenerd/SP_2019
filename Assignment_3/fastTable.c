#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define size 10000
long table[size][size];
long col[size] = {0};
long row[size] = {0};
unsigned int g_seed;

// Used to seed the generator.
extern inline void fast_srand(int seed)
{
	g_seed = seed;
}

// Compute a pseudorandom integer.
extern inline int fast_rand(void)
{
	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 2);
}

// generate table[][] using randomize function
void initTable()
{
	int i, j;
	fast_srand(time(NULL));
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			table[i][j] = fast_rand();
}

// compute row sum and column sum
void rowColSum()
{
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
		{
			row[i] += table[i][j];
			col[j] += table[i][j];
		}
}

// print out row sum and column sum
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
	rowColSum();
	printResult();
	return 0;
}
