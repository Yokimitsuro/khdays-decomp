/* Waits for the texture palette upload DMA and restores the banks it had to release. */
extern void MI_WaitDma(int ch);
extern void GX_BeginLoadOBJExtPltt(int mask);
extern int data_020422b8[];
extern int data_0204470c[];

void GX_EndLoadTexPltt(void) {
    if (data_020422b8[0] != -1) {
        MI_WaitDma(data_020422b8[0]);
    }
    GX_BeginLoadOBJExtPltt(data_0204470c[3]);
    data_0204470c[3] = 0;
    data_0204470c[2] = 0;
}
