/* Poll func_ov223_020d1240: on failure dispatch, otherwise advance +0x5c and once it passes 0x1650 (once only)
 * fire the 0x149/0xc effect; then unless busy latch sub-state 4 and dispatch. */
extern int func_ov223_020d1240(int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov107_020c5af8(int, int, int, int);
void func_ov223_020d3918(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov223_020d1240(param_1, 0) < 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
        return;
    }
    *(int *)(owner + 0x5c) += *(int *)(*(int *)param_1 + 0x2c);
    if ((*(unsigned char *)(owner + 0x75) & 2) == 0) {
        if (*(int *)(owner + 0x5c) >= 0x1650) {
            func_ov107_020c5af8(*(int *)owner, 0x149, 0xc, *(int *)(owner + 8));
            *(unsigned char *)(owner + 0x75) |= 2;
        }
    }
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(unsigned char *)(*(int *)owner + 0x1c7) = 4;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
