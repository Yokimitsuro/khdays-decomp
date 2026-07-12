/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x28. Once it passes 0x4e80 and
 * the +0x51 latch is set, clear the latch and set bit 0 of the u16 at *(child)+0x1ae. Then,
 * only once the timer reaches 0x5000, play the anim (ov107 mode 0x12) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov236_020d133c(int);
void func_ov236_020d12b0(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x28) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x28) = t;
    if (t >= 0x4e80 && *(unsigned char *)(child + 0x51) == 1) {
        *(signed char *)(child + 0x51) = 0;
        *(unsigned short *)(*(int *)child + 0x1ae) |= 1;
    }
    if (*(int *)(child + 0x28) < 0x5000) return;
    func_ov107_020c9264(*(int *)child, 0x12, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov236_020d133c);
}
