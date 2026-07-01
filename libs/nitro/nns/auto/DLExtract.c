typedef struct Unk02002c0c {
    struct Unk02002c0c *next;
    struct Unk02002c0c *prev;
} Unk02002c0c;

Unk02002c0c *DLExtract(Unk02002c0c *tail, Unk02002c0c *node)
{
    if (node->prev != 0) {
        node->prev->next = node->next;
    }

    if (node->next == 0) {
        tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }

    return tail;
}
