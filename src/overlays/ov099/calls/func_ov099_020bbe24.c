extern int func_02030788();
extern int func_ov022_020a35f4();

int func_ov099_020bbe24(int *r0, int r1)
{
    int *r6 = r0;
    int r5 = r1;
    int *r4 = (int *)r6[0xdb4 / 4];

    if (func_02030788() == 0) {
        *(long long *)((char *)r4 + 0x464) |= 0x10000;
    }
    *(long long *)((char *)r4 + 0x46c) |= 0x10000;
    r6[1] = 0;
    r6[0] = r5;
    if (r5 != 0) {
        return func_ov022_020a35f4(r4, 0x23);
    }
    return func_ov022_020a35f4(r4, 0x22);
}
