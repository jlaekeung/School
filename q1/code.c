#include "q1.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tree_init(Tree_CS **T, int key, int value) {
  *T = malloc(sizeof(Tree_CS));
  (*T)->key = key;
  (*T)->value = value;
  (*T)->first_child = NULL;
  (*T)->next_sibling = NULL;
}

Tree_CS *tree_find(Tree_CS *T, int key) {
  Tree_CS *tmp;
  if (T == NULL)
    return NULL;
  if (T->key == key)
    return T;
  tmp = tree_find(T->next_sibling, key);
  if (tmp != NULL)
    return tmp;
  return tree_find(T->first_child, key);
}

int tree_contain(Tree_CS *T, int key) {
  if (tree_find(T, key) != NULL)
    return 1;
  return 0;
}

void tree_insert(Tree_CS *T, int parent_key, int key, int value) {
  Tree_CS *tmp;
  if (tree_contain(T, key) == 1) {
    tmp = tree_find(T, key);
    tmp->value = value;
    return;
  }
  tmp = tree_find(T, parent_key);
  if (tmp->first_child == NULL) {
    tmp->first_child = malloc(sizeof(Tree_CS));
    tmp = tmp->first_child;
    tmp->key = key;
    tmp->value = value;
    tmp->first_child = NULL;
    tmp->next_sibling = NULL;
    return;
  }
  tmp = tmp->first_child;
  while (tmp->next_sibling != NULL) {
    tmp = tmp->next_sibling;
  }
  tmp->next_sibling = malloc(sizeof(Tree_CS));
  tmp = tmp->next_sibling;
  tmp->key = key;
  tmp->value = value;
  tmp->first_child = NULL;
  tmp->next_sibling = NULL;
}

Tree_CS *tree_get_previous(Tree_CS *T, int key) {
  Tree_CS *tmp;
  if (T == NULL)
    return NULL;
  if (T->next_sibling != NULL && T->next_sibling->key == key)
    return T;
  if (T->first_child != NULL && T->first_child->key == key)
    return T;
  tmp = tree_get_previous(T->next_sibling, key);
  if (tmp != NULL)
    return tmp;
  return tree_get_previous(T->first_child, key);
}

void tree_delete(Tree_CS *T, int key) {
  Tree_CS *prev, *tmp;
  if (T->key == key) {
    if (T->next_sibling == NULL && T->first_child == NULL) {
      free(T);
    }
    return;
  }
  tmp = tree_find(T, key);
  if (tmp == NULL || tmp->first_child != NULL) {
    return;
  }
  prev = tree_get_previous(T, key);
  if (prev->first_child == tmp) {
    prev->first_child = tmp->next_sibling;
    free(tmp);
  } else if (prev->next_sibling == tmp) {
    prev->next_sibling = tmp->next_sibling;
    free(tmp);
  }
}

void tree_free(Tree_CS **T) {
  if (T == NULL)
    return;
  if (*T == NULL)
    return;
  if ((*T)->next_sibling != NULL)
    tree_free(&((*T)->next_sibling));
  if ((*T)->first_child != NULL)
    tree_free(&((*T)->next_sibling));
  free(*T);
  *T = NULL;
}

void tree_print_recursive(Tree_CS *T, char *output) {
  if (T == NULL)
    return;
  sprintf(output, "%s(%d)%d \0", output, T->key, T->value);
  tree_print_recursive(T->first_child, output);
  tree_print_recursive(T->next_sibling, output);
}

char *tree_print(Tree_CS *T) {
  char *output = malloc(sizeof(char) * 2500);
  memset(output, 0, sizeof(char) * 2500);
  tree_print_recursive(T, output);
  return output;
}
