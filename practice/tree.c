#include "tree.h"

struct Node *create_node(char *name)
{
	struct Node *new_node = malloc(sizeof(struct Node));
	strcpy(new_node->stored_name, name);
	new_node->next = NULL;
	new_node->children_head = NULL;
	new_node->depth = 0;

	return new_node;
}

void store(struct Node *parent, char* name)
{
	if (!parent->children_head)
	{
		parent->children_head = create_node(name);
	}
	else
	{
		struct Node *temp = parent->children_head;
		while (temp->next)
		{
			temp = temp->next;
		}

		struct Node *new_node = create_node(name);
		temp->next = new_node;
		new_node->prev = temp;
	}
}

void print_tree(struct Node *node, int indentation)
{
	indent(indentation);
	printf("%s\n", node->stored_name);

	if (node->children_head)
	{
		struct Node *temp = node->children_head;
		print_tree(temp, indentation + 1);
		while (temp->next)
		{
			temp = temp->next;
			print_tree(temp, indentation + 1);
		}
	}
}

void indent(int requested_indentation)
{
	for (int i = 0; i < requested_indentation; i++)
	{
		if (i == requested_indentation - 1)
		{
			printf(" |-");
		}
		else
		{
			printf(" | ");
		}
	}
}

void clear(struct Node *node)
{
	if (node->children_head)
	{
		struct Node *temp = node->children_head;
		while (temp->next)
		{
			temp = temp->next;
		}

		while (temp->prev)
		{
			temp = temp->prev;
			clear(temp->next);
		}
		clear(temp);
	}

	if (node->prev)
	{
		node->prev->next = NULL;
	}
	printf("Freeing: %s.\n", node->stored_name);
	free(node);
}