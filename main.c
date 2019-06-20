//	Project:	TINBES01-2.
//	main.c	--	Entry point for assignment.
//	Revisions:
//	2019-05-25	--	F.R. van der Meulen	--	Created.
//	2019-06-12	--	F.R. van der Meulen	--	Visitor added.

#include "tree.h"
#include "visitor.h"
#include <stdbool.h>
#include <dirent.h>

//	List files.
void list_files(char *base_path, struct Node *parent) {
	char path[1000];
	struct dirent *dp;
	DIR *dir = opendir(base_path);

	//	Filter files.
	if (!dir)
		return;

	//	List all children.
	while ((dp = readdir(dir)) != NULL) {
		//	Filter current and previous directory.
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
			//	Create and store node.
			struct Node *dir_node = create_node(dp->d_name);
			strcpy(path, base_path);
			strcat(path, "/");
			strcat(path, dp->d_name);
			dir_node->path = path;
			store(parent, dir_node);
		}
	}
	closedir(dir);

	//	List files on all children.
	struct Node *temp = parent->children_head;
	strcpy(path, base_path);
	strcat(path, "/");
	strcat(path, temp->stored_name);
	list_files(path, temp);

	while (temp->next) {
		temp = temp->next;
		strcpy(path, base_path);
		strcat(path, "/");
		strcat(path, temp->stored_name);
		list_files(path, temp);
	}
}

void open_file(struct Node *file) {
	if (strstr(file->stored_name, ".txt") != NULL) {
		char command[1000] = "vim";
		strcat(command, " ");
		strcat(command, file->path);

		printf("Opening file: %s\n", file->path);
	}

	else {
		printf("Error! Not a file!");
	}
}

void main(void) {

	//	Make root node and visitor.
	struct Node *root_node = create_node("ROOT");
	struct Visitor *cursor = create_visitor(root_node);

	//	Get directory info.
	char path[1000];
	list_files("/home/falco/Documents/TI/TESTING", root_node);
	
	//	Print tree.
	system("clear");
	print_tree(root_node, cursor, 0);

	//	Command loop.
	char command[3];
	bool exit = false;
	while (!exit) {
		//	Read command.
		printf("\n");
		printf("Commands:\n");
		printf("	W - Up.\n");
		printf("	S - Down.\n");
		printf("	A - Left.\n");
		printf("	D - Right.\n");
		printf("	Z - Previous sibling.\n");
		printf("	X - Next sibling.\n");
		printf("	R - Root.\n");
		printf("	O - Open file in vim.\n");
		printf("	C - Open/Close.\n");
		printf("	H - Help.\n");
		printf("\n");
		printf("Enter command: ");
		scanf("%s", &command);

		//	Process input.
		char c = command[0];
		if (c == 'w' || c == 'W') {
			go_prev(cursor);
		}

		else if (c == 's' || c == 'S') {
			go_next(cursor);
		}

		else if (c == 'a' || c == 'A') {
			go_left(cursor);
		}

		else if (c == 'd' || c == 'D') {
			go_right(cursor);
		}

		else if (c == 'z' || c == 'Z') {
			go_up(cursor);
		}

		else if (c == 'x' || c == 'X') {
			go_down(cursor);
		}

		else if (c == 'r' || c == 'R') {
			go_root(cursor);
		}

		else if (c == 'o' || c == 'O') {
			open_file(cursor->current);
		}

		else if (c == 'c' || c == 'C') {
			toggle_closed(cursor);
		}

		else if (c == 'q' || c == 'Q') {
			printf("Exiting!\n");
			exit = true;
		}

		else if (c == 'h' || c == 'H') {
			system("clear");
			printf("--Navigation Help Page--\n");
			printf("The file navigation has several options:\n");
			printf("	U - Moves the cursor to the node above the currently selected node.\n");
			printf("	D - Moves the cursor to the node below the currently selected node.\n");
			printf("	A - Moves the cursor to the parent of the currently selected node.\n");
			printf("	D - Moves the cursor to the first child of the currently selected node.\n");
			printf("	Z - Moves the cursor to the node above the currently selected node, but within the same layer.\n");
			printf("	X - Moves the cursor to the node below the currently selected node, but within the same layer.\n");
			printf("	R - Moves the cursor to the root node.\n");
			printf("	O - Opens the file at the cursor in vim.\n");
			printf("	C - Closes or opens the currently selected node, hiding all children.\n");
			printf("	Q - Exits the program.\n");
			printf("	H - Displays this help page.\n");
			printf("\n");
			printf("Press any key, then enter to continue...\n");
			char continueChar[3];
			scanf("%s", &continueChar);
		}

		else {
			printf("Unknown command!\n");
		}

		system("clear");
		print_tree(root_node, cursor, 0);
	}

	//	Clearing.
	printf("\n");
	clear(root_node);
}
