#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/*Create linked list with n nodes.*/
int ll_create(node_t **head, unsigned int n, int *input_arr)
{
    int data = 1, input_idx = 0;
    node_t *tmp;
    printf("%s: START\n", __FUNCTION__);
    /*If input value arr present use the arr*/
    if (input_arr) {
        data = input_arr[input_idx++];
    }

    *head = NULL;
    if (!n) {
        goto error;
    }


    *head = tmp = (node_t*)malloc(sizeof(node_t));
    if (tmp == NULL) {
        goto error;
    }

    tmp->data = data++;
    while (((n-1) > 0)) {
        tmp->next = (node_t*)malloc(sizeof(node_t));
        if(tmp->next == NULL) {
            goto error;
        }
        tmp = tmp->next;

        /*Use array if present*/
        if (!input_arr) {
            tmp->data = data++;
        } else {
            tmp->data = input_arr[input_idx++];
        }
        n--;
    }
    tmp->next = NULL;
    return LL_SUCCESS;

error:
    return LL_FALSE;
}


/*Free the list and reset the head pointer.*/
int ll_free(node_t **head)
{
    node_t *tmp = *head, *del_node;
    printf("%s: START\n", __FUNCTION__);
    while(tmp) {
        del_node = tmp;
        tmp = tmp->next;
        free(del_node);
    }
    *head = NULL;
    return LL_SUCCESS;
}


