/*
 * MergeSortList.c
 *
 *  Created on: Oct 9, 2016
 *      Author: srikanth
 */
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/* Splits the list into two.
 * Even numbered nodes will split into equal lists
 * Odd numbered nodes will split into (n/2+1), n/2
 * */
void split_list(node_t *a, node_t **b)
{
	node_t *slow = a, *fast = a;
	*b = NULL;

	if (!slow || !slow->next) {
		return;
	}

	while(fast && fast->next) {
		fast = fast->next;
		if (fast->next) {
			fast = fast->next;
		} else {
			break;
		}
		slow = slow->next;
	}

	*b = slow->next;
	slow->next = NULL;
	return;
}

/**
 * Merge two sorted lists using recursion.
 */
node_t* merge_sorted_list_rec(node_t* a, node_t* b)
{
	if(!a) {
		return b;
	} else if (!b) {
		return a;
	}

	if (a->data <= b->data) {
		a->next = merge_sorted_list_rec(a->next, b);
		return a;
	} else {
		b->next = merge_sorted_list_rec(a, b->next);
		return b;
	}
}

/**
 * Merge sort a list using recursion.
 */
node_t* merge_sort_rec(node_t *head, rec_debug_t *dbg)
{
	node_t *a, *b;

	dbg->rec_call_cnt++;

	if (!head || !head->next) {
		return head;
	}

	a = head;
	split_list(a, &b);

	a = merge_sort_rec(a, dbg);
	b = merge_sort_rec(b, dbg);

	return merge_sorted_list_rec(a,b);
}


void test_ll_merge_sort(void)
{
	int arr[6] = {5,4,3,1,2,6};
	node_t *head;
	rec_debug_t dbg;

	printf("%s: START\n", __FUNCTION__);

	ll_create(&head, 6, arr);
	ll_print(head);

	head = merge_sort_rec(head, &dbg);

	printf("%s: Sorted list\n", __FUNCTION__);
	ll_print(head);
	ll_free(&head);
	return;
}



