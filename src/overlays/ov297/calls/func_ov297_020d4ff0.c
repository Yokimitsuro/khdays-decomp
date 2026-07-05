struct w3 { int a, b, c; };
extern void func_01ffa724(int factor, void *src, void *dst);
extern int func_02023e80(int p);
extern void func_0203c634();

void func_ov297_020d4ff0(int this_) {
    int holder = *(int *)(this_ + 4);
    void *src = (void *)(holder + 0x1c);
    *(struct w3 *)(holder + 0x10) = *(struct w3 *)src;
    *(int *)(holder + 0x14) = *(int *)(holder + 0x4c);
    *(int *)(holder + 0x4c) = *(int *)(holder + 0x4c) - 0x80;
    func_01ffa724(0xe00, src, src);
    if (*(unsigned char *)(*(int *)(holder + 4) + 0xad) != 0) return;
    *(int *)(holder + 0x28) = func_02023e80(0x1922) + 0x1922;
    *(signed char *)(*(int *)holder + 0x1c7) = 4;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
