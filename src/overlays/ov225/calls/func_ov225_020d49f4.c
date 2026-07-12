/* For sub-state 0, seed the child's +0x18 vector from the constant at data_02041dc8. Then copy
 * that vector into *(child)+0xf0 and drive the pose via func_0203c9d0. */
struct w3 { int a, b, c; };
extern const struct w3 data_02041dc8;
extern void func_0203c9d0(int a, int b);
void func_ov225_020d49f4(int param_1) {
    int child = *(int *)(param_1 + 4);
    switch (*(signed char *)(*(int *)child + 0x1c6)) {
    case 0: *(struct w3 *)(child + 0x18) = data_02041dc8; break;
    case 1: break;
    }
    *(struct w3 *)(*(int *)child + 0xf0) = *(struct w3 *)(child + 0x18);
    func_0203c9d0(*(int *)child + 0xa0, child + 0x30);
}
