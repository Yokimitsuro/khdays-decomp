struct Node {
    struct Node *prev;
    struct Node *next;
};

void NNS_FndAppendDoubleListObject(struct Node **head, struct Node *node)
{
    struct Node *tail = *head;
    if (tail == 0) {
        node->prev = 0;
        *head = node;
    } else {
        while (tail->next != 0) {
            tail = tail->next;
        }
        node->prev = tail;
        tail->next = node;
    }
    node->next = 0;
}
