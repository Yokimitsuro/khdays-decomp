extern void func_ov107_020c9264();
extern void func_0203c634();
extern void func_ov276_020d27a8();

void func_ov276_020d275c(int this_) {
    int a = *(int *)this_;
    int b = *(int *)(this_ + 4);
    int v = *(int *)(b + 0x4c) - *(int *)(a + 0x2c);
    *(int *)(b + 0x4c) = v;
    if (v > 0) return;
    func_ov107_020c9264(*(int *)b, 0x15, 0);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov276_020d27a8);
}
