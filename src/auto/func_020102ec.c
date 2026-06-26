struct Node {
    int unk0;
    int unk4;
    struct Node *next;
    struct Node *prev;
};

struct List {
    struct Node *head;
    struct Node *tail;
};

struct Node *func_020102ec(struct List *list, struct Node *node) {
    struct Node *next = node->next;
    struct Node *prev = node->prev;

    if (next)
        next->prev = prev;
    else
        list->head = prev;

    if (prev)
        prev->next = next;
    else
        list->tail = next;

    return next;
}
