/* Notify 020cd128, advance +0x44 by the frame delta; once it passes 0x3850 (once only) fire the
 * 0x16d/6 effect; then unless busy kick anim 0x14, retire the +0x468 node, clear +0x40 and dispatch. */
extern int func_ov254_020cd128(int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov254_020d4164(int);
extern int func_0203c634(int, int, void *);
extern int func_ov254_020d0b84(int);
void func_ov254_020d0ad4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov254_020cd128(param_1);
    *(int *)(owner + 0x44) += *(int *)(*(int *)param_1 + 0x2c);
    int f = *(unsigned char *)(owner + 0x70);
    if ((f & 1) == 0) {
        if (*(int *)(owner + 0x44) >= 0x3850) {
            *(unsigned char *)(owner + 0x70) = f | 1;
            func_ov107_020c5af8(*(int *)owner, 0x16d, 6, *(int *)(owner + 8));
        }
    }
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 0x14, 0);
    func_ov254_020d4164(*(int *)(*(int *)owner + 0x468));
    *(int *)(owner + 0x40) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov254_020d0b84);
}
