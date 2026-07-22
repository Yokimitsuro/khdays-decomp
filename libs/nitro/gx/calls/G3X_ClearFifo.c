/* Flushes the geometry FIFO with 128 NOP commands and waits for the engine to go idle. */
extern void GXi_NopClearFifo128_(volatile unsigned int *fifo);

void G3X_ClearFifo(void) {
    GXi_NopClearFifo128_((volatile unsigned int *)0x4000400);
    while (*(volatile unsigned int *)0x4000600 & 0x8000000) {
        ;
    }
}
