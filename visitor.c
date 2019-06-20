//	Project:	TINBES01-2.
//	visitor.c	--	Implementation of the Visitor struct.
//	Revisions:
//	2019-06-12	--	Created.

#include "visitor.h"

struct Visitor *create_visitor(struct Node *start) {
	struct Visitor *new_visitor = malloc(sizeof(struct Visitor));
	new_visitor->current = start;

	return new_visitor;
}

//	Moves the visitor 'up' in the tree.
//	This means the 'prev' sibling if it exists.
bool go_up(struct Visitor *visitor) {
	
	if (visitor->current->prev) {
		visitor->current = visitor->current->prev;
		return true;
	}
	
	return false;
}

//	Moves the visitor 'down' in the tree.
//	This means the 'next' sibling if it exists.
bool go_down(struct Visitor *visitor) {
	
	if (visitor->current->next) {
		visitor->current = visitor->current->next;
		return true;
	}
	
	return false;
}

//	Moves the visitor 'left' in the tree.
//	This means the 'parent' node if it exists.
bool go_left(struct Visitor *visitor) {
	
	if (visitor->current->parent) {
		visitor->current = visitor->current->parent;
		return true;
	}
	
	return false;
}

//	Moves the visitor 'right' in the tree.
//	This means the first child.
bool go_right(struct Visitor *visitor) {
	
	if (visitor->current->open && visitor->current->children_head) {
		visitor->current = visitor->current->children_head;
		return true;
	}
	
	return false;
}

//	Moves the visitor to the root of the tree.
bool go_root(struct Visitor *visitor) {
	
	while (visitor->current->parent) {
		visitor->current = visitor->current->parent;
	}

	return true;
}

//	Moves the visitor to the first sibling in the layer.
//	This means the sibling with no 'prev'.
bool go_first_sibling(struct Visitor *visitor) {
	
	if (visitor->current->prev) {
		
		while (visitor->current->prev) {
			visitor->current = visitor->current->prev;
		}

		return true;
	}
	
	return false;
}

//	Moves the visitor to the last sibling in the layer.
//	This means the sibling with no 'next'.
bool go_last_sibling(struct Visitor *visitor) {
	
	if (visitor->current->next) {
		
		while (visitor->current->next) {
			visitor->current = visitor->current->next;
		}

		return true;
	}
	
	return false;
}

//	Moves the visitor to the last child.
//	This means the child with no 'next'.
bool go_last_child(struct Visitor *visitor) {
	
	if (visitor->current->open && visitor->current->children_head) {
		visitor->current = visitor->current->children_head;

		while (visitor->current->next) {
			visitor->current = visitor->current->next;
		}

		return true;
	}
	
	return false;
}

//	Moves the visitor to the 'bottom' of a tree.
//	This means always picking the last child.
bool go_last_leaf(struct Visitor *visitor) {
	if (visitor->current->open && visitor->current->children_head) {
		while (visitor->current->open && visitor->current->children_head) {
			go_last_child(visitor);
		}

		return true;
	}

	return false;
}

//	Moves the visitor 'down' in the dumped tree.
//	ORDER:
//	1. First child.
//	2. Next sibling.
//	3. Parent's next sibling.
bool go_next(struct Visitor *visitor) {
	
	if (visitor->current->open && visitor->current->children_head) {
		visitor->current = visitor->current->children_head;
		return true;
	}

	else if (visitor->current->next) {
		visitor->current = visitor->current->next;
		return true;
	}

	while (visitor->current->parent) {
		if (visitor->current->parent->next) {
			visitor->current = visitor->current->parent->next;
			return true;
		}

		else {
			visitor->current = visitor->current->parent;
		}
	}

	return false;
}

//	Moves the visitor 'up' in the dumped tree.
//	ORDER:
//	1. Previous sibling -> last leaf.
//	2. Parent.
bool go_prev(struct Visitor *visitor) {
	
	if (visitor->current->prev) {
		visitor->current = visitor->current->prev;
		go_last_leaf(visitor);
	}

	else if (visitor->current->parent) {
		visitor->current = visitor->current->parent;
	}

	else {
		printf("No 'previous' exists!\n");
	}
}

//	Closes the current node.
bool toggle_closed(struct Visitor *visitor) {
	if (visitor->current->open) {
		visitor->current->open = false;
	}
	
	else {
		visitor->current->open = true;
	}
}
