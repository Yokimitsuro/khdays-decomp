/* Unlinks and releases every node of the intrusive doubly linked list. */
extern void func_0203d194(void *node);

void NNSi_FndDestroyDoubleList(int *list) {
    int *node = (int *)list[4];
    int *next;
    if (node == list) {
        return;
    }
    do {
        next = (int *)node[0];
        *(int *)(next + 1) = node[1];
        *(int *)node[1] = node[0];
        func_0203d194(node);
        list[8] = list[8] - 1;
        node = next;
    } while (next != list);
}
