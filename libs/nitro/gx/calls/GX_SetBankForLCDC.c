/* Marks the banks as LCDC-mapped in the shadow word and applies the VRAMCNT change. */
extern void *GX_VRAMCNT_SetLCDC_();
extern unsigned short data_020446d4;

void *GX_SetBankForLCDC(int bank) {
    data_020446d4 = (unsigned short)(data_020446d4 | bank);
    return GX_VRAMCNT_SetLCDC_(bank);
}
