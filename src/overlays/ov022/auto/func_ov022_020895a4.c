struct bf_020895a4 { unsigned char f : 2; unsigned char rest : 6; };
void func_ov022_020895a4(int arg0, int arg1) {
    struct bf_020895a4 *p = *(struct bf_020895a4 **)(arg0 + 0x20);
    if (arg1 > 0) {
        p->f |= 2;
        *(int *)((char *)p + 0x1c) = arg1;
        return;
    }
    p->f &= ~2;
}
