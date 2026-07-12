/* Push the socket at obj+0x3e0+0x2c into 020d07f0; unless busy, tick down +0x2d, kick anim 1,
 * restart sub-anim 020c9ee8, set +0x31=2, clear +0x20 and dispatch 020d1594. */
extern int func_ov238_020d07f0(int, int);
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov238_020d1594(int);
void func_ov238_020d1510(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov238_020d07f0(param_1, *(int *)(*(int *)owner + 0x3e0) + 0x2c);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(unsigned char *)(owner + 0x2d) -= 1;
    func_ov107_020c9264(*(int *)owner, 1, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x3e0), 0, 0);
    *(unsigned char *)(owner + 0x31) = 2;
    *(int *)(owner + 0x20) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov238_020d1594);
}
