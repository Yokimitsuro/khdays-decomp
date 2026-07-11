/* Unlink `node` from its doubly-linked list, fix head at
 * *(data_0204c208 + node[0xa]*4 + 0x64), then zero node links and mark node[0xa]=0xff.
 * Family with func_0202b628/684/6e0 differing only in the head-table offset. */
extern int data_0204c208;
void func_0202b628(void *node) {
    void *next = *(void **)node;
    int base = data_0204c208;
    if (next != 0) {
        *(void **)((char *)next + 4) = *(void **)((char *)node + 4);
    }
    {
        void *prev = *(void **)((char *)node + 4);
        if (prev != 0) {
            *(void **)prev = *(void **)node;
        }
    }
    {
        int idx = *(unsigned char *)((char *)node + 0xa);
        void **head = (void **)(base + idx * 4 + 0x64);
        if (*head == node) {
            *head = *(void **)node;
        }
    }
    *(void **)((char *)node + 4) = 0;
    *(void **)node = 0;
    *(unsigned char *)((char *)node + 0xa) = 0xff;
}
