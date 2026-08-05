/*
 * func_ov002_0207c020 - queue a "first touch" input record for an idle object (ARM).
 *
 * Only acts while the object is idle (both the pending flag param_1[0x2c1] and the touch counter
 * param_1[0x2c0] are 0). It builds a small event record { kind=1, code=param_2[0] } on the stack and
 * submits it through func_ov002_020766e0 (tag 6). On a successful submit it bumps the touch counter
 * and raises the pending flag. Always returns 0; the two idle-guard/submit-fail exits share one
 * return so mwcc branches to a single tail as the ROM does.
 */
extern int func_ov002_020766e0(int a, int b, int c);

int func_ov002_0207c020(int param_1, unsigned char *param_2)
{
    unsigned char local[8];
    if (*(unsigned char *)(param_1 + 0x2c1) != 0 || *(unsigned char *)(param_1 + 0x2c0) != 0)
        goto ret0;
    local[0] = 1;
    local[4] = param_2[0];
    if (func_ov002_020766e0(param_1, (int)local, 6) == 0)
        goto ret0;
    *(unsigned char *)(param_1 + 0x2c0) = *(unsigned char *)(param_1 + 0x2c0) + 1;
    *(unsigned char *)(param_1 + 0x2c1) = 1;
    return 0;
ret0:
    return 0;
}
