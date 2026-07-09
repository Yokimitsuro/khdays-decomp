extern void func_ov107_020c9264();
extern void func_0203c634();
extern void func_ov196_020d5afc();

void func_ov196_020d5ab0(int this_) {
    int n = *(int *)(this_ + 4);
    if (*(unsigned char *)(*(int *)(n + 4) + 0xad)) return;
    func_ov107_020c9264(*(int *)n, 7, 1);
    *(int *)(n + 0x30) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov196_020d5afc);
}
