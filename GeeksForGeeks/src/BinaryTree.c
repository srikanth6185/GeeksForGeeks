#include<stdio.h>
#include<stdlib.h>
#include"BinaryTree.h"
#include"Queue.h"

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


















