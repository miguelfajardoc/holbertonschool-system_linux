#ifndef LAPS
#define LAPS

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

void print_arrays(int *array, int size);
void sort2sorted_arrays(int *sorted_left, int *sorted_right, int size_left,
			int size_right, int *data_sorted);
void race_state(int *id, size_t size);
void mergeSort(int *data, int size, int *data_sorted);
void print_cars(int *id_in_race, int *laps, int competitors);
#endif /* LAPS */
