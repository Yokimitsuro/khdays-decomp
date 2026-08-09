extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void OS_ResetRequestIrqMask(unsigned int mask);
extern void OS_SetIrqFunction(unsigned int mask, void *fn);
extern void OS_EnableIrqMask(unsigned int mask);
extern void PXIi_HandlerRecvFifoNotEmpty(void);
extern unsigned short data_02046284;
extern void *data_02046288[];

/* Brings the PXI FIFO up and handshakes with the ARM7 over IPCSYNC: bounce the low nibble back on
 * the high nibble and require it to hold steady five rounds running. */
void PXI_InitFifo(void) {
    int enabled = OS_DisableInterrupts();
    volatile unsigned short *sync = (volatile unsigned short *)0x04000180;
    int *shared = (int *)0x027ffc00;
    int i;
    int timeout;
    int mark;
    int count;
    if (data_02046284 == 0) {
        data_02046284 = 1;
        shared[0xe2] = 0;
        for (i = 0; i < 0x20; i++) {
            data_02046288[i] = 0;
        }
        *(volatile unsigned short *)0x04000184 = 0xc408;
        OS_ResetRequestIrqMask(0x40000);
        OS_SetIrqFunction(0x40000, (void *)&PXIi_HandlerRecvFifoNotEmpty);
        OS_EnableIrqMask(0x40000);
        count = 0;
        for (;;) {
            mark = *sync & 0xf;
            *sync = (unsigned short)(mark << 8);
            if (mark == 0 && count > 4) {
                break;
            }
            timeout = 1000;
            while ((*sync & 0xf) == mark) {
                if (timeout <= 0) {
                    count = 0;
                    break;
                }
                timeout--;
            }
            count++;
            }
    }
    OS_RestoreInterrupts(enabled);
}
