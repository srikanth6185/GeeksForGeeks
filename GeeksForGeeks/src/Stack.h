/*
 * Stack.h
 *
 *  Created on: Feb 28, 2017
 *      Author: srikanth
 */

#ifndef STACK_H_
#define STACK_H_

#define VAL 1
#define VOID_DATA 2

typedef struct st_node_s {
	void *data;
	int val;
	struct st_node_s *next;
} st_node_t;


typedef struct st_s {
	st_node_t *head;
	int count;
	int type;
} st_t;


st_t* st_create(int type);
void st_push(st_t *st, int val, void *data);
void st_pop(st_t* st, int* val, void** data);
int is_st_empty(st_t* st);
void st_destroy(st_t *st);

#endif /* STACK_H_ */
