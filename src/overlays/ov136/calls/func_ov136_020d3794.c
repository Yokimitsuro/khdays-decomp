struct b1 { unsigned char b : 1; };
extern void func_0203c634();

void func_ov136_020d3794(int this_) {
    int holder = *(int *)(this_ + 4);
    int node = *(int *)holder;
    if (((struct b1 *)(node + 0x17a))->b == 0) return;
    if (((struct b1 *)(holder + 0x42))->b) {
        *(signed char *)(node + 0x1c7) = 4;
        func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
    } else {
        *(signed char *)(node + 0x1c7) = 2;
        func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
    }
}
