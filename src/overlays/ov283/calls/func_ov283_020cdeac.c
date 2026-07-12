/* Unless busy, fire effect 0x173 on the linked node, kick anim 9, clear the +0x68/+0x6c/+0x48/
 * +0x74 block and dispatch 020cdf1c. */
extern int func_ov283_020cc92c(int, int, int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov283_020cdf1c(int);
void func_ov283_020cdeac(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov283_020cc92c(*(int *)owner, 0x173, 7, *(int *)(owner + 8));
    func_ov107_020c9264(*(int *)owner, 9, 0);
    *(int *)(owner + 0x68) = 0;
    *(int *)(owner + 0x6c) = 0;
    *(int *)(owner + 0x48) = 0;
    *(int *)(owner + 0x74) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov283_020cdf1c);
}
