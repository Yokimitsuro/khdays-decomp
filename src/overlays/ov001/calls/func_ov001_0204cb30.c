extern int GX_SetBankForSubBG();
extern int GX_SetBankForSubOBJ();

void func_ov001_0204cb30(void) {
    volatile unsigned int *p;

    GX_SetBankForSubBG(0x180);
    GX_SetBankForSubOBJ(8);
    p = (volatile unsigned int *)0x04001000;
    *p = (*p & 0xffcfffefu) | 0x10u | 0x200000u;
}
