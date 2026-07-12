/* For sub-state 1, build a transform in a local via 0202ed60 (from const data_02042258 and
 * *(child)+0x390) and drive the pose via func_0203c9d0. Then copy the child's +8 vector into
 * *(child)+0xf0. */
struct w3 { int a, b, c; };
struct w4 { int a, b, c, d; };
extern void func_0202ed60(struct w4 *out, const void *in, int p);
extern void func_0203c9d0(int a, struct w4 *b);
extern const struct w4 data_02042258;
void func_ov232_020d3098(int param_1) {
    int child = *(int *)(param_1 + 4);
    struct w4 local;
    if (*(signed char *)(*(int *)child + 0x1c6) == 1) {
        func_0202ed60(&local, &data_02042258, *(int *)child + 0x390);
        func_0203c9d0(*(int *)child + 0xa0, &local);
    }
    *(struct w3 *)(*(int *)child + 0xf0) = *(struct w3 *)(child + 8);
}
