typedef struct Link020102ec {
    int pad0;
    int pad4;
    struct Link020102ec *prev;
    struct Link020102ec *next;
} Link020102ec;

Link020102ec *func_020102ec(Link020102ec **list, Link020102ec *node)
{
    Link020102ec *prev = node->prev;
    Link020102ec *next = node->next;

    if (prev != 0) {
        prev->next = next;
    } else {
        list[0] = next;
    }

    if (next != 0) {
        next->prev = prev;
    } else {
        list[1] = prev;
    }

    return prev;
}
