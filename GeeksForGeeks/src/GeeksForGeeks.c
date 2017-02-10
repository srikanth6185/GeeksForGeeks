/*
 ============================================================================
 Name        : GeeksForGeeks.c
 Author      : Srikanth
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "vector_util.h"

void test_ll(void)
{
    node_t *head;

    ll_create(&head, 10, NULL);
    ll_print(head);

    ll_delete_nth_node(&head, 1);
    ll_print(head);

    ll_delete_val_node(&head, 2, 1);
    ll_print(head);

    ll_add_node(&head, 5);
    ll_print(head);

    ll_add_node(&head, 6);
    ll_print(head);

    ll_add_node(&head, 7);
    ll_print(head);

    ll_add_node(&head, 8);
    ll_print(head);

    ll_add_node(&head, 9);
    ll_print(head);

    printf("Recursive count: %d Linear count: %d \n",ll_get_count_rec(head), ll_get_count(head));


    ll_find_node(head, 5);
    ll_find_node(head, 1);
    ll_find_node(head, 8);

    ll_swap_nodes(&head, 5, 9);
    ll_print(head);

    ll_find_nth_node(head, 5);

    ll_find_nth_from_last_node(head, 3);

    ll_free(&head);
    return;
}


void test_ll_sorted_insert(void)
{
    int n1 = 5;
    int arr1[5] = {5,7,10,25,33};
    node_t* head1;

    if (ll_create(&head1, n1, arr1) == LL_FALSE) {
        printf("%s: list 1 create failure!!!\n", __FUNCTION__);
        return;
    }

    ll_print(head1);
    head1 = ll_sorted_insert_value(head1, 4);

    ll_print(head1);
    head1 = ll_sorted_insert_value(head1, 34);

    ll_print(head1);
    head1 = ll_sorted_insert_value(head1, 16);


    ll_print(head1);
    head1 = ll_sorted_insert_value(head1, 9);
    ll_print(head1);

    ll_free(&head1);
    return;
}

void test_ll_mergesort(void)
{
    int n1 = 5, n2 = 5;
    int arr1[5] = {9,7,1,3,5};
    int arr2[5] = {2,4,6,8,10};
    node_t* head1 , *head2;

    if (ll_create(&head1, n1, arr1) == LL_FALSE) {
        printf("%s: list 1 create failure!!!\n", __FUNCTION__);
        return;
    }

    if (ll_create(&head2, n2, arr2) == LL_FALSE) {
        printf("%s: list 2 create failure!!!\n", __FUNCTION__);
        ll_free(&head1);
        return;
    }

    ll_print(head1);
    ll_print(head2);

    head1 = ll_merge(head1, head2);

    ll_print(head1);

    head1 = ll_reverse(head1);

    ll_print(head1);

    ll_free(&head1);
    return;
}
void test_ll_sorted_merge(void)
{
    int n1 = 5, n2 = 5;
    int arr1[5] = {1,3,5,7,9};
    int arr2[5] = {2,4,6,8,10};
    node_t* head1 , *head2;
    printf("%s: START\n", __FUNCTION__);
    if (ll_create(&head1, n1, arr1) == LL_FALSE) {
        printf("%s: list 1 create failure!!!\n", __FUNCTION__);
        return;
    }

    if (ll_create(&head2, n2, arr2) == LL_FALSE) {
        printf("%s: list 2 create failure!!!\n", __FUNCTION__);
        ll_free(&head1);
        return;
    }

    ll_print(head1);
    ll_print(head2);

    head1 = ll_merge_sorted_list(head2, head1);

    ll_print(head1);
    ll_free(&head1);

    return;
}

void test_vector()
{
    printf("%s: START\n", __FUNCTION__);
    test_vector_dispatch();
    return;
}

void test_middle(void)
{
    int n1 = 5, n2 = 6 , even = 0;
    int arr1[5] = {5,7,10,25,33};
    int arr2[6] = {5,7,10,25,33,44};
    node_t *head1, *head2, *middle;

    if (ll_create(&head1, n1, arr1) == LL_FALSE) {
        printf("%s: list 1 create failure!!!\n", __FUNCTION__);
        return;
    }

    if (ll_create(&head2, n2, arr2) == LL_FALSE) {
        printf("%s: list 2 create failure!!!\n", __FUNCTION__);
        return;
    }

    middle = ll_get_middle_node(NULL, &even);
    printf("%s: Middle of NULL list is %p : %d even: %d\n", __FUNCTION__, middle, middle ? middle->data : 111111, even);

    middle = ll_get_middle_node(head1, &even);
    printf("%s: Middle of list 1 is %p : %d even: %d \n", __FUNCTION__, middle, middle ? middle->data : 111111, even);

    middle = ll_get_middle_node(head2, &even);
    printf("%s: Middle of list 2 is %p : %d even: %d\n", __FUNCTION__, middle, middle ? middle->data : 111111, even);

    ll_free(&head1);
    ll_free(&head2);
}

void test_ll_palindrome(void)
{
    int n = 5, arr[5] = {5,7,10,25,33};
    //int n = 5, arr[5] = {5,7,10,7,5};
    //int n = 6, arr[6] = {5,7,10,25,33,66};
    //int n = 6, arr[6] = {5,7,10,10,7,5};

    node_t* head;

    if (ll_create(&head, n, arr) == LL_FALSE) {
        printf("%s: list create failure!!!\n", __FUNCTION__);
        return;
    }

    printf("result : %d\n", ll_is_palidrome(head));
    ll_print(head);
    ll_free(&head);
}

void test_ll_intersection(void)
{
    int n1 = 5, n2 = 6;
    int arr1[5] = {1,2,3,4,5};
    int arr2[6] = {11,22,33,44,55,66};
    node_t *list1, *list2;

    if (ll_create(&list1, n1, arr1) == LL_FALSE) {
        printf("%s: list 1 create failure!!!\n", __FUNCTION__);
        return;
    }

    if (ll_create(&list2, n2, arr2) == LL_FALSE) {
        printf("%s: list 2 create failure!!!\n", __FUNCTION__);
        return;
    }


    ll_print(list1);
    ll_print(list2);
    ll_get_intersect_node(list1, list2);


    list1->next->next->next->next->next = list2;
    ll_print(list1);
    ll_print(list2);
    ll_get_intersect_node(list1, list2);


    list1->next->next->next->next->next = list2->next;
    ll_print(list1);
    ll_print(list2);
    ll_get_intersect_node(list1, list2);

    list1->next->next->next->next->next = list2->next->next->next;
    ll_print(list1);
    ll_print(list2);
    ll_get_intersect_node(list1, list2);


    list1->next->next->next->next->next = list2->next->next->next->next->next;
    ll_print(list1);
    ll_print(list2);
    ll_get_intersect_node(list1, list2);

    list1->next->next->next->next->next = NULL;

    ll_free(&list1);
    ll_free(&list2);
}

void test_generic(void)
{
    int n = 11, arr[11] = {5,5,7,7,10,25,25,25,33,33,44};
    int n1 = 5, arr1[5] = {1,2,3,5,6};
    int n2 = 3, arr2[3] = {0,3,6};
    node_t* head, *l1, *l2/*, *nl*/;

    if (ll_create(&head, n, arr) == LL_FALSE) {
        printf("%s: list create failure!!!\n", __FUNCTION__);
        return;
    }

    //ll_print(head);
    ll_remove_duplicates(head);

    //ll_print(head);
    head = ll_last2front(head);
    //ll_print(head);

    ll_del_alt_nodes(head);
    //ll_print(head);
    ll_free(&head);

    if (ll_create(&l1, n1, arr1) == LL_FALSE) {
        printf("%s: list create failure!!!\n", __FUNCTION__);
        return;
    }
    if (ll_create(&l2, n2, arr2) == LL_FALSE) {
        printf("%s: list create failure!!!\n", __FUNCTION__);
        return;
    }

    l2 = ll_alternate_merge(l1, l2);
    ll_print(l1);
    ll_print(l2);

    /*
    nl = ll_get_intersection_list(l1, l2);
    ll_print(l1);
    ll_print(l2);
    ll_print(nl);
    ll_free(&nl);

    nl = ll_add_lists(l1,l2);
    ll_print(nl);
    ll_free(&nl);

    ll_print(l1);
    ll_delete_node_seemless(l1, l1->next->next->next->next);
    ll_print(l1);
    */
    ll_free(&l1);
    ll_free(&l2);
}

