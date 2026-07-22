/* Waits for the main BG extended-palette upload DMA and restores the released banks. */
extern void MI_WaitDma(int ch);
extern void GX_SetBankForBGExtPltt(int mask);
extern int data_020422b8[];
extern int data_020446f0[];

void GX_EndLoadBGExtPltt(void) {
    if (data_020422b8[0] != -1) {
        MI_WaitDma(data_020422b8[0]);
    }
    GX_SetBankForBGExtPltt(data_020446f0[5]);
    data_020446f0[5] = 0;
    data_020446f0[4] = 0;
    data_020446f0[3] = 0;
}
