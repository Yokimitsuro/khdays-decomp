/* Thin forwarder: push a caller-supplied vector to the owner (*param_1) via
 * func_ov107_020c0b90 with mode 0 / flag 0. */
struct vec { int x, y, z; };
extern void func_ov107_020c0b90(int owner, int mode, struct vec v, int flag);
void func_ov222_020d62b8(int *param_1, struct vec v) {
    func_ov107_020c0b90(*param_1, 0, v, 0);
}
