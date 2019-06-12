#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tree.h"

struct Visitor {
	struct Node *current;
};

struct Visitor *create_visitor(struct Node *start);
bool go_up(struct Visitor *visitor);
bool go_down(struct Visitor *visitor);
bool go_left(struct Visitor *visitor);
bool go_right(struct Visitor *visitor);
bool go_root(struct Visitor *visitor);
bool go_first_sibling(struct Visitor *visitor);
bool go_last_sibling(struct Visitor *visitor);
bool go_last_child(struct Visitor *visitor);
bool go_last_leaf(struct Visitor *visitor);
bool go_next(struct Visitor *visitor);
bool go_prev(struct Visitor *visitor);
