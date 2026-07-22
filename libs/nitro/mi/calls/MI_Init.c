/* Boot-time MI setup: give all of WRAM to the ARM9 and stop DMA channel 0. */
extern void MI_SetWramBank(int bank);
extern void MI_StopDma(int ch);

void MI_Init(void) {
    MI_SetWramBank(3);
    MI_StopDma(0);
}
