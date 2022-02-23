#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"



/*
 * Fügt einen Knoten mit der Telefonnummer phone und dem Namen name
 * in den Binären Suchbaum bst ein.  Für den Suchbaum soll die
 * Eigenschaft gelten, dass alle linken Kinder einen Wert kleiner
 * gleich (<=) und alle rechten Kinder einen Wert größer (>) haben.
 */
void bst_insert_node(bstree* bst, unsigned long phone, char *name) {
  bst_node *new = (bst_node*) calloc(1, sizeof(bst_node)); // node to be added
  bst_node *x = bst->root;        // Hilfsstrucktur
  bst_node *y = NULL; // y will be parent of new
  new->phone = phone;
  new->name = calloc( strlen(name) + 1 , sizeof(char));
  strncpy(new->name, name, strlen(name));

  while (x) {
    y =x;
    if (phone == x->phone) {
      printf("This number already exists\n");
      return;
    } else if (phone < x->phone) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  new->parent = y;
  if (y == NULL) {
    bst->root = new;
  } else {
        if (phone <= y->phone) {
          y->left = new;
        } else {
          y->right = new;
        }
  }
}


/*
 * Diese Funktion liefert einen Zeiger auf einen Knoten im Baum mit
 * dem Wert phone zurück, falls dieser existiert.  Ansonsten wird
 * NULL zurückgegeben.
 */
bst_node* find_node(bstree* bst, unsigned long phone) {
  bst_node* node = bst->root;
  while  (node != NULL && phone != node->phone) {
    if (phone <= node->phone) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return node;
}

/* Gibt den Unterbaum von node in "in-order" Reihenfolge aus */
void bst_in_order_walk_node(bst_node* node) {
  if (node != NULL) {
    bst_in_order_walk_node(node->left);
    print_node(node);
    bst_in_order_walk_node(node->right);
  }
}

/*
 * Gibt den gesamten Baum bst in "in-order" Reihenfolge aus.  Die
 * Ausgabe dieser Funktion muss aufsteigend soriert sein.
 */
void bst_in_order_walk(bstree* bst) {
    if (bst != NULL) {
        bst_in_order_walk_node(bst->root);
    }
}

/*
 * Löscht den Teilbaum unterhalb des Knotens node rekursiv durch
 * "post-order" Traversierung, d.h. zurerst wird der linke und dann
 * der rechte Teilbaum gelöscht.  Anschließend wird der übergebene
 * Knoten gelöscht.
 */
void bst_free_subtree(bst_node* node) {
  if (node) {
    bst_node *x = node->left;
    bst_node *y = node->right;
    if (x) { bst_free_subtree(x); }
    if (y) { bst_free_subtree(y); }
    free(node->name);
    free(node);
  }
}

/*
 * Löscht den gesamten Baum bst und gibt den entsprechenden
 * Speicher frei.
 */
void bst_free_tree(bstree* bst) {
    if(bst != NULL && bst->root != NULL) {
        bst_free_subtree(bst->root);
        bst->root = NULL;
    }
}
