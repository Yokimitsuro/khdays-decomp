typedef struct MBlock MBlock;
typedef struct { MBlock *head; MBlock *tail; } MBlockList;

/* Link b into the list right after `after` (or at the head when `after` is null). */
MBlock *InsertMBlock(MBlockList *list, MBlock *b, MBlock *after) {
    MBlock *next;
    *(MBlock **)((char *)b + 8) = after;
    if (after != 0) {
        next = *(MBlock **)((char *)after + 0xc);
        *(MBlock **)((char *)after + 0xc) = b;
    } else {
        next = list->head;
        list->head = b;
    }
    *(MBlock **)((char *)b + 0xc) = next;
    if (next != 0) {
        *(MBlock **)((char *)next + 8) = b;
    } else {
        list->tail = b;
    }
    return b;
}
