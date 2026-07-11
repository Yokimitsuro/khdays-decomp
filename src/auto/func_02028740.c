#pragma thumb on
/* Unlink node from its doubly-linked list (next at [0], prev at [4]); fix the
 * head if node was first, then clear node's links. */
void func_02028740(int **head, int *node) {
    if (node[0] != 0) {
        *(int *)(node[0] + 4) = node[1];
    }
    if (node[1] != 0) {
        *(int *)node[1] = node[0];
    }
    if (node == *head) {
        *head = (int *)node[0];
    }
    node[1] = 0;
    node[0] = 0;
}
