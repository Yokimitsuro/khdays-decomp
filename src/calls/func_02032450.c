extern void func_02031df0(void *ptr, void *arg);

void func_02032450(unsigned char *ptr, int index) {
    int offset;
    int *flags;

    if (index < 0) {
        return;
    }

    offset = index * 0x8c;
    flags = (int *)(ptr + 0x7c + offset);
    if (((unsigned int)(*flags << 31) >> 31) == 0) {
        return;
    }

    func_02031df0(ptr, ptr + 4 + offset);
    *flags &= ~1;
}
