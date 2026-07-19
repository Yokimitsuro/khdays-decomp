extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_01ff8664(unsigned int channel, void *src, void *dest, unsigned int ctrl);

/* Fills memory with a 32-bit pattern through DMA, waiting for the channel both before and after. */
void MI_DmaFill32(unsigned int channel, void *dest, unsigned int data, unsigned int size) {
    volatile unsigned int *ctrl;
    int enabled;
    if (size == 0) {
        return;
    }
    ctrl = &((volatile unsigned int *)0x040000b0)[channel * 3 + 2];
    while ((*ctrl & 0x80000000) != 0) {
    }
    enabled = OS_DisableInterrupts();
    *(volatile unsigned int *)(0x040000e0 + channel * 4) = data;
    func_01ff8664(channel, (void *)(0x040000e0 + channel * 4), dest,
                  (size >> 2) | 0x85000000);
    OS_RestoreInterrupts(enabled);
    while ((*ctrl & 0x80000000) != 0) {
    }
}
