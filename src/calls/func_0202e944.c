extern int SNDi_UnlockMutex_0x020063f8();
extern int SNDi_UnlockMutex_0x020063e4();
extern int GX_SetBankForTex(int);
extern int GX_SetBankForSubBG(int);
extern int GX_SetBankForSubOBJ(int);
extern int GXS_SetGraphicsMode(int);
extern void func_020056b4(int a, int b, int c);
extern int func_02010f08(void);
extern int func_02010e80(int a, int b);
extern int func_02023c30(int a);

extern char data_0204c214[];

/* Bring up the sub 2D engine: assign VRAM banks, set DISPCNT-B (mode + BG ext-pal),
 * enable POWCNT1 top/bottom swap (bit15), select graphics mode 3, then hand off. */
void func_0202e944(void) {
    SNDi_UnlockMutex_0x020063f8();
    SNDi_UnlockMutex_0x020063e4();
    GX_SetBankForTex(7);
    GX_SetBankForSubBG(6 << 6);
    GX_SetBankForSubOBJ(8);
    {
        volatile unsigned int *reg_dispcnt_b = (volatile unsigned int *)0x04001000;
        *reg_dispcnt_b = (*reg_dispcnt_b & 0xffcfffef) | 0x00200010;
    }
    func_020056b4(1, 0, 1);
    GXS_SetGraphicsMode(3);
    {
        volatile unsigned short *reg_powcnt1 = (volatile unsigned short *)0x04000304;
        *reg_powcnt1 = *reg_powcnt1 | 0x8000;
    }
    func_02010f08();
    func_02010e80(3, 1);
    func_02023c30(0);
    *data_0204c214 = 1;
}
