typedef struct { unsigned short size; unsigned short flags; int len; void *prev; void *next; } MBlock;
typedef struct { MBlock *start; char *end; } MHeap;

/* Turns the whole heap into a single free block: 0x10-byte header, the rest is payload. */
MBlock *InitMBlock(MHeap *heap, unsigned short size) {
    MBlock *b = heap->start;
    b->size = size;
    b->flags = 0;
    b->len = (int)(heap->end - ((char *)b + 0x10));
    b->prev = 0;
    b->next = 0;
    return b;
}
