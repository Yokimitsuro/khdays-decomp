extern int func_ov107_020cb100();
extern int func_ov107_020c9f48();
extern int func_0202f384();
extern int func_01ffa724();
extern int func_0203c634();

void func_ov131_020cde38(int this) {
    int s = *(int *)(this + 4);
    int p = *(int *)s;
    int local[3];
    int r6;

    if (*(int *)(p + 0x3d0) != 0) {
        func_ov107_020cb100();
        *(int *)(*(int *)s + 0x3d0) = 0;
    }

    p = *(int *)s;
    r6 = func_ov107_020c9f48(*(int *)(p + 0x3c8), local);

    func_0202f384(s + 0x18, *(int *)s + 0xa0, local);

    func_01ffa724(r6, s + 0x18, s + 0x18);

    p = *(int *)s;
    if (((unsigned int)(*(unsigned char *)(p + 0x17a) << 0x1f) >> 0x1f) == 0) {
        return;
    }
    if (*(unsigned char *)(*(int *)(s + 0x48)) != 0) {
        return;
    }

    *(unsigned char *)(p + 0x1c7) = 2;
    func_0203c634(this, *(signed char *)(this + 0x20), 0);
}
