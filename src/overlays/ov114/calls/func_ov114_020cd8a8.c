extern void func_ov107_020c9264();
extern int func_020050b4();
extern void func_0203c634();
extern void func_ov114_020cd8f8();

void func_ov114_020cd8a8(int this_) {
    int node = *(int *)(this_ + 4);
    int a;
    func_ov107_020c9264(*(int *)node, 8, 0);
    a = func_020050b4(*(int *)(node + 0x5c), *(int *)(node + 0x64)) + 0x3244;
    *(int *)(node + 0x18) = a;
    *(int *)(node + 0x14) = a;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov114_020cd8f8);
}
