#include "tree.h"
#include "visitor.h"

void main(void)
{
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
	print_tree(root_node, 0);

	//	Cursor testing.
	printf("%s\n", cursor->current->stored_name);
	go_down(cursor);
	printf("%s\n", cursor->current->stored_name);
	go_right(cursor);
	printf("%s\n", cursor->current->stored_name);
	go_down(cursor);
	printf("%s\n", cursor->current->stored_name);
	go_prev(cursor);
	printf("%s\n", cursor->current->stored_name);
	go_next(cursor);
	printf("%s\n", cursor->current->stored_name);
	go_next(cursor);
	printf("%s\n", cursor->current->stored_name);
	go_prev(cursor);
	go_prev(cursor);
	go_prev(cursor);
	go_prev(cursor);
	printf("%s\n", cursor->current->stored_name);

	//	Clearing.
	printf("\n");
	clear(root_node);
}
