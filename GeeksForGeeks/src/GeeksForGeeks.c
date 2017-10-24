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
#include "BinaryTree.h"
#include "Queue.h"
#include "Graph.h"

void test_ll(void)
{
    node_t *head;

    ll_create(&head, 10, 0);
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

void test_list_clone_with_rnd_ptrs(void)
{
    int n = 5;
    int arr[5] = {1,5,4,2,3};
    node_t *l, *nl;

    if (ll_create(&l, n, arr) == LL_FALSE) {
        printf("%s: list 1 create failure!!!\n", __FUNCTION__);
        return;
    }
#if 1
    l->rnd = l->next->next;
    l->next->rnd = l;
    l->next->next->rnd = l->next->next->next->next;
    l->next->next->next->rnd = l->next->next;
    l->next->next->next->next->rnd = l->next;
    ll_print_rnd(l);

    nl = ll_clone_list_with_rnd_links(l);
    ll_print_rnd(nl);
    ll_print_rnd(l);
    ll_free(&nl);


    ll_update_rnd_to_highest_on_right(l);
    ll_print_rnd(l);
#else
    ll_print(l);
    nl = ll_co_locate_even_odd(l);
    ll_print(nl);
    ll_free(&nl);
#endif

    ll_free(&l);
}

void test_ll_all(void)
{
    //test_ll();
    //test_ll_mergesort();
    //test_ll_sorted_merge();
    //test_vector();
    //test_ll_merge_sort();
    //test_ll_sorted_insert();
    //test_middle();
    //test_ll_palindrome();
    //test_ll_intersection();
    //test_generic();
    //test_alt_split_list();
    //test_reverse_kll();
    //test_merge_sort_lists();
    //test_union_intersection();
    //test_add_2_lists();
    //test_qsort();
    //test_list_clone_with_rnd_ptrs();
}

void test_q_basic(void)
{
    q_t* q;
    int arr[10] = {1,2,3,4,5,6,7,8,9,10}, i;
    q = q_create();

    for (i = 0; i < 10; i++) {
        en_q(q, &arr[i], 0);
    }

    for(;!is_q_empty(q);) {
        int *val;
        de_q(q, (void**)&val, NULL);
        if (val) {
            printf("%d\n", *val);
        } else {
            printf("ERROR\n");
            break;
        }
    }
    q_destroy(q);
    return;
}
void test_q_all(void)
{
    test_q_basic();
}

void test_bt_print(void)
{
    bt_node_t *root = NULL;
    int arr[6] = {5,3,6,1,4,2};
    int i;

    for (i = 0; i < 6; i++) {
        bt_insert(&root, arr[i]);
    }

    //bt_print_level(root);
    //bt_print_inorder_no_rec_st(root);
    //bt_print_inorder_morris_traversal(root);
    //bt_print_preorder_iterative(root);
    //bt_print_preorder_morris(root);
    //printf(" Size of Tree: %d\n", bt_get_size(root));
//TODO: Need to debug this
    bt_print_post_order_iterative(root);
    bt_destroy(&root);
    return;
}

void test_identical_bt(void)
{
    bt_node_t *root = NULL, *root1 = NULL;
    int arr[6] = {5,3,6,1,4,2};
    int i;

    for (i = 0; i < 6; i++) {
        bt_insert(&root, arr[i]);
    }

    for (i = 0; i < 6; i++) {
        bt_insert(&root1, arr[i]);
    }


    i = is_bts_identical(root, root);
    printf("The trees are %s \n", i ? "identical" : "non-identical");


    i = is_bts_identical(root, root1);
    printf("The trees are %s \n", i ? "identical" : "non-identical");

    bt_insert(&root1, 7);
    i = is_bts_identical(root, root1);
    printf("The trees are %s \n", i ? "identical" : "non-identical");

    bt_insert(&root1, 8);
    bt_insert(&root1, 9);
    bt_insert(&root1, 10);

    printf("r1 hgt: %d and r2 hgt: %d\n", bt_get_height(root), bt_get_height(root1));
    bt_destroy(&root);
    bt_destroy(&root1);
    return;
}

void test_bt_to_List(void)
{
    bt_node_t *root = NULL, *sentinel;
    int arr[6] = {5,3,6,1,4,2};
    int i;

    for (i = 0; i < 6; i++) {
        bt_insert(&root, arr[i]);
    }

    bt_print_level(root);

    printf("\n");
    sentinel = root = btToList(root);
    while (sentinel) {
        bt_node_t *temp = sentinel;
        printf("%d \n", sentinel->val);
        sentinel = sentinel->right;
        free(temp);
        if (sentinel == root) {
            break;
        }
    }

    return;
}


void test_bt_constructTree(void)
{
    int in[10] = {1,2,3,4,5,6};
    int pre[10] = {4,2,1,3,6,5};
    int po[10] = {1,3,2,5,6,4};

    int idx = 0;
    bt_node_t *root;

    root = buildTreeInAndPre(in, pre, 0, 5, &idx);
    if (root) {
        printf("Building tree with inorder and preorder arr done\n");
        bt_print_inorder_morris_traversal(root);
    } else {
        printf("Returned NULL\n");
        return;
    }

    bt_destroy(&root);
    printf("----------------------------------------------\n");
    idx = 5;
    root = buildTreeInAndPost(in, po, 0, 5, &idx);
    if (root) {
        printf("Building tree with inorder and postorder arr done\n");
        bt_print_inorder_morris_traversal(root);
    } else {
        printf("Returned NULL\n");
        return;
    }

    bt_destroy(&root);

    return;
}


void test_bt_diameter(void)
{
    bt_node_t *root = NULL;
    int arr[10] = {6, 1, 2, 3, 4, 5, -1, -2, 7, 8};
    int i, dia = 0;

    for (i = 0; i < 10; i++) {
        bt_insert(&root, arr[i]);
    }

    bt_print_level(root);

    getDiameterOfTree(root, &dia);
    printf("Diameter: %d\n", dia);
    bt_destroy(&root);
}

void test_bt_subtree(void)
{
    bt_node_t *t1 = NULL, *t2 = NULL;
    int arr[10] = {5,2,1,3,7,6,8};
    int arr1[3] = {7,6,8};
    int i;

    for (i = 0; i < 7; i++) {
        bt_insert(&t1, arr[i]);
    }

    bt_print_level(t1);

    for (i = 0; i < 3; i++) {
        bt_insert(&t2, arr1[i]);
    }

    bt_print_level(t2);

    printf("t2 %s a subtree of t1\n", isSubTree(t1, t2) ? "is" : "is not");

    printf("Height of t2 is %d\n", bt_get_height(t2));

    bt_destroy(&t1);
    bt_destroy(&t2);
}

void testConnectLevels(void)
{
    bt_node_t *t1 = NULL;
    int arr[10] = {5,2,1,3,7,6,8};
    int i;

    for (i = 0; i < 7; i++) {
        bt_insert(&t1, arr[i]);
    }

    connectLevelNodesFaster(t1);
    connectLevelNodes(t1);
    bt_destroy(&t1);
}

void testMaxSumPath(void)
{
    bt_node_t *t1 = NULL;
    int arr[10] = {5,2,1,3,7,6,4};
    int i;

    for (i = 0; i < 7; i++) {
        bt_insert(&t1, arr[i]);
    }
    bt_get_max_sum_path(t1);
    bt_destroy(&t1);
}

void test_bt_specialTreeConstruct(void)
{
    bt_node_t *t1 = NULL;

    //int arr[10] = {1,5,10,40,30,15,28,20};
    //t1 = buildSpecialTreeIn(arr, 0, 7);

    char arrT[10] = {'N','N','L','L','N','L','L'};
    int arr[10] = {10,30,20,5,15,22,36}, i = 0;

    t1 = buildSpecialTree1(arr, arrT, &i, 7);

    bt_print_level(t1);
    bt_destroy(&t1);

}

void test_completeTree(void)
{
    bt_node_t *t1 = NULL;
    int arr[10] = {5,6}, i = 0;

    for (i = 0; i < 2; i++) {
        bt_insert(&t1, arr[i]);
    }

    bt_print_level(t1);

    printf("Tree is %s\n", isCompleteTree(t1) ? "complete": "incomplete");

    bt_destroy(&t1);

}

void test_printBoundary(void)
{
    bt_node_t *t1 = NULL;
    int arr[10] = {8,4,2,6,5,7,9,10}, i = 0;

    for (i = 0; i < 8; i++) {
        bt_insert(&t1, arr[i]);
    }

    bt_print_level(t1);
    bt_print_bndry_nodes(t1);
    bt_destroy(&t1);
}

void test_liss(void)
{
    bt_node_t *t1 = NULL;
    int arr[10] = {70,80,90,20,10,50,30,60}, i = 0;

    for (i = 0; i < 8; i++) {
        bt_insert(&t1, arr[i]);
    }

    bt_print_level(t1);

    printf("LISS = %d \n", LISS(t1));

    bt_destroy(&t1);

}


void test_bt_all(void)
{
    test_bt_print();
    //test_identical_bt();
    //test_bt_to_List();
    //test_bt_constructTree();
    //test_bt_diameter();
    //test_bt_subtree();
    //testConnectLevels();
    //testMaxSumPath();
    //test_bt_specialTreeConstruct();
    //test_completeTree();
    //test_printBoundary();
    //test_liss();
}

graph_t *test_create_graph(int v)
{
    graph_t *graph;

    graph = create_graph(v);

    return graph;
}
void test_gr_create_print(void)
{
    graph_t *graph = test_create_graph(5);

    add_edge(graph, 0, 1, NON_DIRECTIONAL, 0);
    add_edge(graph, 0, 4, NON_DIRECTIONAL, 0);
    add_edge(graph, 1, 2, NON_DIRECTIONAL, 0);
    add_edge(graph, 1, 3, NON_DIRECTIONAL, 0);
    add_edge(graph, 1, 4, NON_DIRECTIONAL, 0);
    add_edge(graph, 2, 3, NON_DIRECTIONAL, 0);
    add_edge(graph, 3, 4, NON_DIRECTIONAL, 0);

    print_graph(graph);
    destroy_graph(graph);
}

void test_gr_bfs(void)
{
    graph_t *graph = test_create_graph(4);

    add_edge(graph, 0, 1, DIRECTIONAL, 0);
    add_edge(graph, 0, 2, DIRECTIONAL, 0);
    add_edge(graph, 1, 2, DIRECTIONAL, 0);
    add_edge(graph, 2, 0, DIRECTIONAL, 0);
    add_edge(graph, 2, 3, DIRECTIONAL, 0);
    add_edge(graph, 3, 3, DIRECTIONAL, 0);

    print_graph(graph);

    bfs_traversal_graph(graph, 2);
    destroy_graph(graph);

}

void test_gr_dfs(void)
{
    graph_t *graph = test_create_graph(4);

    add_edge(graph, 0, 1, DIRECTIONAL, 0);
    add_edge(graph, 0, 2, DIRECTIONAL, 0);
    add_edge(graph, 1, 2, DIRECTIONAL, 0);
    add_edge(graph, 2, 0, DIRECTIONAL, 0);
    add_edge(graph, 2, 3, DIRECTIONAL, 0);
    add_edge(graph, 3, 3, DIRECTIONAL, 0);

    print_graph(graph);

    dfs_traversal_graph(graph, 2);
    destroy_graph(graph);
}

void test_topological_sort(void)
{
    graph_t *graph = test_create_graph(6);

    add_edge(graph, 5, 2, DIRECTIONAL, 0);
    add_edge(graph, 5, 0, DIRECTIONAL, 0);
    add_edge(graph, 4, 0, DIRECTIONAL, 0);
    add_edge(graph, 4, 1, DIRECTIONAL, 0);
    add_edge(graph, 2, 3, DIRECTIONAL, 0);
    add_edge(graph, 3, 1, DIRECTIONAL, 0);

    print_graph(graph);

    topological_sort_graph(graph);
    destroy_graph(graph);
}

void test_longest_path_acyclic_directed_graph(void)
{
    graph_t *graph = test_create_graph(6);

    add_edge(graph, 0, 1, DIRECTIONAL, 5);
    add_edge(graph, 0, 2, DIRECTIONAL, 3);
    add_edge(graph, 1, 3, DIRECTIONAL, 6);
    add_edge(graph, 1, 2, DIRECTIONAL, 2);
    add_edge(graph, 2, 4, DIRECTIONAL, 4);
    add_edge(graph, 2, 5, DIRECTIONAL, 2);
    add_edge(graph, 2, 3, DIRECTIONAL, 7);
    add_edge(graph, 3, 5, DIRECTIONAL, 1);
    add_edge(graph, 3, 4, DIRECTIONAL, -1);
    add_edge(graph, 4, 5, DIRECTIONAL, -2);

    print_graph(graph);

    lonest_path_directed_acyclic_graph(graph, 1);
    destroy_graph(graph);
}

void test_mother_vertex(void)
{
	int v;
    graph_t *graph = test_create_graph(7);

    add_edge(graph, 0, 1, DIRECTIONAL, 0);
    add_edge(graph, 0, 2, DIRECTIONAL, 0);
    add_edge(graph, 1, 3, DIRECTIONAL, 0);
    add_edge(graph, 4, 1, DIRECTIONAL, 0);
    add_edge(graph, 6, 4, DIRECTIONAL, 0);
    add_edge(graph, 5, 6, DIRECTIONAL, 0);
    add_edge(graph, 5, 2, DIRECTIONAL, 0);
    add_edge(graph, 6, 0, DIRECTIONAL, 0);

    print_graph(graph);

    find_mother_vertex_in_graph(graph, &v);
    destroy_graph(graph);
}

void test_graph_all(void)
{
    //test_gr_create_print();
    //test_gr_bfs();
    //test_gr_dfs();
    //test_topological_sort();
    //test_longest_path_acyclic_directed_graph();
	test_mother_vertex();
}

/*Main program to test all the problems.*/
int main(void) {
    //test_ll_all();
    //test_q_all();
    //test_bt_all();
    test_graph_all();
    printf("\nALL TESTS COMPLETE!!!\n");
    return EXIT_SUCCESS;
}
