extern void func_ov022_020892f0(unsigned short *arg0, short arg1);
void func_ov022_020894a0(int arg0, int arg1, short arg2) {
    int b = *(int *)(arg0 + 0x20);
    if (arg1 < 0) return;
    func_ov022_020892f0((unsigned short *)(arg1 * 0x114 + *(int *)(b + 0xc) + 4), arg2);
}
