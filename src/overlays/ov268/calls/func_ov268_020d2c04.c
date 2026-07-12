/* Kick anim 0xd, clear the 0x40 bit of the hw60 hi byte, arm the 0x15f/0xb timer with +0xc,
 * clear +0x4e/+0x2c and dispatch 020d2c88. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov268_020d2c88(int);
struct hw60 { unsigned short lo : 8, hi : 8; };
void func_ov268_020d2c04(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0xd, 1);
    ((struct hw60 *)(*(int *)owner + 0x60))->hi &= ~0x40;
    func_ov107_020c5af8(*(int *)owner, 0x15f, 0xb, *(int *)(owner + 0xc));
    *(unsigned char *)(owner + 0x4e) = 0;
    *(int *)(owner + 0x2c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov268_020d2c88);
}
