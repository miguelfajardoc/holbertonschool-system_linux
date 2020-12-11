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
	static int laps[592];
	static int competitors;
	int i, j;
	int exist = 0;
	int to_sort_b[100];
	int amount_sort = 0;
	int *sorted_new;
	int *sorted;

	for (i = 0; i < (int)size; i++)
	{
		for (j = 0; j < competitors; j++)
		{
			if (id[i] == id_in_race[j])
			{
				laps[id_in_race[j]]++;
				exist = 1;
			}
		}
		if (!exist)
		{
			/* id_in_race[competitors] = id[i]; */
			printf("Car %d joined the race\n", id[i]);
			to_sort_b[amount_sort] = id[i];
			amount_sort++;
		}
		exist = 0;
	}
	competitors = amount_sort;
	sorted_new = malloc(sizeof(int) * amount_sort);
	mergeSort(to_sort_b, amount_sort, sorted_new);
	sorted = malloc(sizeof(int) * (competitors + amount_sort));
	sort2sorted_arrays(sorted, id_in_race, amount_sort,
			     competitors + amount_sort, sorted);
	printf("Race state:\n");
	id_in_race = sorted;
	for ( j = 0; j < competitors; j++)
	{
		printf("Car %d [%d laps]\n", id_in_race[j],
		       laps[id_in_race[j]]);
	}
}


/**
 * sort - function that sorts an array of ints
 * @id: is an array of int representing the “identifier” of each number.
 * @size: is the size of this array
 * @sorted: the pointer with the buffer of the data to be sorted
 */
void mergeSort(int *data, int size, int *data_sorted)
{
	int half_right, half_left;
	int complement = 0;
	int *data_left;
	int *data_right;
	int *sorted_left;
	int *sorted_right;

	if (size > 2)
	{
		if (size % 2 != 0)
			complement = 1;
		half_left = size / 2 + complement;
		half_right = size / 2;
		data_left = malloc(sizeof(int) * half_left);
		sorted_left = malloc(sizeof(int) * half_left);
		data_right = malloc(sizeof(int) * half_right);
		sorted_right = malloc(sizeof(int) * half_right);
		memcpy(data_left, data, sizeof(int) * half_left);
		memcpy(data_right, data + half_left, sizeof(int) * half_right);
		mergeSort(data_left, half_left, sorted_left);
		mergeSort(data_right, half_right, sorted_right);
		sort2sorted_arrays(sorted_left, sorted_right, half_left, half_right,
				   data_sorted);
		free(data_right), free(data_left), free(sorted_right);
		free(sorted_left);
	}
	else{
		if (size == 1)
			data_sorted[0] = data[0];
		else
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


void sort2sorted_arrays(int * sorted_left, int *sorted_right, int size_left,
			int size_right, int *data_sorted)
{
	int iterl = 0;
	int iterr = 0;
	int i = 0;
	int total_size = size_left + size_right;

	while (i < total_size)
	{
		if(iterl < size_left &&
		   (iterr >=size_right || sorted_left[iterl] <= sorted_right[iterr]))
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
