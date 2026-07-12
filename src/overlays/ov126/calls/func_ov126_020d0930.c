/* Build the child's +0x58 transform via 0202f55c, drive the pose via func_0203c9d0, count the
 * +0x54 timer down by the owner rate while positive, copy the child's +8 vector into
 * *(child)+0xf0 and reseed +8 from the constant data_02041dc8. */
struct w3 { int a, b, c; };
extern void func_0202f55c(int a, int b, int c, int d);
extern void func_0203c9d0(int a, int b);
extern const struct w3 data_02041dc8;
void func_ov126_020d0930(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_0202f55c(child + 0x58, *(int *)(child + 0x3c), child + 0x58, child + 0x68);
    func_0203c9d0(*(int *)child + 0xa0, child + 0x58);
    if (*(int *)(child + 0x54) > 0)
        *(int *)(child + 0x54) -= *(int *)(*(int *)param_1 + 0x2c);
    {
        struct w3 *p8 = (struct w3 *)(child + 8);
        *(struct w3 *)(*(int *)child + 0xf0) = *p8;
        *p8 = data_02041dc8;
    }
}
