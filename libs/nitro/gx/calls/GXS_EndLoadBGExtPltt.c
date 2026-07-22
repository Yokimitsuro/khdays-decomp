/* Waits for the sub BG extended-palette upload DMA and restores the released banks. */
extern void MI_WaitDma(int ch);
extern void GX_SetBankForSubBGExtPltt(int mask);
extern int data_020422b8[];
extern int data_020446f0[];

void GXS_EndLoadBGExtPltt(void) {
    if (data_020422b8[0] != -1) {
        MI_WaitDma(data_020422b8[0]);
    }
    GX_SetBankForSubBGExtPltt(data_020446f0[0]);
    data_020446f0[0] = 0;
}
