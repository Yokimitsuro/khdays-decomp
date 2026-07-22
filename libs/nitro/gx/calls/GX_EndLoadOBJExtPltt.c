/* Waits for the main OBJ extended palette upload DMA and restores the banks it had to release. */
extern void MI_WaitDma(int ch);
extern void GX_SetBankForOBJExtPltt(int mask);
extern int data_020422b8[];
extern int data_020446f0[];

void GX_EndLoadOBJExtPltt(void) {
    if (data_020422b8[0] != -1) {
        MI_WaitDma(data_020422b8[0]);
    }
    GX_SetBankForOBJExtPltt(data_020446f0[2]);
    data_020446f0[2] = 0;
    data_020446f0[1] = 0;
}
