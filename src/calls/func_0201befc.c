extern unsigned int func_0201b6cc(void *a0, void *a1, void *a2, void *a3);
extern void *func_0201b9a0(void *heap, unsigned int size, void *a2, void *a3, void *a4);
extern unsigned int func_0201b6f4(void *a0, void *buf, unsigned int size, int zero);
extern void DC_StoreRange(void *start, unsigned int size);

void *func_0201befc(void *a0, void *a1, void *a2, void *a3, void *a4)
{
    unsigned int size;
    void *buf;

    size = func_0201b6cc(a0, a1, a2, a3);
    if (size == 0) {
        return 0;
    }
    if (a4 == 0) {
        return 0;
    }

    buf = func_0201b9a0(a4, size + 0x20, a1, a2, a3);
    if (buf == 0) {
        return 0;
    }

    if (size != func_0201b6f4(a0, buf, size, 0)) {
        return 0;
    }

    DC_StoreRange(buf, size);
    return buf;
}