void test_alt_split_list(void)
{
    int n = 11, arr[11] = {1,2,1,2,1,2,1,2,1,2,1};
    node_t *l , *l1, *l2;
    if (ll_create(&l, n, arr) == LL_FALSE) {
        printf("%s: list create failure!!!\n", __FUNCTION__);
        return;
    }

    ll_print(l);
    ll_alt_split_list(l, &l1, &l2);

    ll_print(l1);
    ll_print(l2);

    ll_free(&l1);
    ll_free(&l2);
}

void test_reverse_kll(void)
{
    int n1 = 8;
    int arr1[8] = {1,2,3,4,5,6,7,8};
    node_t *list1, *curr;
    if (ll_create(&list1, n1, arr1) == LL_FALSE) {
        printf("%s: list 1 create failure!!!\n", __FUNCTION__);
        return;
    }

    ll_print(list1);
    //list1 = ll_reverse_size_k(list1, 3);
    list1 = ll_rec_rev_k(list1,3);
    ll_print(list1);

    list1 = ll_segregate_even_odd(list1);
    ll_print(list1);

    curr = list1;
    while (curr->next) {
        curr = curr->next;
    }

    curr->next = list1->next->next;
    printf("%s: list has loop : %d \n", __FUNCTION__, ll_detect_and_remove_loop(list1));
    ll_print(list1);

    ll_free(&list1);
}

