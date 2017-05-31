#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include <limits.h>

typedef struct bt_node_s {
    int val;
    struct bt_node_s *right;
    struct bt_node_s *left;
    struct bt_node_s *nextRight;
} bt_node_t;



void bt_insert(bt_node_t **root, int val);
void bt_destroy(bt_node_t **root);
void bt_print_level(bt_node_t *root);
void bt_print_inorder_no_rec_st(bt_node_t *root);
void bt_print_inorder_morris_traversal(bt_node_t* root);
void bt_print_preorder_iterative(bt_node_t *root);
void bt_print_preorder_morris(bt_node_t *root);

int bt_get_size(bt_node_t *root);
int is_bts_identical(bt_node_t *rA, bt_node_t *rB);
int bt_get_height(bt_node_t* root);
bt_node_t* btToList(bt_node_t *root);
bt_node_t* buildTreeInAndPre(int *in, int *pre, int start, int end, int *preIdx);
bt_node_t* buildTreeInAndPost(int *in, int *pre, int start, int end, int *poIdx);

int getDiameterOfTree(bt_node_t *root, int* max);
int isSubTree(bt_node_t *t1, bt_node_t* t2);
int isIdenticalTree(bt_node_t *t1, bt_node_t* t2);
void connectLevelNodes(bt_node_t* root);
void connectLevelNodesFaster(bt_node_t* root);


void bt_get_max_sum_path(bt_node_t *root);
bt_node_t* buildSpecialTreeIn(int *in, int start, int end);
bt_node_t* buildSpecialTree1(int *node, char *nodeT, int *idx, int max);
int isCompleteTree(bt_node_t* root);
void bt_print_bndry_nodes(bt_node_t *root);


#endif  //_BINARY_TREE_H_
