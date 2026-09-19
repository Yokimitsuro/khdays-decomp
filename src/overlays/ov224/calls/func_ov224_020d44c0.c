/* Thin forwarder: push a caller-supplied vector to the owner (*state) via ov107 c0b90 with
 * mode 0; the flag is set when the caller passes a zero fourth argument. */
struct vec { int x, y, z; };
extern void func_ov107_020c0b90(int owner, int mode, struct vec v, unsigned char flag);
void func_ov224_020d44c0(int *state, struct vec v, int bTarget) {
    func_ov107_020c0b90(*state, 0, v, bTarget == 0 ? 1 : 0);
}
