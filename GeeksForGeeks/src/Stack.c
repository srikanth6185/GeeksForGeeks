/*
 * Stack.c
 *
 *  Created on: Feb 28, 2017
 *      Author: srikanth
 */
#include<stdlib.h>
#include"Stack.h"

st_t* st_create(int type)
{
	st_t* new_st = (st_t*)calloc(sizeof(char), sizeof(st_t));
	new_st->type = type;
	return new_st;
}
void st_destroy(st_t *st)
{
	if (st) {
		st_node_t *curr = st->head, *del ;
		while (curr) {
			del = curr;
			curr = curr->next;
			free(del);
		}
		free(st);
	}
}


void st_push(st_t *st, int val, void *data)
{
	if (st) {
		st_node_t* new_node = (st_node_t*)calloc(sizeof(char), sizeof(st_t));
		if (st->type == VAL) {
			new_node->val = val;
		} else if (st->type == VOID_DATA) {
			new_node->data = data;
		}
		new_node->next = st->head;
		st->head = new_node;
		st->count++;
	}
	return;
}

void st_pop(st_t* st, int* val, void** data)
{
	if (st && st->head) {
		st_node_t *del_node;
		if ((st->type == VAL) && val) {
			*val = st->head->val;
		} else if ((st->type == VOID_DATA) && data) {
			*data = st->head->data;
		} else {
			return;
		}
		del_node = st->head;
		st->head = st->head->next;
		st->count--;
		free(del_node);
	}
	return;
}


int is_st_empty(st_t* st)
{
	if (st->count > 0) {
		return 0;
	}
	return 1;
}
