typedef struct List0200ff94 {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short offset;
} List0200ff94;

void func_0200ff94(List0200ff94 *list, void *node)
{
    char *link = (char *)node + list->offset;

    *(void **)(link + 4) = 0;
    *(void **)link = 0;
    list->head = node;
    list->tail = node;
    list->count++;
}
