/*
 * Queue
 *
 *  Created on: Feb 27, 2017
 *      Author: srikanth
 */
#include<stdlib.h>
#include"Queue.h"



/** This is a basic Queue implementation that can store void *data or integer value.
 *  On create its an empty shell.
 *  Each enq allocates a new q node and adds the passed in value to it.
 *
 *  Each deq will return the stored void*data or val based on the passed in args.
 *  Each deq will in addition delete the q node that was used to store the content.
 *
 *  Destroy is q destroy only. Its upto the caller to destroy void*data contents.
 */


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

int en_q(q_t* q, void* data, int val)
{
    if (q) {
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

        if (data) {
            new_q_node->data = data;
        } else {
            new_q_node->val = val;
        }

        new_q_node->next = NULL;
        q->count++;
        return Q_OK;
    }

error:
    return Q_ERR;
}


int de_q(q_t* q, void **data, int *val)
{
    if (q && (data || val)) {
        q_node_t *del_node = q->head;

        if (is_q_empty(q)) {
            if (data) {
                *data = NULL;
            } else {
                *val = 0;
            }
            goto error;
        }

        if (data) {
            *data = q->head->data;
        } else {
            *val = q->head->val;
        }

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









