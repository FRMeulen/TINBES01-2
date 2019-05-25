#include "tree.h"

void main(void)
{
	//	Make root node.
	struct node *root = malloc(sizeof(struct node));
	strcpy(root->stored_name, "ROOT");
	root->left = NULL;
	root->right = NULL;
	root->depth = 0;

	//	Execute program.
	store(root, "Falco");
	store(root, "Chris");
	store(root, "Jasper");
	store(root, "Kirty");
	store(root, "Thomas");
	store(root, "Bryan");
	store(root, "Damian");
	store(root, "Noelle");
	store(root, "Sarah");

	//	Print result.
	print_alfabetical(root);

	//	Clearing.
	printf("\n");
	clear(root);
}