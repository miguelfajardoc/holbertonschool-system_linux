#include "laps.h"

/**
 * race_state - function that keeps track of the number of laps made by
 * several cars in a race.
 * @id: is an array of int representing the “identifier” of each car.
 * @size: is the size of this array
 */
void race_state(int *id, size_t size)
{
	static int *id_in_race;
	static int laps[2592], competitors;
	int i, j, exist = 0, amount_sort = 0;
	int to_sort_b[100];
	int *sorted_new, *sorted;

	memset(to_sort_b, 0, sizeof(to_sort_b));
	if (size == 0)
	{
		free(id_in_race), memset(laps, 0, sizeof(laps) * 1);
		competitors = 0;
		return;
	}
	for (i = 0; i < (int)size; i++)
	{
		for (j = 0; j < competitors; j++)
		{
			if (id[i] == id_in_race[j])
				laps[id_in_race[j]]++, exist = 1;
		}
		if (!exist)
		{
			printf("Car %d joined the race\n", id[i]);
			to_sort_b[amount_sort] = id[i];
			amount_sort++;
		}
		exist = 0;
	}
	sorted_new = malloc(sizeof(int) * amount_sort);
	mergeSort(to_sort_b, amount_sort, sorted_new);
	sorted = malloc(sizeof(int) * (competitors + amount_sort));
	sort2sorted_arrays(sorted_new, id_in_race, amount_sort,
			     competitors, sorted);
	competitors += amount_sort;
	printf("Race state:\n");
	if (id_in_race != NULL)
		free(id_in_race);
	id_in_race = malloc(sizeof(int) * (competitors));
	memcpy(id_in_race, sorted, sizeof(int) * competitors);
	free(sorted_new), free(sorted);
	print_cars(id_in_race, laps, competitors);
}


/**
 * mergeSort - function that sorts an array of ints
 * @data: is an array of int representing the “identifier” of each number.
 * @size: is the size of this array
 * @data_sorted: the pointer with the buffer of the data to be sorted
 */
void mergeSort(int *data, int size, int *data_sorted)
{
	int half_right, half_left, complement = 0;
	int *data_left, *data_right, *sorted_left, *sorted_right;

	if (size > 2)
	{
		if (size % 2 != 0)
			complement = 1;
		half_left = (size / 2) + complement, half_right = size / 2;
		if (half_right != 0)
		{
			data_right = malloc(sizeof(int) * half_right);
			sorted_right = malloc(sizeof(int) * half_right);
			memcpy(data_right, data + half_left,
			       sizeof(int) * half_right);
			mergeSort(data_right, half_right, sorted_right);
		}
		data_left = malloc(sizeof(int) * half_left);
		sorted_left = malloc(sizeof(int) * half_left);
		memcpy(data_left, data, sizeof(int) * half_left);
		mergeSort(data_left, half_left, sorted_left);
		sort2sorted_arrays(sorted_left, sorted_right, half_left,
				   half_right, data_sorted);
		free(data_right), free(data_left), free(sorted_right);
		free(sorted_left);
	}
	else
	{
		if (size == 1)
			data_sorted[0] = data[0];
		else if (size == 2)
		{
			if (data[0] <= data[1])
			{
				data_sorted[0] = data[0];
				data_sorted[1] = data[1];
			}
			else
			{
				data_sorted[0] = data[1];
				data_sorted[1] = data[0];
			}
		}
		return;
	}
}

/**
 * sort2sorted_arrays - function that sort to sorted arrays
 * @sorted_left: the first array.
 * @sorted_right: the second array
 * @size_left: the size of the left
 * @size_right: the size of the right
 * @data_sorted: the pointer of the data that is saved
 */
void sort2sorted_arrays(int *sorted_left, int *sorted_right, int size_left,
			int size_right, int *data_sorted)
{
	int iterl = 0;
	int iterr = 0;
	int i = 0;
	int total_size = size_left + size_right;

	while (i < total_size)
	{
		if (iterl < size_left &&
		    (iterr >= size_right ||
		     sorted_left[iterl] <= sorted_right[iterr]))
		{
			data_sorted[i] = sorted_left[iterl];
			iterl++;
		}
		else
		{
			data_sorted[i] = sorted_right[iterr];
			iterr++;
		}
		i++;
	}
}

/**
 * print_arrays - function that prints an array of integers
 * @array: is an array of int .
 * @size: is the size of this array
 */
void print_arrays(int *array, int size)
{
	int i;

	for (i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("/n");
}

/**
 * print_cars - function that prints an array of cars and laps
 * @id_in_race: id of the carrs in race
 * @laps: rray of laps
 * @competitors: the amount of competitors
 */
void print_cars(int *id_in_race, int *laps, int competitors)
{
	int j;

	for (j = 0; j < competitors; j++)
	{
		printf("Car %d [%d laps]\n", id_in_race[j],
		       laps[id_in_race[j]]);
	}
}
