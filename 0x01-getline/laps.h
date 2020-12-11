#ifndef LAPS
#define LAPS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void sort2sorted_arrays(int * sorted_left, int *sorted_right, int size_left,
			int size_right, int *data_sorted);
void race_state(int *id, size_t size);
void mergeSort(int *data, int size, int *data_sorted);
#endif /* LAPS */
