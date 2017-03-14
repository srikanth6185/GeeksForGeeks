#include<stdio.h>
#include<stdlib.h>
#include"BinaryTree.h"
#include"Queue.h"
#include"Stack.h"

void bt_insert(bt_node_t **root, int val)
{
    if (*root) {
        bt_node_t *curr = *root;
        while(curr) {
            if (val <= curr->val) {
                if (curr->left) {
                    curr = curr->left;
                } else {
                    curr->left = (bt_node_t*)calloc(sizeof(char), sizeof(bt_node_t));
                    curr->left->val = val;
                    break;
                }
            } else {
                if (val > curr->val) {
                    if (curr->right) {
                        curr = curr->right;
                    } else {
                        curr->right = (bt_node_t*)calloc(sizeof(char), sizeof(bt_node_t));
                        curr->right->val = val;
                        break;
                    }
                }
            }
        }
    } else {
        *root = (bt_node_t*)calloc(sizeof(char), sizeof(bt_node_t));
        (*root)->val = val;
    }
    return;
}


static void _bt_destroy(bt_node_t *root)
{
    if (root) {
        if (root->left) {
            _bt_destroy(root->left);
        }
        if (root->right) {
            _bt_destroy(root->right);
        }
        free(root);
    } else {
        return;
    }
}

void bt_destroy(bt_node_t **root)
{
    _bt_destroy(*root);
    *root = NULL;
    return;
}

void bt_print_level(bt_node_t *root)
{
    q_t *q;
    bt_node_t *curr;

    if (!root) {
        printf("Null Tree\n");
    }
    q = q_create();
    en_q(q, root);

    while(!is_q_empty(q)) {
        de_q(q, (void**)&curr);
        if (curr->left) {
            en_q(q, curr->left);
        }
        if (curr->right) {
            en_q(q, curr->right);
        }
        printf("%d ", curr->val);
    }
    q_destroy(q);
    return;
}

void bt_print_inorder_no_rec_st(bt_node_t *root)
{
    st_t *st;
    bt_node_t *curr;

    if (!root) {
        printf("NULL Tree\n");
        return;
    }

    st = st_create(VOID_DATA);
    curr = root;
    while (curr) {
        st_push(st, 0, curr);
        curr = curr->left;
    }

    while (!is_st_empty(st)) {
        st_pop(st, NULL, (void**)&curr);
        printf("%d ", curr->val);
        if (curr->right) {
            curr = curr->right;
            while (curr) {
                st_push(st, 0, curr);
                curr = curr->left;
            }
        }
    }
    st_destroy(st);
    return;
}


void bt_print_inorder_morris_traversal(bt_node_t* root)
{
    bt_node_t *curr, *pre;

    if (!root) {
        printf("Null Tree\n");
        return;
    }

    curr = root;
    while (curr) {
        if (curr->left == NULL) {
            printf("%d ", curr->val);
            curr = curr->right;
        } else {
            pre = curr->left;
            /*Find the in order predecessor for curr.*/
            while ((pre->right != NULL)  && (pre->right != curr)) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
                /*We are reaching this predecessor for the first time
                 *hence setup the link(thread) to the successor which is curr.*/
                pre->right = curr;
                curr = curr->left;
            } else {
                /*We reached back to the successor from the predecessor,
                 *hence reset the link(thread) to the successor and print the
                 *predecessor.*/
                printf("%d ", curr->val);
                pre->right = NULL;
                curr = curr->right;
            }
        }
    }
    return;
}

int bt_get_size(bt_node_t *root)
{
    if (!root) {
        return 0;
    } else {
        return (bt_get_size(root->left) + 1 + bt_get_size(root->right));
    }
}













