/* Build the child's +0xc transform via 0202f55c, drive the pose via func_0203c9d0, copy the
 * child's +0x30 vector into *(child)+0xf0, then reseed +0x30 from the constant data_02041dc8. */
struct w3 { int a, b, c; };
extern void func_0202f55c(int a, int b, int c, int d);
extern void func_0203c9d0(int a, int b);
extern const struct w3 data_02041dc8;
void func_ov119_020cd0f0(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_0202f55c(child + 0xc, *(int *)(child + 0x2c), child + 0xc, child + 0x1c);
    func_0203c9d0(*(int *)child + 0xa0, child + 0xc);
    {
        struct w3 *p30 = (struct w3 *)(child + 0x30);
        *(struct w3 *)(*(int *)child + 0xf0) = *p30;
        *p30 = data_02041dc8;
    }
}
