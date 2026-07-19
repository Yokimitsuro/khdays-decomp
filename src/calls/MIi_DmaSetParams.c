extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

/* Programs one DMA channel's source, destination and control words atomically. */
void MIi_DmaSetParams(int channel, unsigned int src, unsigned int dst, unsigned int ctrl) {
    int enabled = OS_DisableInterrupts();
    volatile unsigned int *reg = (volatile unsigned int *)(0x040000b0 + channel * 12);
    reg[0] = src;
    reg[1] = dst;
    reg[2] = ctrl;
    OS_RestoreInterrupts(enabled);
}
