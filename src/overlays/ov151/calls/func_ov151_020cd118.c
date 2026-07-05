struct w4 { int a, b, c, d; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634();

void func_ov151_020cd118(int this_) {
    int holder = *(int *)(this_ + 4);
    if ((((struct hw60 *)(*(int *)holder + 0x60))->lo & 1) == 0) return;
    *(struct w4 *)(holder + 0x18) = *(struct w4 *)(*(int *)holder + 0x394);
    *(signed char *)(*(int *)holder + 0x1c7) = 1;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
