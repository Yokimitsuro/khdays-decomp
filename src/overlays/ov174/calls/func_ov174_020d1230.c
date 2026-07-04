extern void func_ov107_020c9264();
extern int func_02023eb4();
extern void func_0203c634();
extern void func_ov174_020d1274();

void func_ov174_020d1230(int this_) {
    int node = *(int *)(this_ + 4);
    func_ov107_020c9264(*(int *)node, 1, 1);
    *(int *)(node + 0x54) = func_02023eb4(0x15) + 0x14;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov174_020d1274);
}
