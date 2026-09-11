extern void *func_0203d15c(int size);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

int func_ov107_020c1e24(void *self, int size, void *src) {
    short idx = *(short *)((char *)self + 0xb0);
    void *buf;

    if (idx >= 8) return -1;
    buf = *(void **)((char *)self + idx * 8 + 0xb4) = func_0203d15c(size);
    MI_CpuCopy8(src, buf, size);
    *(int *)((char *)self + 0xb8 + idx * 8) = size;
    *(short *)((char *)self + 0xb0) = *(short *)((char *)self + 0xb0) + 1;
    return idx;
}
