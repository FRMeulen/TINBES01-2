/*
 *
 * BertOS - Memory allocator
 * src/alloc.c
 *
 * Copyright (C) 2019 Bastiaan Teeuwen <bastiaan@mkcl.nl>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 */

#include <alloc.h>

static struct block *head;

/* A pointer to the end of the kernel, all memory past this point is free */
extern uintptr_t kern_end;

static void *block_alloc(size_t n)
{
	//	Declare new block.
	struct block *new_block;		//	NOTE:	Warning: may be uninitialised when used.	-	Vraag aan Jacques!

	//	Check if first block.
	if(!head)
	{
		//	New block is the head.
		new_block = head;
		
		//	Assign properties.
		new_block->addr = &kern_end + sizeof(struct block);
		new_block->size = n;
		new_block->used = true;
		new_block->next = NULL;
	}
	
	else
	{
		//	Get last block in list.
		struct block *temp;
		temp = head;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}

		//	Store block properties.
		new_block->addr = temp->addr + temp->size + sizeof(struct block);
		new_block->size = n;
		new_block->used = true;
		new_block->next = NULL;
		temp->next = new_block->addr;
	}

	return new_block->addr;

}

static void block_free(struct block *bptr)
{
	bptr->used = false;
}

static void *block_get(size_t n)
{
	struct block *temp;

	if (!head)
	{
		return NULL;
	}

	else
	{
		temp = head;
		while (temp->next != NULL)
		{
			if (temp->used == false)
			{
				if (temp->size >= n)
				{
					temp->used = true;
					return temp->addr;	
				}
			}

			temp = temp->next;
		}

		return NULL;

	}
	
}

void *malloc(size_t n)
{
	if (n != 0)
	{
		if (block_get(n) == NULL)
		{
			return block_alloc(n);
		}

		else
		{
			return block_get(n);
		}
	}

	else
	{
		return NULL;
	}
}

void free(void *ptr)
{
	if (ptr != NULL)
	{
		block_free(ptr - sizeof(struct block));
	}
}

void *realloc(void *ptr, size_t n)
{
	/* TODO */
}

void *calloc(size_t n, size_t m)
{
	/* TODO */
}
