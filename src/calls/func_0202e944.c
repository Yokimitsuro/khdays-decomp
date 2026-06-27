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

void func_0202e944(void) {
    SNDi_UnlockMutex_0x020063f8();
    SNDi_UnlockMutex_0x020063e4();
    GX_SetBankForTex(7);
    GX_SetBankForSubBG(6 << 6);
    GX_SetBankForSubOBJ(8);
    *(volatile unsigned int *)0x4001000 =
        (*(volatile unsigned int *)0x4001000 & 0xffcfffef) | 0x00200010;
    func_020056b4(1, 0, 1);
    GXS_SetGraphicsMode(3);
    *(volatile unsigned short *)0x4000304 =
        *(volatile unsigned short *)0x4000304 | (0x4000304 >> 11);
    func_02010f08();
    func_02010e80(3, 1);
    func_02023c30(0);
    *data_0204c214 = 1;
}
