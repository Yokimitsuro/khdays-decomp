/* Notify 020cd794, latch +0x68->+0x64, kick anim 0x12, restart sub-anim 020c9ee8, arm 020cd148
 * with +0x10, clear +0x79 and set +0x78=-1, then dispatch 020ce2f0. */
extern int func_ov260_020cd794(int);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_ov260_020cd148(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov260_020ce2f0(int);
void func_ov260_020ce27c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov260_020cd794(param_1);
    *(int *)(owner + 0x64) = *(int *)(owner + 0x68);
    func_ov107_020c9264(*(int *)owner, 0x12, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x428), 8, 0);
    func_ov260_020cd148(*(int *)owner, 0x18, *(int *)(owner + 0x10));
    *(unsigned char *)(owner + 0x79) = 0;
    *(signed char *)(owner + 0x78) = -1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov260_020ce2f0);
}
