extern void func_01ffa724();

struct w3 { int a, b, c; };

void func_ov199_020d58dc(int this_, struct w3 *src) {
    *(signed char *)(*(int *)this_ + 0x1c7) = 1;
    *(struct w3 *)(this_ + 0x14) = *src;
    func_01ffa724(0x800, this_ + 0x14, this_ + 8);
}
