int func_0203be68(int *obj, int idx, int idx2) {
    short *base = *(short **)((char *)obj + 0x8c);
    if (base[idx] == 0) {
        return 0;
    }
    {
        int *p = *(int **)((char *)base + idx * 4 + 0x10);
        int *q = (int *)p[idx2];
        int *r = (int *)q[2];
        return ((unsigned short *)r)[2] << 12;
    }
}
