/* Set bit0 of +0x1ae, clear bit0 of the +0x3a4->+8 byte, kick anim 5, arm the 0x166/7 timer with
 * +0x38, clear +0x28, clear bit0 of +0x3bc and dispatch 020d08b0. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov278_020d08b0(int);
struct b8 { unsigned f : 8; };
void func_ov278_020d0810(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(unsigned short *)(*(int *)owner + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*(int *)owner + 0x3a4) + 8))->f &= ~1;
    func_ov107_020c9264(*(int *)owner, 5, 0);
    func_ov107_020c5af8(*(int *)owner, 0x166, 7, *(int *)(owner + 0x38));
    *(int *)(owner + 0x28) = 0;
    *(unsigned char *)(*(int *)owner + 0x3bc) &= ~1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov278_020d08b0);
}
