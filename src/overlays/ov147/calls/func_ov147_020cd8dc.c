struct w3 { int a, b, c; };
extern void func_01ffa724(int factor, void *src, void *dst);
extern void func_0203c634();

void func_ov147_020cd8dc(int this_) {
    int holder = *(int *)(this_ + 4);
    void *src = (void *)(holder + 0x1c);
    *(struct w3 *)(holder + 0x10) = *(struct w3 *)src;
    func_01ffa724(0xb00, src, src);
    if (*(unsigned char *)(*(int *)(holder + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)holder + 0x1c7) = 2;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
