
typedef struct tree_cs {
	int key;						/* key of the node */
	int value;						/* value stored in the node */
	struct tree_cs * first_child;	/* pointer to the first child */
	struct tree_cs * next_sibling;	/* pointer to the next sibling */
} Tree_CS;


/* Initialize the tree with a root #1 */
/* Create a new tree T with initialized root as (key, value) */
void tree_init(Tree_CS **T, int key, int value);

/* Insert (key, value) to the tree T #2 #3 */
/* If key already exist in T, then update the value */
/* If key does not exist in T, */
/* then add (key, value) to the last child of node with parent_key */
void tree_insert(Tree_CS *T, int parent_key, int key, int value);

/* Delete leaf with key from the tree T #4 #5 #6 */
/* If key in T and is a leaf, then delete the node */
/* Note: if it is the first child, then the second child becomes the first child */
/* Note: it if is in the middle of the sibling, then the list structure of siblings need to be maintained */
/* If key in T and key is not a leaf, then do nothing */
/* If key does not in T, then do nothing */
void tree_delete(Tree_CS *T, int key);

/* Check if key exist in the tree T or not #7 */
/* If key in T, return 1 */
/* If key not in T, return 0 */
int tree_contain(Tree_CS *T, int key);

/* Find the node based on the key in the tree T #8 */
/* If key in T, return the node of key */
/* If key does not exist in T, return NULL */
Tree_CS *tree_find(Tree_CS *T, int key);

/* Free the tree T, if T is not NULL #9 */
/* Assign NULL to T after free */
void tree_free(Tree_CS **T);

/* The print function print the tree in an output string using preorder traversal #10 */
/* The number in the bracket is key, number after bracket is value */
/* If the tree looks like */
/* (0)17 */
/* |       \ */
/* (1)12   (2)18  */
/* |        |     \ */
/* (4)0    (3)2   (8)5 */
/* Then, the output string is "(0)17 (1)12 (4)0 (2)18 (3)2 (8)5 " */
/* You can assume the number of nodes is not more than 100 */
char * tree_print(Tree_CS *T);
