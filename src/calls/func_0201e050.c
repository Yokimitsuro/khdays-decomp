extern int MI_CpuCopy8();
extern void *func_0201b7e0();

int func_0201e050(char *p, int arg) {
    void *src = func_0201b7e0(arg);
    *(void **)(p + 0xa4) = src;
    MI_CpuCopy8(src, p + 0xa8, 0x40);
    return 1;
}
