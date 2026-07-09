extern void func_ov107_020c9264();
extern void func_0203c634();
extern void func_ov205_020d5a14();

void func_ov205_020d59c8(int this_) {
    int n = *(int *)(this_ + 4);
    if (*(unsigned char *)*(int *)(n + 0x28)) return;
    func_ov107_020c9264(*(int *)n, 0xa, 1);
    *(int *)(n + 0x2c) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov205_020d5a14);
}
