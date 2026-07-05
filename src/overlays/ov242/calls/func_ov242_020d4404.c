struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634();

void func_ov242_020d4404(int this_) {
    int holder = *(int *)(this_ + 4);
    if ((((struct hw60 *)(*(int *)holder + 0x60))->lo & 1) == 0) return;
    *(int *)(holder + 0x1c) = *(int *)(holder + 0x24) * 0x14 + *(int *)(*(int *)holder + 0x3a4);
    *(signed char *)(*(int *)holder + 0x1c7) = *(signed char *)(*(int *)holder + 0x1c9);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
