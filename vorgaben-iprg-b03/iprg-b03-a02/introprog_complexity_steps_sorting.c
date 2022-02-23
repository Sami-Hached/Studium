#include <stdio.h>
#include <stdlib.h>
#include "introprog_complexity_steps_input.h"

const int MAX_VALUE = 5000000;

void count_sort_calculate_counts(int input_array[], int len, int count_array[], unsigned int* befehle) {
    *befehle = *befehle +1; // definition of i
    for (int i = 0; i <= MAX_VALUE; i++) {
      count_array[i] = 0;
      *befehle = *befehle +1; //Vergleiche
      *befehle = *befehle +1; //Inkrementierung von i
      *befehle = *befehle +1; //definition of count_array[i]
    }
    *befehle = *befehle +1; // letzter Vergleich
    *befehle = *befehle +1; // definition of i
    for (int i = 0; i <= len -1; i++) {
      *befehle = *befehle +1; // Inkrementierung von i
      *befehle = *befehle +1; //Vergleiche
      *befehle = *befehle +1; //for the action in the line below
      count_array[input_array[i]] = count_array[input_array[i]] +1;
    }
    *befehle = *befehle +1; // letzter Vergleich
}

void count_sort_write_output_array(int output_array[], int len, int count_array[], unsigned int* befehle) {
    int k =0;
    *befehle = *befehle +1; //Definition of k

    *befehle = *befehle +1; //Definition of i
    for (int i = 0; i <= MAX_VALUE; i++) {
      *befehle = *befehle +1; // Inkrementierung von i
      *befehle = *befehle +1; //Vergleiche

      *befehle = *befehle +1; //Definition of j
      for (int j = 1; j <= count_array[i]; j++) {
        *befehle = *befehle +1; // Inkrementierung von j
        *befehle = *befehle +1; //Vergleiche
        output_array [k] = i;
        k = k+1;
        *befehle = *befehle +1; // first action
        *befehle = *befehle +1; //Inkrementierung von k
      }
      *befehle = *befehle +1; // letzter Vergleich
    }
    *befehle = *befehle +1; //letzter Vergleich
}

void count_sort(int array[], int len, unsigned int* befehle) {
    // Muss implementiert werden
    int* count_array = malloc(MAX_VALUE * sizeof(int*));
    *befehle = *befehle +1; //Speicher allozieren
    count_sort_calculate_counts(array, len, count_array, befehle);
    count_sort_write_output_array(array, len, count_array, befehle);
    free(count_array);
    *befehle = *befehle +1; //Speicher frei machen
}


void insertion_sort(int array[], int len, unsigned int* befehle) {
    // Muss implementiert werden
    *befehle = *befehle +1; //Definition of j
    for(int j=1; j<len; j++){
      *befehle = *befehle +1; // Inkrementierung von j
      *befehle = *befehle +1; //Vergleiche

      int key = array[j];
      *befehle = *befehle +1; //the action in the line above
      int i = j-1;
      *befehle = *befehle +1; //the action in the line above
      while (i>=0 && array[i]>key) {
        *befehle = *befehle +1; //Vergleiche von i
        *befehle = *befehle +1; //Vergleiche von array[i]

        array[i+1] = array[i];
        *befehle = *befehle +1; //the action in the line above
        i = i-1;
        *befehle = *befehle +1; //the action in the line above
      }
      array[i+1] = key;
      *befehle = *befehle +1; //the action in the line above
    }
    *befehle = *befehle +1; //letzter Vergleich
}


int main(int argc, char *argv[]) {
    const int WERTE[] = {10000,20000,30000,40000,50000};
    const int LEN_WERTE = 5;
    const int LEN_ALGORITHMEN = 2;

    int rc = 0;
    unsigned int befehle_array[LEN_ALGORITHMEN][LEN_WERTE];
    double laufzeit_array[LEN_ALGORITHMEN][LEN_WERTE];

    for(int j = 0; j < LEN_WERTE; ++j) {
        int n = WERTE[j];

        // Reserviere Speicher für  Arrays der Länge n
        int* array_countsort = malloc(sizeof(int) * n);
        int* array_insertionsort = malloc(sizeof(int) * n);

        // Fülle array_countsort mit Zufallswerten ..
        fill_array_randomly(array_countsort, n, MAX_VALUE);
        // ... und kopiere die erzeugten Werte in das Array
        // array_insertionsort
        copy_array_elements(array_insertionsort, array_countsort, n);

        // Teste ob beide Arrays auch wirklich die gleichen Werte
        // enthalten
        if(!check_equality_of_arrays(array_countsort, array_insertionsort, n)) {
            printf("Die Eingaben für beide Algorithmen müssen für die Vergleichbarkeit gleich sein!\n");
            return -1;
        }

        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            unsigned int anzahl_befehle = 0;

            start_timer();

            // Aufruf der entsprechenden Sortieralgorithmen
            if(i==0) {
                    count_sort(array_countsort, n, &anzahl_befehle);
            } else if(i==1) {
                    insertion_sort(array_insertionsort, n, &anzahl_befehle);
            }

            // Speichere die Laufzeit sowie die Anzahl benötigter
            // Befehle
            laufzeit_array[i][j] = end_timer();
            befehle_array[i][j] = anzahl_befehle;
        }

        // Teste, ob die Ausgabe beider Algorithmen gleich sind
        if(!check_equality_of_arrays(array_countsort, array_insertionsort, n)) {
            printf("Die Arrays sind nicht gleich. Eines muss (falsch) sortiert worden sein!\n");
            rc = -1;
        }

        // Gib den Speicherplatz wieder frei
        free(array_countsort);
        free(array_insertionsort);
    }

    // Ausgabe der Anzahl ausgeführter Befehle sowie der gemessenen
    // Laufzeiten (in Millisekunden)
    printf("Parameter MAX_VALUE hat den Wert %d\n", MAX_VALUE);
    printf("\t %32s           %32s \n", "Countsort","Insertionsort");
    printf("%8s \t %16s %16s \t %16s %16s \n", "n","Befehle", "Laufzeit","Befehle","Laufzeit");

    for(int j = 0; j < LEN_WERTE; ++j) {
        printf("%8d \t ",WERTE[j]);
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("%16u %16.4f \t ",  befehle_array[i][j], laufzeit_array[i][j]);
        }
        printf("\n");
    }

    return rc;
}
