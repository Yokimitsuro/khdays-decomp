extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int);

void func_01ff85d0(unsigned int dmaNo, unsigned int src, unsigned int dest, unsigned int ctrl) {
    int mask = OS_DisableInterrupts();
    volatile unsigned int *p = (volatile unsigned int *)(0x040000B0 + dmaNo * 12);
    *p = (volatile unsigned int)src;
    *(p + 1) = (volatile unsigned int)dest;
    *(p + 2) = (volatile unsigned int)ctrl;
    (void)*(volatile unsigned int *)0x040000B0;
    (void)*(volatile unsigned int *)0x040000B0;
    if (dmaNo == 0) {
        *p = 0;
        *(p + 1) = 0;
        *(p + 2) = 0x81400001;
    }
    OS_RestoreInterrupts(mask);
}
