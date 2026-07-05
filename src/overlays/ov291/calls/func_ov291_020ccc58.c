struct hw60 { unsigned short lo : 8, hi : 8; };
struct sb2 { int pad : 2; int b : 1; };
extern void func_0203c634();

void func_ov291_020ccc58(int this_) {
    int holder = *(int *)(this_ + 4);
    if ((((struct hw60 *)(*(int *)holder + 0x60))->lo & 1) == 0) return;
    *(int *)(holder + 0x24) = 0;
    *(int *)(holder + 0x2c) = 0;
    {
        int node = *(int *)holder;
        void (*cb)(int, int);
        if (((struct sb2 *)(node + 0x40))->b && (cb = *(void (**)(int, int))(node + 0x10)) != 0)
            cb(node, 1);
    }
    *(signed char *)(*(int *)holder + 0x1c7) = *(signed char *)(*(int *)holder + 0x1c9);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
