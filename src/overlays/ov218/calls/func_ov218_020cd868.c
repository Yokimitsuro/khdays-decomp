struct w3 { int a, b, c; };
extern void func_01ffa724(int factor, void *src, void *dst);
extern void func_0203c634();

void func_ov218_020cd868(int this_) {
    int holder = *(int *)(this_ + 4);
    void *src = (void *)(holder + 0x34);
    *(struct w3 *)(holder + 0x28) = *(struct w3 *)src;
    func_01ffa724(0xb00, src, src);
    if (*(unsigned char *)(*(int *)(holder + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)holder + 0x1c7) = 8;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
