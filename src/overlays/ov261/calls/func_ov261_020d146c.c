extern void func_ov107_020c9264();
extern void func_ov107_020c5af8();
extern void func_0203c634();
extern void func_ov261_020d14bc();

void func_ov261_020d146c(int this_) {
    int node = *(int *)(this_ + 4);
    func_ov107_020c9264(*(int *)node, 1, 1);
    func_ov107_020c5af8(*(int *)node, 0x179, 4, *(int *)(node + 4));
    *(int *)(node + 0x40) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov261_020d14bc);
}
