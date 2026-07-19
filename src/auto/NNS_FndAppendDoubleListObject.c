typedef struct Link { struct Link *prev; struct Link *next; } Link;

/* Appends obj to the end of the list, walking from the head to find the current tail. */
void NNS_FndAppendDoubleListObject(Link **list, Link *obj) {
    Link *tail = list[0];
    if (tail == 0) {
        obj->prev = 0;
        list[0] = obj;
    } else {
        Link *n = tail->next;
        while (n != 0) {
            tail = n;
            n = n->next;
        }
        obj->prev = tail;
        tail->next = obj;
    }
    obj->next = 0;
}
