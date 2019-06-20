//	Project:	TINBES01-2.
//	tree.h	--	Interface for the Node struct.
//	Revisions:
//	2019-05-25	--	F.R. van der Meulen	--	Created.
//	2019-06-12	--	F.R. van der Meulen	--	Nodes now doubly linked.

# pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "visitor.h"
#include <stdbool.h>

struct Node {
	struct Node *prev;
	struct Node *next;
	struct Node *children_head;
	struct Node *parent;
	char stored_name[100];
	char path[1000];
	int children_count;
	int depth;
	bool open;
};

struct Node *create_node(char *name);
void store(struct Node *parent, struct Node *child);
void print_tree(struct Node *node, struct Visitor *visitor, int indentation);
void indent(int requested_indentation);
void clear(struct Node *node);
