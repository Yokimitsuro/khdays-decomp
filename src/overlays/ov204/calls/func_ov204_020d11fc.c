struct w3 { int a, b, c; };
struct b1 { unsigned char b : 1; };
extern void func_01ffa724(int factor, void *src, void *dst);
extern void func_0203c634();

void func_ov204_020d11fc(int this_) {
    int holder = *(int *)(this_ + 4);
    void *src = (void *)(holder + 0x14);
    *(struct w3 *)(holder + 8) = *(struct w3 *)src;
    func_01ffa724(0xb00, src, src);
    if (*(unsigned char *)*(int *)(holder + 0x28) != 0) return;
    {
        int node = *(int *)holder;
        if (((struct b1 *)(node + 0x17a))->b || ((struct b1 *)(node + 0x17c))->b) {
            *(signed char *)(node + 0x1c7) = 2;
            func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
        }
    }
}
