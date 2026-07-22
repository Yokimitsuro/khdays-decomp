/* Pushes `node` onto the front of a doubly linked list and returns the new head. */
struct DLNode {
    struct DLNode *prev;
    struct DLNode *next;
};

struct DLNode *DLAddFront(struct DLNode *head, struct DLNode *node) {
    node->next = head;
    node->prev = 0;
    if (head != 0) {
        head->prev = node;
    }
    return node;
}
