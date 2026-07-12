/* Allocate a 0x3f8-byte object, link owner (+0x3dc), install callback (+0x18c), init, seed the
 * +0x3d0 vector from const data_02041dc8 and nudge its x by -/+0x2000 for arg 0/2. Return it. */
struct w3 { int a, b, c; };
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov245_020cf2f0(int);
extern const struct w3 data_02041dc8;
int func_ov245_020cf284(int param_1, int param_2) {
    int obj = func_0203d15c(0x3f8);
    *(int *)(obj + 0x3dc) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov245_020cf2f0;
    func_ov107_020c6624(obj, 0);
    *(struct w3 *)(obj + 0x3d0) = data_02041dc8;
    if (param_2 == 0) *(int *)(obj + 0x3d0) -= 0x2000;
    if (param_2 == 2) *(int *)(obj + 0x3d0) += 0x2000;
    return obj;
}
