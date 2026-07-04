extern void func_ov107_020c9264();
extern void func_ov107_020c9ee8();
extern void func_0203c634();
extern void func_ov270_020d4be4();

void func_ov270_020d4b98(int this_) {
    int node = *(int *)(this_ + 4);
    func_ov107_020c9264(*(int *)node, 2, 1);
    *(int *)(node + 0x30) = 0;
    func_ov107_020c9ee8(*(int *)(*(int *)node + 0x3d0), 0, 1);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov270_020d4be4);
}
