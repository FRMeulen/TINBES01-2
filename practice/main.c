#include "tree.h"
#include <sys/types.h>
#include <dirent.h>

void main(void)
{
	//	Make root node.
	struct Node *root_node = create_node("ROOT");

	//	Execute program.
	store(root_node, "Falco");
	store(root_node, "Chris");
	store(root_node, "Dane");
	store(root_node->children_head, "Jasper");
	store(root_node->children_head->next, "Kirty");
	store(root_node->children_head, "Thomas");
	store(root_node->children_head->next->next, "Bryan");
	store(root_node->children_head->children_head, "Damian");
	store(root_node->children_head->children_head, "Noelle");
	store(root_node->children_head->children_head->next, "Sarah");

	//	Print tree.
	print_tree(root_node, 0);

	//	Clearing.
	printf("\n");
	clear(root_node);
}