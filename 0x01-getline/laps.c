#include "laps.h"

/**
 * race_state - function that keeps track of the number of laps made by
 * several cars in a race.
 * @id: is an array of int representing the “identifier” of each car.
 * @size: is the size of this array
 */
void race_state(int *id, size_t size)
{
	static int id_in_race[100];
	static int laps[100];
	static int competitors;
	int i, j;
	int exist = 0;
	int to_sort_b[100];
	int amount_sort = 0;
	int sorted;

	for (i = 0; i < (int)size; i++)
	{
		for (j = 0; j < competitors; j++)
		{
			if (id[i] == id_in_race[j])
			{
				laps[j]++;
				exist = 1;
			}
		}
		if (!exist)
		{
			id_in_race[competitors] = id[i];
			competitors++;
			printf("Car %d joined the race\n", id[i]);
			to_sort_b[amount_sort] = id[i];
			amount_sort++;
		}
		exist = 0;
	}
	sorted = malloc(sizeof(int) * amount_sort);
	sort(to_sort_b, amount_sort, sorted);
	printf("Race state:\n");
	for ( j = 0; j < competitors; j++)
	{
		printf("Car %d [%d laps]\n", id_in_race[j], laps[j]);
	}
}


/**
 * sort - function that sorts an array of ints
 * @id: is an array of int representing the “identifier” of each number.
 * @size: is the size of this array
 * @sorted: the pointer with the buffer of the data to be sorted
 */
void sort(int *id, int size, int *to_sort)
{
	
}
