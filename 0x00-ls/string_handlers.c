#include "hls.h"

/**
 * _strncmp - This is like strncmp
 * @s1: the pointer that points first string
 * @s2: the pointer that points second string
 * @n: the number of letters to compare
 * Return: 0 if there equal
 */
int _strncmp(char *s1, char *s2, int n)
{
	int iter;
	int validator = 0;

	for (iter = 0; iter < n; iter++)
	{
		/* printf("in strcmp %c and %c with iter: %d son %d\n",*/
		/* s1[iter], s2[iter], iter, s1[iter] != s2[iter]); */
		if (s1[iter] != s2[iter])
		{
			/* printf("entre\n"); */
			validator = iter + 1;
			break;
		}
	}
	return (validator);
}
