struct w3 { int a, b, c; };
extern int func_0203c9d0(int dst, int src);
extern const struct w3 data_02041dc8;

void func_ov260_020d1d88(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_0203c9d0(*(int *)child + 0xa0, child + 8);
    {
        struct w3 *p = (struct w3 *)(child + 0x28);
        *(struct w3 *)(*(int *)child + 0xf0) = *p;
        *p = data_02041dc8;
    }
}
