extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int);

void MIi_DmaSetParams(unsigned int dmaNo, unsigned int src, unsigned int dest, unsigned int ctrl) {
    int mask = OS_DisableInterrupts();
    volatile unsigned int *p = (volatile unsigned int *)(0x040000B0 + dmaNo * 12);
    *p = (volatile unsigned int)src;
    *(p + 1) = (volatile unsigned int)dest;
    *(p + 2) = (volatile unsigned int)ctrl;
    OS_RestoreInterrupts(mask);
}
