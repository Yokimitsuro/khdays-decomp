/* Enter the burst state: flag +0x4c, store angle/5 into +0x9c, clear +0x68/+0xac, flag the node's
 * +0x42c, kick anim 4, run 020cd524 and the 0x15/0x1e48 020cd628 pulse, then dispatch 020cf764. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov259_020cd524(int, int, int);
extern int func_ov259_020cd628(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov259_020cf764(int);
void func_ov259_020cf6d0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x4c) = 1;
    *(int *)(owner + 0x9c) = (short)*(short *)(*(int *)owner + 0x21a) / 5;
    *(int *)(owner + 0x68) = 0;
    *(unsigned char *)(owner + 0xac) = 0;
    *(int *)(*(int *)owner + 0x42c) = 1;
    func_ov107_020c9264(*(int *)owner, 4, 0);
    func_ov259_020cd524(param_1, 4, 0);
    func_ov259_020cd628(param_1, 0x15, 0x1e48);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov259_020cf764);
}
