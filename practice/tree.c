#include "tree.h"

void store(struct node *parent, char* name)
{
	struct node *new_node = malloc(sizeof(struct node));
	strcpy(new_node->stored_name, name);
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->depth = parent->depth + 1;

	if (name[0] < parent->stored_name[0])
	{
		if (!parent->left)
		{
			parent->left = new_node;
		}

		else
		{
			store(parent->left, name);
		}
	}

	else
	{
		if (!parent->right)
		{
			parent->right = new_node;
		}

		else
		{
			store(parent->right, name);
		}
	}
}

void print_alfabetical(struct node *node)
{
	if (node->left)
	{
		print(node->left);
	}

	printf("Stored name:\t%s\t\t at depth:\t%d.\n", node->stored_name, node->depth);

	if (node->right)
	{
		print(node->right);
	}

}