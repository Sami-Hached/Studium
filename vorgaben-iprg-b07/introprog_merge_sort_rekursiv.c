#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des letzten Elements(Ende) des (Teil-)Array
 */
void merge(int* array, int first, int middle, int last)
{
  int *Be = calloc(last - first +1, sizeof(int));
  int k = first; //variable for the left side
  int m = middle +1; //variable for the right side
  int i = 0; //variable for the array Be

  //as long as we still have numbers on both sides
  while (k <= middle && m <= last) {
    if (array[k] <= array[m]) {
      Be[i++] = array[k++]; // insert the smaller variable in B at index i
    } else {                // then increment both respective variables
      Be[i++] = array[m++];
    }
  }

  //copying the rest of the left half
  while (k <= middle) {
    Be[i++] = array[k++];
  }

  //copying the rest of the right half
  while (m <= last) {
    Be[i++] = array[m++];
  }

  //print_array(Be, i);
  //moving numbers from Be to Array
  // i-1 is the last index in Be (cuz i++ at the last while iteration)
  int j = 0; //variable for the array Array
  while (j < i) {
    array[first + j] = Be[j];
    j++;
  }

  //freeing the allocated memory
  free(Be);
  return;
}

/*
 * Diese Funktion implementiert den rekursiven Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array: Pointer auf das Array
 * first: Index des ersten Elements des (Teil-)Array
 * last:  Index des letzten Elements des (Teil-)Array
 */
void merge_sort(int* array, int first, int last)
{
  // HIER Funktion merge_sort() implementieren
  if (first < last) {
    int middle = (first + last)/2;
    merge_sort(array, first, middle); //sort the left side
    merge_sort(array, middle +1, last); // sort the right side
    merge(array, first, middle, last); // merge the sorted halves
  }
}

/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_rekursiv <maximale anzahl> \
 *         <dateipfad>
 */
int main (int argc, char *argv[])
{
    if (argc!=3){
        printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
        exit(2);
    }

    char *filename = argv[2];

    // Hier array initialisieren
    int *array = (int *) calloc (atoi(argv[1]), sizeof(int)); //Allocate memory and initialise

    int len = read_array_from_file(array, atoi(argv[1]), filename);

    printf("Eingabe:\n");
    print_array(array, len);

    // HIER Aufruf von "merge_sort()"
    merge_sort(array, 0, len-1); // sort from first index 0 to last index len-1

    printf("Sortiert:\n");
    print_array(array, len);

    free(array); // free the allocated memory

    return 0;
}
