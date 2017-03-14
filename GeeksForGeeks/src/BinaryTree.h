#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

typedef struct bt_node_s {
    int val;
    struct bt_node_s *right;
    struct bt_node_s *left;
} bt_node_t;




void bt_insert(bt_node_t **root, int val);
void bt_destroy(bt_node_t **root);
void bt_print_level(bt_node_t *root);
void bt_print_inorder_no_rec_st(bt_node_t *root);
void bt_print_inorder_morris_traversal(bt_node_t* root);
int bt_get_size(bt_node_t *root);
#endif  //_BINARY_TREE_H_