void test_merge_sort_lists()
{
    int n1 = 8;
    int arr1[8] = {8,5,6,1,3,2,4,7};
    node_t *list1;

    if (ll_create(&list1, n1, arr1) == LL_FALSE) {
        printf("%s: list 1 create failure!!!\n", __FUNCTION__);
        return;
    }

    ll_print(list1);
    list1 = ll_merge_sort(list1);
    ll_print(list1);

    ll_free(&list1);
    return;
}

void test_union_intersection(void)
{
    int n1 = 5, n2 = 5;
    int arr1[5] = {1,2,3,4,5};
    int arr2[5] = {2,5,6,6,8};
    node_t *l1, *l2, *nl;

    if (ll_create(&l1, n1, arr1) == LL_FALSE) {
        printf("%s: list 1 create failure!!!\n", __FUNCTION__);
        return;
    }

    if (ll_create(&l2, n2, arr2) == LL_FALSE) {
        printf("%s: list 2 create failure!!!\n", __FUNCTION__);
        return;
    }

    nl = ll_get_union(l1, l2);
    ll_print(nl);
    ll_free(&nl);

    nl = ll_get_intersection(l1, l2);
    ll_print(nl);
    ll_free(&nl);


    ll_free(&l1);
    ll_free(&l2);
}

void test_add_2_lists(void)
{
    int n1 = 6, n2 = 5;
    int arr1[6] = {1,2,3,4,5,7};
    int arr2[5] = {2,5,6,6,8};
    node_t *l1, *l2, *nl;

    if (ll_create(&l1, n1, arr1) == LL_FALSE) {
        printf("%s: list 1 create failure!!!\n", __FUNCTION__);
        return;
    }

    if (ll_create(&l2, n2, arr2) == LL_FALSE) {
        printf("%s: list 2 create failure!!!\n", __FUNCTION__);
        return;
    }

    nl = ll_add_lists_MSBfirst(l2, l1);
    ll_print(nl);
    ll_free(&nl);

    ll_free(&l1);
    ll_free(&l2);
}

void test_qsort(void)
{
    int n = 8;
    int arr[8] = {3,4,5,2,6,1,7,8};
    node_t *l;

    if (ll_create(&l, n, arr) == LL_FALSE) {
        printf("%s: list 1 create failure!!!\n", __FUNCTION__);
        return;
    }
    ll_print(l);

    l = ll_qsort(l);
    ll_print(l);

    ll_free(&l);
}


/*Main program to test all the problems.*/
int main(void) {
    //test_ll();
    //test_ll_mergesort();
    //test_ll_sorted_merge();
    //test_vector();
    //test_ll_merge_sort();
    //test_ll_sorted_insert();
    //test_middle();
    //test_ll_palindrome();
    //test_ll_intersection();
    test_generic();
    //test_alt_split_list();
    //test_reverse_kll();
    //test_merge_sort_lists();
    //test_union_intersection();
    //test_add_2_lists();
    //test_qsort();
    printf("ALL TESTS COMPLETE!!!\n");
    return EXIT_SUCCESS;
}
