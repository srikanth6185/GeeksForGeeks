#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#define LL_SUCCESS 1
#define LL_FALSE 0

typedef struct rec_debug_s {
	int rec_call_cnt;
}rec_debug_t;


typedef struct node_s {
    int data;
    struct node_s *next;
} node_t;


int ll_create(node_t **head, unsigned int n, int *input_arr);
int ll_free(node_t **head);
int ll_delete_nth_node(node_t **head, int n);
void ll_print(node_t *head);
void ll_print_rec(node_t *head);
int ll_delete_val_node(node_t **head, int val, unsigned char all);
int ll_add_node(node_t **head, int val);
int ll_get_count(node_t *head);
int ll_get_count_rec(node_t *head);
node_t* ll_find_node(node_t* head, int data);
node_t *ll_find_nth_node(node_t* head, int n);
node_t* ll_find_nth_from_last_node(node_t *head, int n);
int ll_swap_nodes(node_t **head, int data1, int data2);
node_t* ll_merge(node_t* list1, node_t* list2);
node_t* ll_reverse(node_t* head);
node_t* ll_sorted_merge(node_t* list1, node_t* list2);
node_t* ll_sorted_insert_value(node_t* head, int data);
node_t* ll_get_middle_node(node_t* head, int *even);
int ll_is_palidrome(node_t* head);
node_t* ll_get_intersect_node(node_t* list1, node_t* list2);
void ll_remove_duplicates(node_t *head);
node_t* ll_last2front(node_t* head);
node_t* ll_get_intersection_list(node_t* l1, node_t* l2);
void ll_del_alt_nodes(node_t *l);
void ll_alt_split_list(node_t *l, node_t **l1, node_t **l2);
node_t* ll_reverse_size_k(node_t *l , int k);
node_t* ll_rec_rev_k(node_t *head, int c);
node_t* ll_segregate_even_odd(node_t* head);
int ll_detect_and_remove_loop(node_t *head);

#endif // _LINKED_LIST_H_



