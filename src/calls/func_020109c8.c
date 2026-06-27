extern int abs(int);

typedef struct Block {
    int pad0;
    int size;
    int pad8;
    struct Block *next;
} Block;

int func_020109c8(void *heap, int align_in) {
    int align;
    int best_size;
    unsigned int best_pad;
    Block *node;
    unsigned int mask_lo, mask_hi;

    align = abs(align_in);
    node = *(Block **)((char *)heap + 0x24);
    best_size = 0;
    best_pad = (unsigned int)-1;
    if (node == 0) goto end;

    mask_lo = align - 1;
    mask_hi = ~mask_lo;
    do {
        unsigned int base = (unsigned int)node + 0x10;
        unsigned int size = (unsigned int)node->size;
        unsigned int aligned = (mask_lo + base) & mask_hi;
        unsigned int end_addr = size + base;
        if (aligned < end_addr) {
            unsigned int avail = end_addr - aligned;
            unsigned int pad = aligned - base;
            if ((unsigned int)best_size < avail ||
                ((unsigned int)best_size == avail && best_pad > pad)) {
                best_size = avail;
                best_pad = pad;
            }
        }
        node = node->next;
    } while (node);
end:
    return best_size;
}
