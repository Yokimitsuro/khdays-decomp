extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

/* Spins until the channel's DMA has finished, then rearms channel 0's fill parameters. */
void MI_WaitDma(unsigned int channel) {
    int enabled = OS_DisableInterrupts();
    volatile unsigned int *ctrl = &((volatile unsigned int *)0x040000b0)[channel * 3 + 2];
    while ((*ctrl & 0x80000000) != 0) {
    }
    if (channel == 0) {
        volatile unsigned int *reg = (volatile unsigned int *)(0x040000b0 + channel * 12);
        reg[0] = 0;
        reg[1] = 0;
        reg[2] = 0x81400001;
    }
    OS_RestoreInterrupts(enabled);
}
