struct Node {
    struct Node *prev;
    struct Node *next;
};

struct Node *func_02002c0c(struct Node *ret, struct Node *node)
{
    if (node->next != 0)
        node->next->prev = node->prev;
    if (node->prev == 0)
        return node->next;
    node->prev->next = node->next;
    return ret;
}
