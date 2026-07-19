typedef struct MBlock {
    unsigned short size;
    struct MBlock *prev;
    struct MBlock *next;
} MBlock;

typedef struct { MBlock *head; MBlock *tail; } MBlockList;

/* Unlink b from the doubly-linked block list; returns the block that preceded it. */
MBlock *RemoveMBlock(MBlockList *list, MBlock *b) {
    MBlock *prev = *(MBlock **)((char *)b + 8);
    MBlock *next = *(MBlock **)((char *)b + 0xc);
    if (prev != 0) {
        *(MBlock **)((char *)prev + 0xc) = next;
    } else {
        list->head = next;
    }
    if (next != 0) {
        *(MBlock **)((char *)next + 8) = prev;
    } else {
        list->tail = prev;
    }
    return prev;
}
