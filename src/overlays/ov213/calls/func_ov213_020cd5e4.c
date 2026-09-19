/* Build the child's +0x28 transform via 0202f55c, drive the pose via func_0203c9d0, count the
 * +0x6c timer down by the owner rate while positive, copy the child's +0xc vector into
 * *(child)+0xf0 and reseed +0xc from the constant data_02041dc8. */
struct w3 { int a, b, c; };
extern void func_0202f55c(int a, int b, int c, int d);
extern void func_0203c9d0(int a, int b);
extern const struct w3 data_02041dc8;
void func_ov213_020cd5e4(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(int *)(child + 0x6c) > 0)
        *(int *)(child + 0x6c) -= *(int *)(*(int *)param_1 + 0x2c);
    func_0202f55c(child + 0x28, *(int *)(child + 0x48), child + 0x28, child + 0x38);
    func_0203c9d0(*(int *)child + 0xa0, child + 0x28);
    {
        struct w3 *pc = (struct w3 *)(child + 0xc);
        *(struct w3 *)(*(int *)child + 0xf0) = *pc;
        *pc = data_02041dc8;
    }
}
