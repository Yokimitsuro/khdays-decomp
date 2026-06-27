extern void WM_EndKeySharing_0x020107f0(void *heap);
extern void *NNS_FndCreateExpHeapEx(void *start, unsigned int size, int opt);
extern void NNS_FndInitAllocatorForExpHeap(void *allocator, void *heap, int align);

struct State {
    char *heap;
    int allocator;
};

void func_02023604(struct State *s) {
    char *old = s->heap;
    unsigned int size = (unsigned int)(((char **)old)[7] - old);
    WM_EndKeySharing_0x020107f0(old);
    s->heap = (char *)NNS_FndCreateExpHeapEx(old, size, 1);
    NNS_FndInitAllocatorForExpHeap(&s->allocator, s->heap, 4);
}
