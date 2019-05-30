# pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node {
	struct Node *prev;
	struct Node *next;
	struct Node *children_head;
	char stored_name[10];
	int depth;
};

struct Node *create_node(char *name);
void store(struct Node *parent, char *name);
void print_tree(struct Node *node, int indentation);
void indent(int count);
void clear(struct Node *node);