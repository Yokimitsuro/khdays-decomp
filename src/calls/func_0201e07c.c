extern int MI_CpuCopy8();

int func_0201e07c(int *p, void *dst, int sz, int off) {
    MI_CpuCopy8(*(char **)((char *)p + 0xa4) + off, dst, sz);
    return sz;
}
