/* Build a transform in a local from const data_02042264 and the child's +0xc, then drive the
 * pose via func_0203c9d0. */
struct w4 { int a, b, c, d; };
extern void func_0202ed60(struct w4 *out, const void *in, int p);
extern void func_0203c9d0(int a, struct w4 *b);
extern const struct w4 data_02042264;
void func_ov254_020d4778(int param_1) {
    int child = *(int *)(param_1 + 4);
    struct w4 local;
    func_0202ed60(&local, &data_02042264, child + 0xc);
    func_0203c9d0(*(int *)child + 0xa0, &local);
}
