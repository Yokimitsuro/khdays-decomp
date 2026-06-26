struct Vec3 {
    int x;
    int y;
    int z;
};

extern int func_ov107_020c0b90(int a, int b, struct Vec3 v, int c);

int func_ov171_020ce2e8(int *a, int b, short *c) {
    int *p = *(int **)((char *)a + 0x214);
    int *q = *(int **)p;
    struct Vec3 *vp;
    unsigned short v;
    if (*(signed char *)((char *)q + 0x1c6) == 1) {
        v = (unsigned short)*(int *)c;
        if (v & 1) {
            if (v & 0x10) {
                vp = *(struct Vec3 **)((char *)p + 8);
                func_ov107_020c0b90(*(int *)((char *)q + 0x38c), 2, *vp, 0);
                *(char *)(*(int *)p + 0x1c7) = 0;
                return 1;
            }
        }
    }
    return 0;
}
