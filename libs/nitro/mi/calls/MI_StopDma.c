extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

/* Clears the channel's trigger bits and its enable bit, then rearms channel 0's fill parameters.
 * The two dummy reads are the SDK's write-settle delay. */
void MI_StopDma(unsigned int channel) {
    int enabled = OS_DisableInterrupts();
    volatile unsigned short *ctrl = &((volatile unsigned short *)0x040000b0)[channel * 6 + 5];
    *ctrl &= ~0x3a00;
    *ctrl &= ~0x8000;
    *ctrl;
    *ctrl;
    if (channel == 0) {
        volatile unsigned int *reg = (volatile unsigned int *)(0x040000b0 + channel * 12);
        reg[0] = 0;
        reg[1] = 0;
        reg[2] = 0x81400001;
    }
    OS_RestoreInterrupts(enabled);
}
