/* Advance +0x68 by the frame delta; when the +0x21a gauge has drained set +0x1ae bits0-1; once
 * +0x68 passes 0xaa0 (and +0xac bit1 is clear) set it and notify 020cd2c8; then unless busy anim 6. */
extern int func_ov259_020cdcac(int);
extern int func_ov259_020cd2c8(int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov259_020cfd90(int);
void func_ov259_020cfce4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov259_020cdcac(param_1);
    *(int *)(owner + 0x68) += *(int *)(*(int *)param_1 + 0x2c);
    if ((short)*(short *)(*(int *)owner + 0x21a) <= 0) {
        *(unsigned short *)(*(int *)owner + 0x1ae) |= 3;
    }
    int f = *(unsigned char *)(owner + 0xac);
    if ((f & 2) == 0) {
        if (*(int *)(owner + 0x68) >= 0xaa0) {
            *(unsigned char *)(owner + 0xac) = f | 2;
            func_ov259_020cd2c8(*(int *)owner, 3);
        }
    }
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 6, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov259_020cfd90);
}
