#include<stdio.h>
#include<stdlib.h>
#include"BinaryTree.h"
#include"Queue.h"
#include"Stack.h"

#define MAX(a,b)  ((a >= b) ? a : b)

bt_node_t *bt_get_new_node(int val)
{
    bt_node_t *newNode = (bt_node_t*)calloc(1, sizeof(bt_node_t));
    if (!newNode) {
        printf("Node alloc failed\n");
        return NULL;
    }
    newNode->val = val;
    return newNode;
}

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
    if (!root) {
        return;
    }

    _bt_destroy(root->left);
    _bt_destroy(root->right);
    free(root);

    return;
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
    printf("\n");
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
    printf("\n");
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

int bt_get_height(bt_node_t* root)
{
    if (!root) {
        return 0;
    } else {
        int dLeft = bt_get_height(root->left);
        int dRight = bt_get_height(root->right);

        return (1 + ((dLeft > dRight) ? dLeft : dRight));
    }
}
/*Detect if two given trees are identical*/
int is_bts_identical(bt_node_t *rA, bt_node_t *rB)
{
    if (!rA && !rB) {
        return 1;
    }

    if (rA && rB) {
        return ((rA->val == rB->val) &&
                is_bts_identical(rA->left, rB->left) &&
                is_bts_identical(rA->right, rB->right));
    }
    return 0;
}

bt_node_t* concatenateCL(bt_node_t *l1, bt_node_t *l2)
{
    bt_node_t *l1Last ,*l2Last;

    if (!l1 || !l2) {
        return l1 ? l1:l2;
    }

    l1Last = l1->left;
    l2Last = l2->left;

    /* L1 beginning to
     * L2 end and vice-versa*/
    l1->left = l2Last;
    l2Last->right = l1;


    /* L1 end to
     * L2 beginning and vice-versa.*/
    l1Last->right = l2;
    l2->left = l1Last;

    return l1;
}

bt_node_t* btToList(bt_node_t *root)
{
    bt_node_t *leftList, *rightList;

    if (!root) {
        return NULL;
    }

    if(!root->left && !root->right) {
        root->left = root->right = root;
        return root;
    }

    leftList = btToList(root->left);
    rightList = btToList(root->right);

    root->left = root->right = root;

    return concatenateCL(concatenateCL(leftList, root), rightList);
}

int searchInOrderTable(int *in, int s, int e, int value)
{
    int i;
    if (!in || (s < 0) || (e < 0)) {
        printf("Input wrong\n");
        return -1;
    }
    for(i = s; i <= e; i++) {
        if (in[i] == value) {
            return i;
        }
    }
    return -1;
}

/* Convert a given tree to SUM tree by changing the values of
 * node data.*/
bt_node_t* convertTreeToSumTree(bt_node_t *root)
{
    return NULL;
}


/* Construct tree from In-order + pre-order/post-order traversals
 * We need in-order + one of the remaining traversals to fully contruct*/
