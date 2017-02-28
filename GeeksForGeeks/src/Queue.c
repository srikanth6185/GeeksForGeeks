/*
 * Queue
 *
 *  Created on: Feb 27, 2017
 *      Author: srikanth
 */
#include<stdlib.h>
#include"Queue.h"



q_t* q_create(void)
{
	q_t *new_q;
	new_q = (q_t*)calloc(sizeof(char), sizeof(q_t));
	return new_q;
}

/* Does not free enqueued value.
 * This only deletes the q infra.
 * TODO: write a callback function
 * to free the contents.*/
void q_destroy(q_t *q)
{
	if (q) {
		q_node_t *curr = q->head, *del;
		while (curr) {
			del = curr;
			curr = curr->next;
			free(del);
		}
		free(q);
	}
}

int en_q(q_t* q, void* data)
{
	if (q && data) {
		q_node_t *new_q_node = (q_node_t*)malloc(sizeof(q_node_t));

		if (!new_q_node) {
			goto error;
		}

		if (q->head) {
			q->tail->next = new_q_node;
			q->tail = new_q_node;
		} else {
			q->head = q->tail = new_q_node;
		}

		new_q_node->data = data;
		new_q_node->next = NULL;
		q->count++;
		return Q_OK;
	}

error:
	return Q_ERR;
}


int de_q(q_t* q, void **data)
{
	if (q && *data) {
		q_node_t *del_node = q->head;

		if (is_q_empty(q)) {
			*data = NULL;
			goto error;
		}

		*data = q->head->data;
		if (q->head == q->tail) {
			q->head = q->tail = NULL;
		} else {
			q->head = q->head->next;
		}
		q->count--;
		free(del_node);
		return Q_OK;
	}
error:
	return Q_ERR;
}

int is_q_empty(q_t* q)
{
	if (q->count > 0) {
		return 0;
	}
	return 1;
}









