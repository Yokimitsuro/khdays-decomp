extern void *func_02010af0(void *hh, unsigned size, unsigned align);
extern void *func_02010a94(void *hh, unsigned size, unsigned align);

void *func_02010bcc(void *heap, unsigned size, int align) {
    if (size == 0) size = 1;
    size = (size + 3) & ~3;
    heap = (char *)heap + 0x24;
    if (align >= 0) {
        return func_02010a94(heap, size, (unsigned)align);
    } else {
        return func_02010af0(heap, size, (unsigned)-align);
    }
}
