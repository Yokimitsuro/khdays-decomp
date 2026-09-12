extern char *data_0204c234;

typedef struct SlotLink {
    struct SlotLink *next;
    struct SlotLink *prev;
} SlotLink;

void func_02032a7c(void *ptr) {
    SlotLink *node = (SlotLink *)ptr;
    char *base = data_0204c234;

    {
        SlotLink *tailVal = *(SlotLink **)(base + 0xb46e8);
        if (tailVal == node) {
            *(SlotLink **)(base + 0xb46e8) = tailVal->next;
        }
    }
    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    if (node->prev != 0) {
        node->prev->next = node->next;
    }
    node->next = *(SlotLink **)(base + 0xb46e4);
    node->prev = 0;
    if (*(SlotLink **)(base + 0xb46e4) != 0) {
        (*(SlotLink **)(base + 0xb46e4))->prev = node;
    }
    *(SlotLink **)(base + 0xb46e4) = node;
    *(unsigned short *)((char *)node + 0x14) = 0;
}
