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






