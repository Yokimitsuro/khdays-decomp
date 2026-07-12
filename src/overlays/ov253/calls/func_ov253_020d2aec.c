/* Unless the parent's +0x454 is busy, drain +0x3ec by the frame delta; once it hits 0 with +0x3d0
 * clear and 020d26c8 accepting, store the 020d26e0 result into +0x20 and dispatch. */
extern int func_ov253_020d26c8(int);
extern int func_ov253_020d26e0(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020d2b74(int);
void func_ov253_020d2aec(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int obj = *(int *)owner;
    if (*(int *)(*(int *)(obj + 0x388) + 0x454) != 0) return;
    *(int *)(obj + 0x3ec) = *(int *)(obj + 0x3ec) - *(int *)(*(int *)param_1 + 0x2c);
    if (*(int *)(*(int *)owner + 0x3ec) > 0) return;
    if (*(int *)(*(int *)owner + 0x3d0) != 0) return;
    if (func_ov253_020d26c8(*(int *)owner) != 0) return;
    *(unsigned short *)(owner + 0x20) = func_ov253_020d26e0(*(int *)owner, 2, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d2b74);
}
