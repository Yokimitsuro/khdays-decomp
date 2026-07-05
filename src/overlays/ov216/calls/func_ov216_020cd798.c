extern int func_ov107_020cab14(int node, int flag);
extern int func_0203c634();
extern int VEC_Subtract();
extern int func_01ff8d18();
extern int func_020050b4();
extern int func_ov216_020cd0f8(int this_, int x);

void func_ov216_020cd798(int this_) {
    int holder = *(int *)(this_ + 4);
    int local[3];
    int r;
    int r4;

    r = func_ov107_020cab14(*(int *)holder, 0);
    *(int *)(holder + 8) = r;
    if (r == 0) {
        *(signed char *)(*(int *)holder + 0x1c7) = 2;
        func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
        return;
    }

    VEC_Subtract(r + 0x190, *(int *)holder + 0xb0, local);
    r4 = func_01ff8d18(local, local);
    *(int *)(holder + 0x4c) = func_020050b4(local[0], local[2]);

    if (func_ov216_020cd0f8(this_, r4) != 0) {
        func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
        return;
    }
    *(signed char *)(*(int *)holder + 0x1c7) = 4;
}
