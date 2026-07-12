/* Notify 020d0878, advance +0x20 by the frame delta, emit three 020d0f0c pulses, then unless
 * busy latch sub-state 2 and dispatch. */
extern int func_ov238_020d0878(int);
extern int func_ov238_020d0f0c(int, int, int, int);
extern int func_0203c634(int, int, void *);
void func_ov238_020d17d0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov238_020d0878(param_1);
    *(int *)(owner + 0x20) += *(int *)(*(int *)param_1 + 0x2c);
    func_ov238_020d0f0c(param_1, 0x19, 2, 5);
    func_ov238_020d0f0c(param_1, 0xf, 3, 4);
    func_ov238_020d0f0c(param_1, 0x23, 1, 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(unsigned char *)(*(int *)owner + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
