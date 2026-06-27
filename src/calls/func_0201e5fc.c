extern int OS_UnlockByWord_0x0200ae4c(void *file, void *buf, int size);
extern void func_0200443c(void *a, void *buf, void *hdr);
extern void *func_020236f8(unsigned size, int align, int **heapPP);

void *func_0201e5fc(char *self, void *file, int existing, int maxSize, int **heap) {
    int hdr;
    void *buf;
    unsigned size;

    OS_UnlockByWord_0x0200ae4c(file, &hdr, 4);
    size = (unsigned)hdr >> 8;
    if (existing == 0) {
        buf = func_020236f8(size, 0x20, heap);
    } else {
        if ((int)size > maxSize) return 0;
        buf = (void *)existing;
    }
    *(void **)(self + 0x28) = buf;
    *(unsigned *)(self + 0x2c) = size;
    func_0200443c(self + 0x14, buf, &hdr);
    return buf;
}
