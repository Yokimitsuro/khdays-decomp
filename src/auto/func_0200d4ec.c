/* Append `node` to the tail of the singly-linked list at *head (next at +8):
 * if the list is empty, node becomes the head; otherwise walk to the last node
 * and link node after it. node's next is cleared. */
void func_0200d4ec(void **head, void *node) {
    void *cur, *next;
    if (head == 0) return;
    cur = *head;
    if (cur == 0) {
        *(void **)((char *)node + 8) = 0;
        *head = node;
        return;
    }
    next = *(void **)((char *)cur + 8);
    while (next != 0) {
        cur = next;
        next = *(void **)((char *)cur + 8);
    }
    *(void **)((char *)node + 8) = next;
    *(void **)((char *)cur + 8) = node;
}
