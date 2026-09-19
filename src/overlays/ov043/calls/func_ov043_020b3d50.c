/* Enters state 0x21 of the mission enemy: raises bit 16 of both 64-bit flag words (+0x464,
 * +0x46c) on the local player's session, resets the mission owner's +0x2d38 block speed (+0xc)
 * to 0x50a -- scaled by 1.5 on difficulty 1 -- and its +0x128 duration to 0x1e6 (0x144
 * otherwise), then runs the shared state entry. */
extern int func_02030788(void);
extern int func_02023c40(void);
extern int func_ov022_020a35f4(int *self, int state);
extern int data_ov043_020b58e0;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

int func_ov043_020b3d50(int *self) {
    int *blk = (int *)(*(int *)&data_ov043_020b58e0 + 0x138 + 0x2c00);
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x46c) |= 0x10000;
    }
    blk[3] = 0x50a;
    if (func_02023c40() == 1) {
        blk[3] = FX_Mul(blk[3], 0x1800);
    }
    blk[0x4a] = (func_02023c40() == 1) ? 0x1e6 : 0x144;
    return func_ov022_020a35f4(self, 0x21);
}
