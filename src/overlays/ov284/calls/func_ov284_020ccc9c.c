/* Kick anim 3, set bit 0 of the +0x3a8 status byte, clear +0x1c/+0x24/+0x25, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
struct b8 { unsigned int f : 8; };
extern int func_ov284_020ccd08(int);
void func_ov284_020ccc9c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 3, 0);
    ((struct b8 *)(*(int *)(*(int *)owner + 0x3a8) + 8))->f |= 1;
    *(int *)(owner + 0x1c) = 0;
    *(signed char *)(owner + 0x24) = 0;
    *(signed char *)(owner + 0x25) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov284_020ccd08);
}
