struct w3 { int a, b, c; };
struct b1 { unsigned char b : 1; };
extern void func_01ffa724(int factor, void *src, void *dst);
extern int VEC_Mag(void *v);
extern void func_0203c634();

void func_ov293_020d2bfc(int this_) {
    int holder = *(int *)(this_ + 4);
    void *src = (void *)(holder + 0x34);
    *(struct w3 *)(holder + 0x1c) = *(struct w3 *)src;
    func_01ffa724(0xa00, src, src);
    if (*(unsigned char *)*(int *)(holder + 0x4c) != 0) return;
    {
        int node = *(int *)holder;
        if (!(((struct b1 *)(node + 0x17a))->b || ((struct b1 *)(node + 0x17c))->b)) return;
    }
    if (VEC_Mag((void *)(holder + 0x34)) > 0x10) return;
    *(signed char *)(*(int *)holder + 0x1c7) = 4;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
