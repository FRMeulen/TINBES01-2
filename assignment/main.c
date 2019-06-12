//	Project:	TINBES01-2.
//	main.c	--	Entry point for assignment.
//	Revisions:
//	2019-05-25	--	F.R. van der Meulen	--	Created.
//	2019-06-12	--	F.R. van der Meulen	--	Visitor added.

#include "tree.h"
#include "visitor.h"

void main(void) {

	//	Make root node and visitor.
	struct Node *root_node = create_node("ROOT");
	struct Visitor *cursor = create_visitor(root_node);

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
	print_tree(root_node, cursor, 0);

	//	Move cursor.
	go_right(cursor);
	go_down(cursor);
	go_prev(cursor);

	//	Print tree again.
	print_tree(root_node, cursor, 0);


	//	Clearing.
	printf("\n");
	clear(root_node);
}
