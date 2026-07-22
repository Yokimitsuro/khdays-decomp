/* Waits for the sub OBJ extended palette upload DMA and restores the banks it had to release. */
extern void MI_WaitDma(int ch);
extern void GX_SetBankForSubOBJExtPltt(int mask);
extern int data_020422b8[];
extern int data_020446f0[];

void GXS_EndLoadOBJExtPltt(void) {
    if (data_020422b8[0] != -1) {
        MI_WaitDma(data_020422b8[0]);
    }
    GX_SetBankForSubOBJExtPltt(data_020446f0[6]);
    data_020446f0[6] = 0;
}
