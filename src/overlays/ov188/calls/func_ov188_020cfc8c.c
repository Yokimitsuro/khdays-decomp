extern void func_ov107_020c9264();
extern void func_0203c634();
extern void func_ov188_020cfce0();

void func_ov188_020cfc8c(int this_) {
    int node = *(int *)(this_ + 4);
    if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)node, 0xc, 1);
    *(int *)(node + 0x18) = 0;
    *(unsigned char *)(node + 0x3c) = 0;
    *(unsigned char *)(node + 0x3d) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov188_020cfce0);
}
