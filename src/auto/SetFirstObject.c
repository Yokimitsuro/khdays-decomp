typedef struct { void *head; void *tail; unsigned short count; unsigned short linkOffset; } DLList;

/* Makes obj the one and only element: its link is cleared and the list points at it twice. */
void SetFirstObject(DLList *list, void *obj) {
    char *link = (char *)obj + list->linkOffset;
    *(void **)(link + 4) = 0;
    *(void **)link = 0;
    list->head = obj;
    list->tail = obj;
    list->count++;
}
