# pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node {
	struct node *left;
	struct node *right;
	char stored_name[10];
	int depth;
};

void store(struct node *parent, char *name);
void print_alfabetical(struct node *node);
void clear(struct node *node);