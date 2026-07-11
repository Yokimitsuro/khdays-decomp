/* Remove `node` from the singly linked list headed by *head (next link @+0x10).
 * Returns 1 if the node was found and unlinked (also clearing node's own next
 * pointer), 0 otherwise. The loop's first read of cur->next is kept distinct
 * from the head-case read (the ROM re-loads rather than reusing the value). */
int func_02014d50(int *head, int node) {
    int next;
    int cur = *head;
    if (cur == 0) return 0;
    if (cur == node) {
        *head = *(int *)(cur + 0x10);
        *(int *)(node + 0x10) = 0;
        return 1;
    }
    next = *(volatile int *)(cur + 0x10);
    while (next != 0) {
        if (next == node) {
            *(int *)(cur + 0x10) = *(int *)(next + 0x10);
            *(int *)(next + 0x10) = 0;
            return 1;
        }
        cur = next;
        next = *(int *)(next + 0x10);
    }
    return 0;
}
