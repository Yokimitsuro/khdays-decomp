extern void func_0203c634();

struct b1 { unsigned char b : 1; };

void func_ov286_020d3fe8(int this_) {
    int a = *(int *)this_;
    int b = *(int *)(this_ + 4);
    int obj;
    *(int *)(b + 0x28) = *(int *)(b + 0x28) + *(int *)(a + 0x2c);
    obj = *(int *)b;
    if (((struct b1 *)(obj + 0x17a))->b == 0) return;
    if (*(int *)(b + 0x28) < 0x400) return;
    *(signed char *)(obj + 0x1c7) = 2;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
