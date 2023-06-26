#include"lab5-q2.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tree_init(BTree **T, int key, double value, int max_size) {
  *T = (BTree *)malloc(sizeof(BTree));
  (*T)->key = (int *)malloc(max_size * sizeof(int));
  (*T)->value = (double *)malloc(max_size * sizeof(double));
  (*T)->max_size = max_size;
  for (int i = 0; i < max_size; i++) {
    (*T)->key[i] = INT_MAX;
    (*T)->value[i] = -2100;
  }
  (*T)->key[0] = key;
  (*T)->value[0] = value;
}

void tree_init_with_array(BTree **T, int *key, double *value, int n, int max_size) {
  tree_init(T, INT_MAX, -2100, max_size);
  for (int i = 0; i < max_size; i++) {
     if (i < n) {
       (*T)->key[i] = key[i];
       (*T)->value[i] = value[i];
     } else {
       (*T)->key[i] = INT_MAX;
       (*T)->value[i] = -2100;
     }
   }
}

void tree_init_with_height(BTree **T, int height) {
  int max_size = (int)pow(2, height + 1) - 1;
  tree_init(T, INT_MAX, -2100, max_size);
}

int tree_parent(BTree *T, int child_index) {
  if (child_index <= 0 || child_index >= T->max_size)
    return -2100;
  return (child_index - 1) / 2;
}

int tree_lchild(BTree *T, int parent_index) {
  int left_index = 2 * parent_index + 1;
  if (left_index >= T->max_size)
    return -2100;
  return left_index;
}

int tree_rchild(BTree *T, int parent_index) {
  int right_index = 2 * parent_index + 2;
  if (right_index >= T->max_size)
    return -2100;
  return right_index;
}

void tree_insert_lchild(BTree *T, int parent_index, int key, double value) {
  for (int i = 0; i < T->max_size; i++) {
    if (T->key[i] == key) {
      T->value[i] = value;
      return;
    }
  }
  int left_index = tree_lchild(T, parent_index);
  if (left_index != -2100 && left_index != key && T->key[left_index] == INT_MAX) {
     T->key[left_index] = key;
     T->value[left_index] = value;
   }
}

void tree_insert_rchild(BTree *T, int parent_index, int key, double value) {
  for (int i = 0; i < T->max_size; i++) {
    if (T->key[i] == key) {
      T->value[i] = value;
      return;
    }
  }
  int right_index = tree_rchild(T, parent_index);
  if (right_index != -2100 && right_index != key && T->key[right_index] == INT_MAX) {
     T->key[right_index] = key;
     T->value[right_index] = value;
   }
}

double tree_key_find(BTree *T, int key) {
  for (int i = 0; i < T->max_size; i++)
    if (T->key[i] == key)
      return T->value[i];
  return -2100.0;
}

double tree_index_find(BTree *T, int index) {
  if (index < 0 || index >= T->max_size || T->key[index] == INT_MAX)
    return -2100.0;
  return T->value[index];
}

void tree_free(BTree **T) {
  if (*T != NULL) {
    free((*T)->key);
    free((*T)->value);
    free(*T);
    *T = NULL;
  }
}

void tree_postorder(BTree *T, int index, char *output) {
  if (index >= T->max_size || T->key[index] == INT_MAX)
    return;
  tree_postorder(T, tree_lchild(T, index), output);
  tree_postorder(T, tree_rchild(T, index), output);
  char buffer[100];
  sprintf(buffer, "(%d)%.2f ", T->key[index], T->value[index]);
  strcat(output, buffer);
}

char *tree_print(BTree *T) {
  char *output = malloc(sizeof(char) * 3000);
  output[0] = '\0';
  tree_postorder(T, 0, output);
  return output;
}
