extern void func_ov107_020c9264();
extern void func_0203c634();
extern void func_ov261_020d0b28();

void func_ov261_020d0ae8(int this_) {
    int node = *(int *)(this_ + 4);
    func_ov107_020c9264(*(int *)node, 2, 1);
    *(int *)(*(int *)node + 0x3a8) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov261_020d0b28);
}
