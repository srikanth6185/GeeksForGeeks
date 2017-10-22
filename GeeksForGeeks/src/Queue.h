/*
 * Queue.h
 *
 *  Created on: Feb 27, 2017
 *      Author: srikanth
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#define Q_OK 1
#define Q_ERR -1

typedef struct q_node_s {
	void *data;
	int val;
	struct q_node_s *next;
}q_node_t;

typedef struct q_s {
	q_node_t *head;
	q_node_t *tail;
	int count;
}q_t;

q_t* q_create(void);
void q_destroy(q_t *q);
int en_q(q_t* q, void* data, int val);
int de_q(q_t* q, void **data, int *val);
int is_q_empty(q_t* q);


#endif /* QUEUE_H_ */
