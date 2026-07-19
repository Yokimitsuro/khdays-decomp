typedef struct DLNode { struct DLNode *prev; struct DLNode *next; } DLNode;

/* Unlinks node; returns the new head (node->next when node was first, otherwise head as given). */
void *DLExtract(void *head, DLNode *node) {
    DLNode *next = node->next;
    if (next != 0) {
        next->prev = node->prev;
    }
    if (node->prev == 0) {
        return node->next;
    }
    node->prev->next = node->next;
    return head;
}