bt_node_t* buildTreeInAndPre(int *in, int *pre, int start, int end, int *preIdx)
{
    int iIdx;
    bt_node_t *newNode;

    //printf("%s: start:%d end:%d  preIdx:%d\n", __FUNCTION__, start, end, preIdx ? *preIdx: -1);
    if (!in || !pre || !preIdx || (start < 0) || (end < 0) || (start > end)) {
        return NULL;
    }

    newNode = (bt_node_t*)malloc(sizeof(bt_node_t));
    if(!newNode) {
        printf("Memory alloc failed\n");
        return NULL;
    }
    newNode->val = pre[*preIdx];
    *preIdx = *preIdx + 1;

    if (start == end) {
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    iIdx = searchInOrderTable(in, start, end, newNode->val);
    if (iIdx < 0) {
        printf("%d not found in InOrderTraversal\n", newNode->val);
        return NULL;
    }

    //printf("%s\n", "LEFT");
    newNode->left = buildTreeInAndPre(in, pre, start, iIdx - 1, preIdx);

    //printf("%s\n", "RIGHT");
    newNode->right = buildTreeInAndPre(in, pre, iIdx + 1, end, preIdx);

    return newNode;
}


bt_node_t* buildTreeInAndPost(int *in, int *po, int start, int end, int *poIdx)
{
    int iIdx;
    bt_node_t *newNode;


    //printf("%s: start:%d end:%d  poIdx:%d po[poIdx]:%d \n", __FUNCTION__, start, end, poIdx ? *poIdx: -1, po[*poIdx]);
    if (!in || !po || !poIdx || (start < 0) || (end < 0) || (start > end)) {
        return NULL;
    }

    newNode = (bt_node_t*)malloc(sizeof(bt_node_t));
    if(!newNode) {
        printf("Memory alloc failed\n");
        return NULL;
    }
    newNode->val = po[*poIdx];
    *poIdx = *poIdx - 1;

    if (start == end) {
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    iIdx = searchInOrderTable(in, start, end, newNode->val);
    if (iIdx < 0) {
        //printf("%d not found in InOrderTraversal\n", newNode->val);
        return NULL;
    } else {
        //printf("Found %d at %d in in\n", newNode->val, iIdx);
    }

    //printf("%s\n", "RIGHT");
    newNode->right = buildTreeInAndPost(in, po, iIdx + 1, end, poIdx);

    //printf("%s\n", "LEFT");
    newNode->left = buildTreeInAndPost(in, po, start, iIdx - 1, poIdx);

    return newNode;
}

int getDiameterOfTree(bt_node_t *root, int* max)
{
    int leftHgt, rightHgt;

    if(!root) {
        return 0;
    }

    if (!root->left && !root->right) {
        return 1;
    }

    leftHgt = getDiameterOfTree(root->left, max);
    rightHgt = getDiameterOfTree(root->right, max);

    if (*max < (leftHgt + rightHgt + 1)) {
        *max = leftHgt + rightHgt + 1;
    }

    return (leftHgt > rightHgt) ? (leftHgt + 1) : (rightHgt + 1) ;
}

//Totest

void doubleTree(bt_node_t* root)
{
    bt_node_t* newNode;

    if (!root) {
        return;
    }

    newNode = (bt_node_t*)malloc(sizeof(bt_node_t));
    newNode->left = root->left;
    newNode->val = root->val;
    newNode->right = NULL;
    root->left = newNode;

    doubleTree(newNode->left);
    doubleTree(root->right);
}



/* A tree is foldable if its left subtree is mirror of its
 * right subtree.
 */
int isTreeFoldableImpl(bt_node_t *a, bt_node_t* b)
{
    if (!a && !b) {
        return 1;
    } else if (!a || !b ) {
        return 0;
    } else {
        return (isTreeFoldableImpl(a->left, b ->right) &&
               isTreeFoldableImpl(a->right, b->left));
    }
}

/* Check if the left trbee and right tree are
 * mirrors of each other.
 */
int isTreeFoldable(bt_node_t *root)
{
    if (!root) {
        return 0;
    }

    return isTreeFoldableImpl(root->left, root->right);
}

int isIdenticalTree(bt_node_t *t1, bt_node_t* t2)
{
    if (!t1 && !t2) {
        return 1;
    } else if (!t1 || !t2) {
        return 0;
    }

    if (t1->val != t2->val) {
        return 0;
    }

    return (isIdenticalTree(t1->left, t2->left) &&
            isIdenticalTree(t1->right, t2->right));
}

/*Check if a given tree is a subtree of another.*/
int isSubTree(bt_node_t *t1, bt_node_t* t2)
{
    if (!t1 && !t2) {
        return 1;
    } else if (!t1 || !t2) {
        return 0;
    }

    if (isIdenticalTree(t1, t2)) {
        return 1;
    }

    return (isSubTree(t1->left, t2) || isSubTree(t1->right, t2));
}

void printLevelNodesImpl(bt_node_t* root, int level)
{
    bt_node_t* run;
    if (!root) {
        return;
    }


    if (level == 1) {
        run = root;
        while (run) {
            printf("%d\t", run->val);
            run = run->nextRight;
        }
        return;
    }

    if (root->left) {
        printLevelNodesImpl(root->left, level - 1);
    } else {
        printLevelNodesImpl(root->right, level - 1);
    }

    return;
}

bt_node_t* connectLevelNodesImpl(bt_node_t* root, int level)
{
    bt_node_t* left, *right, *runner;

    if (!root) {
        return NULL;
    }


    if (level == 1) {
        root->nextRight = NULL;
        return root;
    }

    left = connectLevelNodesImpl(root->left, level - 1);
    right = connectLevelNodesImpl(root->right, level -1);

    if (left) {
        runner = left;
        while(runner->nextRight) {
            runner = runner->nextRight;
        }
        runner->nextRight = right;
        return left;
    } else {
        return right;
    }
}

void connectLevelNodes(bt_node_t* root)
{
    int hgt = bt_get_height(root), i;

    for(i = 1; i <= hgt; i++) {
        //connectLevelNodesImpl(root , i);
    }

    /*Test*/
    for(i = 1; i <= hgt; i++) {
        printLevelNodesImpl(root , i);
        printf("\n");
    }

    return;
}


void connectLevelNodesFaster(bt_node_t* root)
{
    if (!root) {
        return;
    }

    if (root->left) {
        root->left->nextRight = root->right;
    }

    if (root->right) {
        if (root->nextRight) {
            if (root->nextRight->left) {
                root->right->nextRight = root->nextRight->left;
            } else {
                root->right->nextRight = root->nextRight->right;
            }
        }
    }

    connectLevelNodesFaster(root->left);
    connectLevelNodesFaster(root->right);

    return;
}

/*Get max sum path from root to leaf*/
void bt_get_max_sum_leaf(bt_node_t *root, int* sum, bt_node_t **leaf)
{
    int curr_sum;

    if (!root) {
        return;
    }

    curr_sum = *sum + root->val;

    if (!root->left && !root->right) {
        if (curr_sum > *sum) {
            *sum = curr_sum;
            *leaf = root;
        }
        return;
    }

    bt_get_max_sum_leaf(root->left, sum, leaf);
    bt_get_max_sum_leaf(root->right, sum, leaf);
}

int bt_print_path(bt_node_t *root, bt_node_t *leaf)
{
    if (!root) {
        return 0;
    }

    if ((root == leaf) ||
        bt_print_path(root->left, leaf) ||
        bt_print_path(root->right, leaf)) {
        printf("%d\t", root->val);
        return 1;
    }

    return 0;
}

void bt_get_max_sum_path(bt_node_t *root)
{
    int sum = INT_MIN;
    bt_node_t* leaf = NULL;

    bt_get_max_sum_leaf(root, &sum, &leaf);
    bt_print_path(root, leaf);

    return;
}

/* Build special tree from in order arr where every key is greater than its
 * left and right subtrees */

int getMaxIdx(int *in, int start, int end)
{
    int max = INT_MIN, i, resIdx = -1;

    if (!in || (start > end)) {
        return -1;
    }

    for(i = start; i <= end; i++) {
        if (max < in[i]) {
            max = in[i];
            resIdx = i;
        }
    }

    return resIdx;
}



bt_node_t* buildSpecialTreeIn(int *in, int start, int end)
{
    int iIdx;
    bt_node_t *newNode;

    if (!in || (start < 0) || (end < 0) || (start > end)) {
        return NULL;
    }

    iIdx = getMaxIdx(in, start, end);
    if (iIdx < 0) {
        printf("Max calculation failure\n");
        return NULL;
    }

    newNode = (bt_node_t*)malloc(sizeof(bt_node_t));
    if(!newNode) {
        printf("Memory alloc failed\n");
        return NULL;
    }

    newNode->val = in[iIdx];

    if (start == end) {
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }


    //printf("%s\n", "LEFT");
    newNode->left = buildSpecialTreeIn(in,start, iIdx - 1);

    //printf("%s\n", "RIGHT");
    newNode->right = buildSpecialTreeIn(in, iIdx + 1, end);

    return newNode;
}



/* Construct special tree where two arrays are given
 * 1. Pre order traversal
 * 2. Another array where each value is 'N' or 'L'
 *    depending on whether its a node or a leaf.
 *
 * condition: Every node is a leaf or has two children.
 **/

bt_node_t* buildSpecialTree1(int *node, char *nodeT, int *idx, int max)
{
    bt_node_t *newNode;

    if (!node || !nodeT || !idx || (*idx >= max)) {
        return NULL;
    }

    newNode = bt_get_new_node(node[*idx]);

    if (nodeT[*idx] == 'N') {
        *idx = *idx + 1;

        newNode->left = buildSpecialTree1(node, nodeT, idx, max);
        newNode->right = buildSpecialTree1(node, nodeT, idx, max);

    } else {

        *idx = *idx + 1;
    }

    return newNode;
}

int isCompleteTree(bt_node_t* root)
{
	if (!root) {
		return 1;
	}

	if (!root->left) {
		if (!root->right ) {
			return 1;
		} else {
			return 0;
		}
	}

	return (isCompleteTree(root->left) && isCompleteTree(root->right));
}

void bt_print_bndry_nodes_left(bt_node_t* root)
{
	if (!root) {
		return;
	}

	if (root->left) {
		printf("%d ", root->val);
		bt_print_bndry_nodes_left(root->left);
	} else if (root->right) {
		printf("%d ", root->val);
		bt_print_bndry_nodes_left(root->right);
	}
	return;
}

void bt_print_bndry_nodes_leaves(bt_node_t *root)
{
	if (!root) {
		return;
	}

	if (!root->left && !root->right) {
		printf("%d ", root->val);
		return;
	}

	bt_print_bndry_nodes_leaves(root->left);
	bt_print_bndry_nodes_leaves(root->right);

}

void bt_print_bndry_nodes_right(bt_node_t *root)
{
	if (!root) {
		return;
	}

	if (root->right) {
		bt_print_bndry_nodes_right(root->right);
		printf("%d ", root->val);
	} else if (root->left) {
		bt_print_bndry_nodes_right(root->left);
		printf("%d ", root->val);
	}
}

void bt_print_bndry_nodes(bt_node_t *root)
{
	/*Print the left boundary including the root*/
	bt_print_bndry_nodes_left(root);
	/*Print the leaves*/
	bt_print_bndry_nodes_leaves(root->left);
	bt_print_bndry_nodes_leaves(root->right);

	/*Print the right boundary excluding the  */
	bt_print_bndry_nodes_right(root->right);
}


/*Iterative preorder traversal using stack*/
void bt_print_preorder_iterative(bt_node_t *root)
{
	bt_node_t *curr;
	st_t *st;

	if (!root) {
		printf("Empty tree\n");
		return;
	}

	st = st_create(VOID_DATA);
	st_push(st, 0, root);

	while (!is_st_empty(st)) {
		st_pop(st,NULL, (void**)&curr);
		printf("%d\n", curr->val);

		if (curr->right) {
			st_push(st, 0, curr->right);
		}

		if (curr->left) {
			st_push(st, 0, curr->left);
		}
	}

	st_destroy(st);
}

/**
 * Algorithm
 * 1. If node has no left child, print and move to right child.
 * 2. If node has left child :
 * 	  Find predecessor for this node (left and right till leaf)
 * 	  a. If current node is encountered while finding the predecessor then
 * 	     reset the right child of the predecessor and move to right.
 * 	  b. Print node and set the right child of the predecossor to the current
 * 	     node and move left.
 *
 */
void bt_print_preorder_morris(bt_node_t *root)
{
	if (!root) {
		return;
	}

	while (root) {
		if (!root->left) {
			printf ("%d ", root->val);
			root = root->right;
		} else {
			bt_node_t *curr = root->left;
			while (curr->right && (curr->right != root)) {
				curr = curr->right;
			}

			if (curr->right) {
				curr->right = NULL;
				root = root->right;
			} else {
				printf("%d ", root->val);
				curr->right = root;
				root = root->left;
			}
		}
	}
	printf("\n");
	return;
}

/* DS: Use 2 stacks
 * Algorithm:
 * 1. push root to stack1
 * 2. while stack1 is not empty
 * 	  - pop top
 * 	  - push right child and then left child into stack1
 * 	  - push node to stack2
 * 3. Print stack2 elements.
 * */
void bt_print_post_order_iterative(bt_node_t *bt)
{
	st_t *s1, *s2;
	bt_node_t *curr;

	if (!bt) {
		return;
	}

	s1 = st_create(VOID_DATA);
	s2 = st_create(VOID_DATA);

	st_push(s1, 0, bt);

	while (!is_st_empty(s1)) {
		st_pop(s1, NULL, (void**)&curr);

		//printf("popping %d from s1\n", curr->val);

		if (curr->left) {
			//printf("pushing %d to s1\n", curr->left->val);
			st_push(s1, 0, curr->left);
		}

		if (curr->right) {
			//printf("pushing %d to s1\n", curr->right->val);
			st_push(s1, 0, curr->right);
		}

		//printf("pushing %d to s2\n", curr->val);
		st_push(s2, 0, curr);
	}


	while(!is_st_empty(s2)) {
		st_pop(s2, NULL, (void**)&curr);
		printf("%d ", curr->val);
	}

	printf("\n");

	st_destroy(s1);
	st_destroy(s2);

	return;
}

/**
 * LISS - Largest Independent Set Size
 * Algorithm (with memoization):
 * Max of LISS (grandchildren) and LISS of (children)
 **/
int LISS(bt_node_t *root)
{
	int liss_children, liss_gchildren = 1;

	if (!root) {
		return 0;
	}

	if (root->liss) {
		return root->liss;
	} else if (!root->left && !root->right) {
		root->liss = 1;
		return root->liss;
	}

	liss_children = LISS(root->left) + LISS(root->right);

	if (root->left) {
		liss_gchildren += LISS(root->left->left) + LISS(root->left->right);
	}

	if (root->right) {
		liss_gchildren += LISS(root->right->left) + LISS(root->right->right);
	}

	root->liss = MAX(liss_children, liss_gchildren);

	return root->liss;
}






