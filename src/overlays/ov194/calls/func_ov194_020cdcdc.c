/* Reset an enemy's melee-reaction AI state: cancel the current reaction (func_ov107_020c9264 mode
 * 9), clear the timers/flags, decrement the cooldown if positive, pick a fresh reaction bias
 * (3 one time in four, else 1), and re-register the per-frame think callback.
 *
 * The `+ (v - v)` term is the documented copy artifact for func_02023eb4's 64-bit return
 * (K&R extern), which the ROM tests with `adds r0,r0,#0`. */
extern int func_02023eb4();
extern void func_ov107_020c9264(int owner, int mode, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov194_020cdd54(void);

void func_ov194_020cdcdc(int param_1, int param_2, int param_3, int param_4) {
    int v;
    int *node = *(int **)(param_1 + 4);
    func_ov107_020c9264(*node, 9, 0);
    *(unsigned char *)((char *)node + 0x50) = 0;
    *(int *)((char *)node + 0x30) = 0;
    if (*(int *)((char *)node + 0x44) > 0) {
        *(int *)((char *)node + 0x44) = *(int *)((char *)node + 0x44) - 1;
    }
    *(int *)((char *)node + 0x4c) = (func_02023eb4(4) + (v - v) == 0) ? 3 : 1;
    *(unsigned char *)((char *)node + 0x51) = 0;
    *(unsigned char *)((char *)node + 0x53) = 0;
    *(int *)((char *)node + 0x54) = 0;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov194_020cdd54);
}
