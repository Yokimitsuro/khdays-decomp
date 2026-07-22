/* Waits for the texture upload DMA and restores the released banks. */
extern void MI_WaitDma(int ch);
extern void GX_SetBankForTex(int mask);
extern int data_020422b8[];
extern int data_0204470c[];

void GX_EndLoadTex(void) {
    if (data_020422b8[0] != -1) {
        MI_WaitDma(data_020422b8[0]);
    }
    GX_SetBankForTex(data_0204470c[5]);
    data_0204470c[7] = 0;
    data_0204470c[6] = 0;
    data_0204470c[1] = 0;
    data_0204470c[5] = 0;
}