void ll_print(node_t *head)
{
   // printf("%s: START\n", __FUNCTION__);
    while ( head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n\n");
}

void ll_print_rec(node_t *head)
{
    if (head) {
        ll_print_rec(head->next);
        printf("%d<-", head->data);
    } else {
        printf("NULL<-");
    }
    return;
}

int ll_delete_nth_node(node_t **head, int n)
{
    node_t *prev = NULL, *curr= *head, *del_node;
    int ctr = 1;
    printf("%s: START\n", __FUNCTION__);
    /*Keep walking the list till you reach nth node.*/
    while(curr) {
        if (ctr == n) {
            del_node = curr;
            if (prev) {
                prev->next = curr->next;
            } else {
                *head = curr->next;
            }
            free(del_node);
            return LL_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
        ctr++;
    }

    /*List is too small or empty*/
    return LL_FALSE;
}

/*
This API will remove all occurrences of val
from the node if flag is set. Or just the first
one
*/
int ll_delete_val_node(node_t **head, int val, unsigned char all)
{
    node_t *prev = NULL, *curr= *head, *del_node = NULL;
    printf("%s: START\n", __FUNCTION__);
    while (curr) {
        if (curr->data == val) {
            if (prev) {
                prev->next = curr->next;
            } else {
                /*Handle case where node is
                  the first node.*/
                *head = curr->next;
            }
            del_node = curr;
            curr = curr->next;
            free(del_node);
            if (!all) {
                return LL_SUCCESS;
            }
            continue;
        }

        /*Iterate*/
        prev = curr;
        curr = curr->next;
    }

    /*Return success only if a node has
      been deleted.*/
    if (del_node) {
        return LL_SUCCESS;
    }

    return LL_FALSE;
}

/*@warn: Empty list must have NULL head*/
int ll_add_node(node_t **head, int val)
{
    node_t *tmp;
    printf("%s: START\n", __FUNCTION__);
    tmp = (node_t *)malloc(sizeof(node_t));
    if (!tmp) {
        return LL_FALSE;
    }

    tmp->data = val;
    tmp->next = (*head);
    *head = tmp;

    return LL_SUCCESS;
}

int ll_get_count(node_t *head)
{
    int cnt = 0;
    //printf("%s: START\n", __FUNCTION__);
    while(head) {
        cnt++; head = head->next;
    }
    return cnt;
}

int ll_get_count_rec(node_t *head)
{
    if (head) {
        return ( 1 + ll_get_count_rec(head->next));
    }
    return 0;
}


node_t* ll_find_node(node_t* head, int data)
{
    printf("%s: START\n", __FUNCTION__);
    while(head) {
        if (head->data == data) {
            printf("Found node with data %d\n", data);
            break;
        }
        head = head->next;
    }

    return head;
}

node_t *ll_find_nth_node(node_t* head, int n)
{
    int cnt = 1;
    printf("%s: START\n", __FUNCTION__);
    if (n <= 0) {
        return NULL;
    }

    while (head && (cnt < n)) {
        head = head->next;
        cnt++;
    }
    printf("n = %d th node = %d\n", n, head ? head->data : 0);
    return head;
}

node_t* ll_find_nth_from_last_node(node_t *head, int n)
{
    node_t *nth_node = head;
    int cnt = 0;
    printf("%s: START\n", __FUNCTION__);
    if (n <= 0) {
        return NULL;
    }

    while((cnt < n) && head) {
        head = head->next;
        cnt++;
    }

    if (!head && cnt != n) {
        return NULL;
    }

    while(head) {
        head = head->next;
        nth_node = nth_node->next;
    }
    printf("n = %d node = %d from the last \n", n, nth_node->data);
    return nth_node;
}

int ll_swap_nodes(node_t **head, int data1, int data2)
{
    node_t *tmp, *prev;
    node_t *prev1, *prev2, *node1 = NULL, *node2 = NULL;
    printf("%s: START\n", __FUNCTION__);
    tmp = *head;
    prev = NULL;

    /*Find first node*/
    while(tmp) {
        if (tmp->data == data1) {
            prev1 = prev;
            node1 = tmp;
        } else if (tmp->data == data2) {
            prev2 = prev;
            node2 = tmp;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    /* Return false if :
       1. Any of the nodes are NULL;
       2. If the nodes are the same.
    */
    if (!node1 || !node2 || (node1 == node2)) {
        return LL_FALSE;
    }

    if (prev1) {
        prev1->next = node2;
        if (prev2) {
            prev2->next = node1;
        } else {
            *head = node1;
        }
    } else {
        *head = node2;
        prev2->next = node1;
    }

    /*Swap next pointers*/
    tmp = node1->next;
    node1->next = node2->next;
    node2->next = tmp;

    return LL_SUCCESS;
}

/*Assumes the list is already sorted*/
node_t* ll_sorted_insert(node_t* head, node_t* node)
{
    node_t* curr = head, *prev = NULL;

    while (curr && node) {
        if (node->data >= curr->data) {
            prev = curr;
            curr = curr->next;
        } else {
            if (prev) {
                prev->next = node;
            } else {
                head = node;
            }
            node->next = curr;
            break;
        }
    }

    if (!curr) {
        if (prev) {
            prev->next = node;
        } else {
            head = node;
        }
        node->next  = NULL;
    }

    return head;
}


node_t* ll_merge(node_t* list1, node_t* list2)
{
    node_t *curr1, *curr2, *new_list = NULL, *tmp;
    printf("%s: START\n", __FUNCTION__);
    curr1 = list1;
    curr2 = list2;

    while(curr1) {
        tmp = curr1->next;
        new_list = ll_sorted_insert(new_list, curr1);
        curr1 = tmp;
    }

    ll_print(new_list);

    while(curr2) {
        tmp = curr2->next;
        new_list = ll_sorted_insert(new_list, curr2);
        curr2 = tmp;
    }

    return new_list;
}

node_t* ll_reverse(node_t* head)
{
    node_t* curr = head, *prev = NULL;
    printf("%s: START\n", __FUNCTION__);
    while(curr) {
        node_t *tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }

    return prev;
}

node_t* ll_sorted_insert_value(node_t* head, int data)
{
    node_t *curr = head, *prev = NULL, *new_node;
    new_node = (node_t*)malloc(sizeof(node_t));

    printf("\n%s: START\n", __FUNCTION__);

    if (!new_node) {
        printf("%s: MEM failure\n", __FUNCTION__);
        return NULL;
    } else {
        new_node->data = data;
        new_node->next = NULL;
    }

    while (curr) {
        if (curr->data >= data) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if (prev) {
        new_node->next = prev->next;
        prev->next = new_node;
        return head;
    } else {
        new_node->next = curr;
        return new_node;
    }
}

node_t* ll_get_middle_node(node_t* head, int *even)
{
    node_t *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    if (even) {
        *even = fast ? 0 : 1;
    }
    return slow;
}


int ll_is_palidrome(node_t* head)
{
    node_t *curr, *middle, *next;
    node_t *stack_top = NULL, *stack_curr;
    int result = 1, even = 0;

    if (!head || !head->next) {
        printf("%s: List %s\n", __FUNCTION__, head ? "has-single-node": "is-empty");
        return 0;
    }

    curr = middle = ll_get_middle_node(head, &even);
    if (!even) {
        curr = middle->next;
    }
    /*Load the second half of the nodes on the stack*/
    while (curr) {
        next = curr->next;
        curr->next = stack_top;
        stack_top = curr;
        curr = next;
    }

    /*Compare the two lists till the middle*/
    curr = head;
    stack_curr = stack_top;
    while(curr->next != middle) {
        if (curr->data != stack_curr->data) {
            result = 0;
        }
        curr = curr->next;
        stack_curr = stack_curr->next;
    }

    /*Recover the list. Curr is already just before the middle.*/
    if (!even) {
        /* If there are odd number of nodes then use the middle
         * node as the starting point. */
        curr = middle;
    }
    curr->next = NULL;
    stack_curr = stack_top;
    while (stack_top) {
        stack_curr = stack_top->next;
        stack_top->next = curr->next;
        curr->next = stack_top;
        stack_top = stack_curr;
    }
    return result;
}

node_t* ll_get_intersect_node(node_t* list1, node_t* list2)
{
    int c1, c2, diff;
    node_t *curr1 = list1, *curr2 = list2;

    c1 = ll_get_count(list1);
    c2 = ll_get_count(list2);

    if (c1 > c2) {
        diff = c1 - c2;
        printf("%s: Diff in length is %d\n", __FUNCTION__, diff);

        while (diff) {
            curr1 = curr1->next;
            diff--;
        }
    } else if (c1 < c2){
        diff = c2 - c1;
        printf("%s: Diff in length is %d\n", __FUNCTION__, diff);

        while (diff) {
            curr2 = curr2->next;
            diff--;
        }
    }

    while (curr1 && curr2) {
        if (curr1 == curr2) {
            printf("%s: Found intersection at (%p)->%d\n", __FUNCTION__, curr1, curr1->data);
            return curr1;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    printf("%s: No intersection node\n", __FUNCTION__);
    return NULL;
}

void ll_remove_duplicates(node_t *head)
{
    node_t *curr = head, *prev = NULL;
    printf("%s\n", __FUNCTION__);
    while(curr) {
        if (prev && (prev->data == curr->data)) {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
            continue;
        }
        prev = curr;
        curr = curr->next;
    }
    return;
}


node_t* ll_last2front(node_t* head)
{
    node_t *curr = head, *prev = NULL;
    printf("%s\n", __FUNCTION__);
    while (curr) {
        if (curr->next == NULL) {
            break;
        }
        prev = curr; curr = curr->next;
    }

    if (prev) {
        prev->next = NULL;
        curr->next = head;
    }
    return curr;
}

/*Sorted lists*/
node_t* ll_get_intersection_list(node_t* l1, node_t* l2)
{
    node_t *new_ll, *curr;
    new_ll = curr = NULL;
    printf("%s\n", __FUNCTION__);
    while (l1 && l2) {
        if (l1->data == l2->data) {
            if (new_ll) {
                curr->next = (node_t*)malloc(sizeof(node_t));
                curr = curr->next;
            } else {
                new_ll = curr = (node_t*)malloc(sizeof(node_t));
            }
            curr->data = l1->data;
            curr->next = NULL;
            l1 = l1->next;
            l2 = l2->next;
        } else if (l1->data < l2->data) {
            l1 = l1->next;
        } else {
            l2 = l2->next;
        }
    }
    return new_ll;
}

void ll_del_alt_nodes(node_t *l)
{
    node_t *c = l, *t;
    printf("%s\n", __FUNCTION__);
    while (c && c->next) {
        t = c->next;
        c->next = c->next->next;
        free(t);
        c = c->next;
    }
    return;
}


void ll_alt_split_list(node_t *l, node_t **l1, node_t **l2)
{
    node_t *c = l, *n1 = NULL, *n2 = NULL;
    int alt = 1;
    printf("%s\n", __FUNCTION__);
    *l1 = *l2 = NULL;
    while (c) {
        if (alt) {
            if (!n1) {
                *l1 = c;
            } else {
                n1->next = c;
            }
            n1 = c;
            c = c->next;
            n1->next = NULL;
        } else {
            if (!n2) {
                *l2 = c;
            } else {
                n2->next = c;
            }
            n2 = c;
            c = c->next;
            n2->next = NULL;
        }
        alt = !alt;
    }
    return;
}



node_t* ll_reverse_size_k(node_t *l , int k)
{
    node_t *c = l, *p = NULL, *t, *kh = NULL, *pkh, *nl = NULL;
    int s = k;
    printf("%s\n", __FUNCTION__);
    if (s <= 0) {
        return l;
    }

    while (c) {
        if (s) {
            if (s == k) {
                pkh = kh;
                kh = c;
            }
            t = c->next;
            c->next = p;
            p = c;
            c = t;
            s--;
        }

        if (!s || !c) {
            kh->next = c;
            if (pkh) {
                pkh->next = p;
            }
            s = k;
            if (!nl) {
                nl = p;
            }
        }
    }

    return nl;
}

node_t* ll_rec_rev_k(node_t *head, int c)
{
    node_t *curr = head, *prev = NULL, *temp;
    int k = 0;

    printf("%s\n", __FUNCTION__);
    while (curr && (k < c)) {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
        k++;
    }

    if (head) {
        head->next = ll_rec_rev_k(curr, c);
    }

    return prev;
}

node_t* ll_segregate_even_odd(node_t* head)
{
    node_t *c = head, *p = NULL, *eh = NULL, *ec, *oh = NULL;
    printf("%s\n", __FUNCTION__);
    while (c) {
        if ((c->data % 2) == 0) {
            if (!eh) {
                eh = ec = c;
            } else {
                ec->next = c;
                ec = c;
            }
            if (p) {
                p->next = c->next;
            }

            if (oh) {
                ec->next = oh;
            }
            c = c->next;
        } else {
            if (!oh) {
                oh = c;
            }
            p = c;
            c = c->next;
        }
    }

    return (eh ? eh : head);
}

void ll_remove_loop_floyd(node_t *loop_node, node_t* head)
{
    int k = 1;
    node_t *curr = loop_node, *prev = NULL;
    printf("%s\n", __FUNCTION__);

    /*Count number of nodes.*/
    curr = curr ? curr->next : NULL;
    while (curr) {
        if (curr == loop_node) {
            break;
        }
        curr = curr->next;
        k++;
    }

    curr = head;
    while (k > 0) {
        prev = curr;
        curr = curr->next;
        k--;
    }

    loop_node = curr;
    curr = head;
    while (curr != loop_node) {
        curr = curr->next;
        prev = loop_node;
        loop_node = loop_node->next;
    }

    prev->next = NULL;
    return;
}

int ll_detect_and_remove_loop(node_t *head)
{
    node_t *slow = head, *fast = head;
    printf("%s\n", __FUNCTION__);
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }
    if (fast && fast->next) {
        /*remove loop*/
        ll_remove_loop_floyd(fast, head);
    }
    return 0;
}

node_t* ll_create_node(int val)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    printf("%s\n", __FUNCTION__);
    new_node->data = val;
    new_node->next = NULL;
    return new_node;
}

node_t* ll_add_lists(node_t *l1, node_t* l2) {
    node_t *nnode, *head, *curr = NULL;
    int carry = 0;
    printf("%s\n", __FUNCTION__);
    while (l1 || l2 || carry) {
        nnode = ll_create_node(0);
        if (l1 && l2) {
            nnode->data = (l1->data + l2->data + carry);
            carry = nnode->data / 10;
            nnode->data = nnode->data % 10;
            l1 = l1->next;
            l2 = l2->next;
        } else if (l1 || l2) {
            nnode->data = (l1 ? l1->data : l2->data) + carry;
            carry = nnode->data / 10;
            nnode->data = nnode->data % 10;
            if (l1) {
                l1 = l1->next;
            } else {
                l2 = l2->next;
            }
        } else {
            nnode->data = carry;
            break;
        }

        if (curr) {
            curr->next = nnode;
            curr = nnode;
        } else {
            head = curr = nnode;
        }
    }
    return head;
}

void ll_delete_node_seemless(node_t *l , node_t* del_node)
{
    node_t *prev = NULL;

    printf("%s\n",__FUNCTION__);
    while( l ) {
        if (l == del_node) {
            break;
        }
        prev = l;
        l = l->next;
    }

    if (l) {
        while (l && l->next) {
            l->data = l->next->data;
            prev = l;
            l = l->next;
        }

        if (l) {
            if (prev) {
                prev->next = NULL;
            }
            free(l);
        }
    }
    return;
}


/***************** Merge Sort of linked lists************************/
/* Merge two sorted lists and return then new sorted list.
 * Consumes the input lists.
 * */
node_t* ll_merge_sorted_list(node_t* list1, node_t* list2)
{
    node_t *curr1 = list1, *curr2 = list2,*new_list = NULL;
    node_t *new_curr = NULL;

    //printf("%s: START\n", __FUNCTION__);

    while (curr1 && curr2) {
        if (curr1->data <= curr2->data) {
            if(!new_list) {
                new_list = new_curr = curr1;
            } else {
                new_curr->next = curr1;
                new_curr = curr1;
            }
            curr1 = curr1->next;
        } else {
            if(!new_list) {
                new_list = new_curr = curr2;
            } else {
                new_curr->next = curr2;
                new_curr = curr2;
            }
            curr2 = curr2->next;
        }
    }

    if (curr1) {
        if(!new_list) {
            new_list = new_curr = curr1;
        } else {
            new_curr->next = curr1;
            new_curr = curr1;
        }
    }

    if (curr2) {
        if(!new_list) {
            new_list = new_curr = curr2;
        } else {
            new_curr->next = curr2;
            new_curr = curr2;
        }
    }

    return new_list;
}

node_t* ll_split_list(node_t *l)
{
    node_t *slow = l, *fast = l, *prev;

    //printf("%s: START\n", __FUNCTION__);
    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    if (prev) {
        prev->next = NULL;
    }

    return slow;
}

node_t *ll_merge_sort(node_t *l)
{
    node_t *l1 = l, *l2;

    //printf("%s: START\n", __FUNCTION__);

    if (!l || !l->next){
        return l;
    }


    l2 = ll_split_list(l);
    l1 = ll_merge_sort(l1);
    l2 = ll_merge_sort(l2);

    return ll_merge_sorted_list(l1, l2);
}

/*************Union and intersection of two lists*****************/
node_t* ll_clone_node(node_t *in_node, int clone_val, int clone_next)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    new_node->data = clone_val ? in_node->data : 0;
    new_node->next = clone_next ? in_node->next : NULL;
    return new_node;
}

node_t* ll_get_union(node_t *l1, node_t *l2)
{
    node_t *head = NULL, *curr = NULL;

    l1 = ll_merge_sort(l1);
    l2 = ll_merge_sort(l2);

    ll_print(l1);
    ll_print(l2);

    while ( l1 && l2) {
        if (l1->data == l2->data) {
            if (head) {
                curr->next = ll_clone_node(l1 , 1, 0);
                curr = curr->next;
            } else {
                head = curr = ll_clone_node(l1, 1, 0);
            }
            l1 = l1->next;
        } else if (l1->data < l2->data){
            l1 = l1->next;
        } else {
            l2 = l2->next;
        }
    }

    return head;
}



node_t* ll_get_intersection(node_t *l1, node_t *l2)
{
    node_t *head = NULL, *curr = NULL;

    l1 = ll_merge_sort(l1);
    l2 = ll_merge_sort(l2);

    ll_print(l1);
    ll_print(l2);

    while ( l1 && l2) {
        if ((l1->data == l2->data) || (l1->data < l2->data)) {
            if (head) {
                curr->next = ll_clone_node(l1, 1, 0);
                curr = curr->next;
            } else {
                curr = head = ll_clone_node(l1, 1, 0);
            }

            if (l1->data == l2->data) {
                l2 = l2->next;
            }
            l1 = l1->next;
        } else {
            if (head) {
                curr->next = ll_clone_node(l2, 1, 0);
                curr = curr->next;
            } else {
                curr = head = ll_clone_node(l2, 1, 0);
            }
            l2 = l2->next;
        }
    }


    if (l1) {
        while (l1) {
            if (l1->data != curr->data) {
                if (head) {
                    curr->next = ll_clone_node(l1, 1, 0);
                    curr = curr->next;
                } else {
                    head = curr = ll_clone_node(l1, 1, 0);
                }
            }
            l1 = l1->next;
        }
    } else {
        while (l2) {
            if (l2->data != curr->data) {
                if (head) {
                    curr->next = ll_clone_node(l2, 1, 0);
                    curr = curr->next;
                } else {
                    head = curr = ll_clone_node(l2, 1, 0);
                }
            }
            l2 = l2->next;
        }
    }

    return head;
}
/*********Add 2 lists without modifying the original lists********/
void ll_swap_ptr(void **p1, void **p2)
{
    void *temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    return;
}

node_t* ll_add_same_size_lists(node_t *l1, node_t *l2, int *carry)
{
    node_t *result = NULL;
    if (l1 && l2) {
        result = ll_create_node(0);
        result->next = ll_add_same_size_lists(l1->next, l2->next, carry);
        result->data = (l1->data + l2->data + *carry) % 10;
        *carry = (l1->data + l2->data + *carry) / 10;
        return result;
    }
    return NULL;
}


void ll_add_carry_to_remaining_list(node_t* l, node_t *stop_node, node_t** result, int *carry)
{
    node_t *result_node;
    if (l && (l != stop_node)) {
        result_node = ll_create_node(0);
        ll_add_carry_to_remaining_list(l->next, stop_node, result, carry);
        result_node->data = (l->data + *carry) % 10;
        *carry = (l->data + *carry) / 10;
        result_node->next = *result;
        *result = result_node;
    }
    return;
}

/*Lists are MSB to LSB and we cannot modify the original list.*/
node_t* ll_add_lists_MSBfirst(node_t *l1, node_t *l2)
{
    int c1, c2, diff, carry = 0;
    node_t *result, *curr;

    c1 = ll_get_count(l1);
    c2 = ll_get_count(l2);

    if (!c1 && !c2) {
        return NULL;
    }

    if (c1 == c2) {
        result = ll_add_same_size_lists(l1, l2, &carry);
    } else {
        if (c2 > c1) {
            diff = c2 - c1;
            ll_swap_ptr((void**)&l1, (void**)&l2);
        } else {
            diff = c1 - c2;
        }
        curr = l1;
        while (diff) {
            curr = curr->next;
            diff--;
        }

        result = ll_add_same_size_lists(curr, l2, &carry);
        ll_add_carry_to_remaining_list(l1, curr, &result, &carry);
    }

    if (carry) {
        node_t *nn = ll_create_node(carry);
        nn->next = result;
        result = nn;
    }


    return result;
}


/***********************Quick sort singly linked list***********************************/
node_t* ll_get_tail(node_t *l)
{
    while (l && l->next) {
        l = l->next;
    }
    return l;
}

node_t* ll_partition_for_quick_sort(node_t* hd, node_t* tl, node_t **nh, node_t **ntl)
{
    node_t *pivot = tl, *prev = NULL, *tmp;
    *nh = NULL;
    *ntl = tl;

    while (hd != pivot) {
        if (hd->data < pivot->data) {
            if (!*nh) {
                *nh = hd;
            }
            hd = hd->next;
        } else {
            if (prev) {
                prev->next = hd->next;
            }
            tl->next = hd;
            tl = hd;
            tmp = hd->next;
            hd->next = NULL;
            hd = tmp;
        }
    }

    /*If pivot is the smallest*/
    if (!*nh) {
        *nh = pivot;
    }
    *ntl = tl;
    return pivot;
}

node_t* ll_qsort_rec(node_t *hd, node_t *tl)
{
    node_t *pivot, *nh, *ntl, *curr;

    if (!hd || (hd == tl)) {
        return hd;
    }

    pivot = ll_partition_for_quick_sort(hd, tl, &nh, &ntl);

    if (nh != pivot) {
        curr = nh;
        while (curr->next != pivot){
            curr = curr->next;
        }

        curr->next = NULL;
        nh = ll_qsort_rec(nh, curr);
        curr = ll_get_tail(nh);
        curr->next = pivot;
    }
    pivot->next = ll_qsort_rec(pivot->next, ntl);

    return nh;
}

node_t *ll_qsort(node_t *l)
{
    return ll_qsort_rec(l, ll_get_tail(l));
}

/****************Alternate merge*************************/

node_t* ll_alternate_merge(node_t *l1, node_t* l2)
{
	node_t *curr = l1, *tmp;

	if (!l1 || !l2) {
		return l2;
	}

	while (curr) {
		if (l2) {
			tmp = l2->next;
			l2->next = curr->next;
			curr->next = l2;

			curr = l2->next;
			l2 = tmp;
			continue;
		}
		break;
	}

	return l2;
}











