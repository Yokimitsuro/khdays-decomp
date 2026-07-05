struct w3 { int a, b, c; };
struct b1_1 { unsigned char pad : 1, b : 1; };
extern void func_01ffa724(int factor, void *src, void *dst);
extern void func_ov297_020d4168(int this_);
extern void func_0203c634();

void func_ov297_020d5184(int this_) {
    int holder = *(int *)(this_ + 4);
    void *src = (void *)(holder + 0x1c);
    *(struct w3 *)(holder + 0x10) = *(struct w3 *)src;
    func_01ffa724(0xb00, src, src);
    func_ov297_020d4168(this_);
    if (((struct b1_1 *)(*(int *)holder + 0x17a))->b)
        *(int *)(holder + 0x88) = 1;
    if (*(unsigned char *)(*(int *)(holder + 4) + 0xad) != 0) return;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
