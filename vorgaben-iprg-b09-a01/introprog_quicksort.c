#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quicksort.h"

/*****************************************************
 * Die benoetigten structs findet Ihr in quicksort.h *
 *****************************************************/

void init_list(list* mylist)
{
    // HIER Liste initialisieren
    mylist->first = NULL;
    mylist->last = NULL;
}

// Diese Funktion fügt Listenelemente an die Liste an
void insert_list(list_element* le, list* mylist)
{
    // HIER Code einfügen
    // add element to the end of the list
    if ( mylist->first == NULL ) {
        mylist->first = le;
        mylist->last = le;
    } else {
        mylist->last->next = le;
        mylist->last = le;
    }
    le->next = NULL;
}

// Speicher für Listenelemente wieder freigeben
void free_list(list* mylist)
{
    // HIER Code einfügen
     list_element* tmp1 = mylist->first;
     list_element* tmp2 = mylist->first->next;
     while (tmp2 != NULL) {
         free (tmp1->password);
         free (tmp1);
         tmp1 = tmp2;
         tmp2 = tmp1->next;
     }
     free (tmp1->password);
     free (tmp1);
}

// Namen, Zahlen Paare in Liste einlesen
void read_data(char* filename, list* mylist)
{
		// HIER Code einfügen:
        // * Speicher allozieren
        // * Daten in list_element einlesen
        // * insert_list benutzen, um list_element in Liste einzufügen

    // Konvention: fp == file_pointer
    FILE *fp = fopen(filename, "r");
    int b;
    char a[30]; // = malloc(50 * sizeof (char));
    while (fscanf(fp, "%s %d\n", a, &b) != EOF) {
        //printf("%s %d\n", a, b);
        list_element* temp = malloc( sizeof (list_element));
        temp->next = NULL;
        temp->password = malloc(sizeof (char)*(strlen(a) + 1));
        strncpy(temp->password, a, strlen(a) +1);
        temp->count = b;
        insert_list(temp, mylist);
    }
    fclose(fp);
}

// Liste teilen. Teillisten werden in left und right zurück gegeben
list_element* partition( list* input, list* left, list* right )
{
    // HIER Code einfügen:
    // parition() Funktion implementieren
    list_element *pivot = input->first;
    list_element *tmp = pivot->next; //tmp is the element to be compared to pivot
    //input->last->next = NULL;
    while (tmp != NULL) {
        list_element *tmp2 = tmp->next;
        if (tmp->count < pivot->count) {
            insert_list(tmp, left); //add tmp to the end of left
        } else {
            insert_list(tmp, right); // add tmp to the end of right
        }
        tmp = tmp2;
    }
    return pivot;
}

// Hauptfunktion des quicksort Algorithmus

void qsort_list(list* mylist)
{
    // HIER Code einfügen
    if (mylist->first == mylist->last) {
        return;
    } else {
        list left;          //creating an initialising a left list
        init_list(&left);
        list right;         //creating an initialising a right list
        init_list(&right);

        list_element *pivot = partition(mylist, &left, &right);

        qsort_list(&left);
        qsort_list(&right);

        if (left.first == NULL) {
            mylist->first = pivot;
        } else {
            mylist->first = left.first;
            left.last->next = pivot;
        }

        if (right.first == NULL) {
            pivot->next = NULL;
            mylist->last = pivot;
        } else {
            pivot->next = right.first;
            mylist->last = right.last;
        }
    }
}

// Liste ausgeben
void print_list(list* mylist)
{
    // HIER Code einfügen:
    // * Laufe über die list_element in mylist und gebe sie aus.
    list_element* tmp = mylist->first;
    while (tmp != NULL) {
        printf("%s %d\n", tmp->password, tmp->count);
        tmp = tmp->next;
    }
}

