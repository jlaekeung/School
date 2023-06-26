#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 201
int parent[MAXN];

int main(int argc, char *argv[]){
  FILE *fin, *fout;
  int i, a, b, p, n, N, root, lca;
  fin = fopen(argv[1], "r");
  fout = fopen(argv[2], "w");
  memset(parent, -1, sizeof(parent));
  fscanf(fin, "%d", &N);
  for (i = 0; i < N-1; i++) {
    fscanf(fin, "%d%d", &p, &n);
    parent[n] = p;
  }
  fscanf(fin, "%d%d", &a, &b);
  while (a != -1) {
    int b_parent = parent[b];
    while (b_parent != -1) {
      if (a == b_parent) {
        lca = a;
        goto output;
      } b_parent = parent[b_parent];
    } a = parent[a];
  }
output:
  fprintf(fout, "%d\n", lca);
  fclose(fin);
  fclose(fout);
  return 0;
}
