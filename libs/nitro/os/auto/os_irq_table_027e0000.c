/* NitroSDK os_irqTable.c / os_irqHandler.c: the ARM9 interrupt handler table and the thread queue
 * of OS_WaitIrq, both in DTCM .data (0x027e0000-0x027e0060).  Every IRQ source starts on
 * OS_IrqDummy (func_02001138) except the four timers and the four DMA channels, whose SDK
 * handlers dispatch the per-channel callbacks. */

typedef void (*OSIrqFunction)(void);

typedef struct OSThreadQueue {
    struct OSThread *head;
    struct OSThread *tail;
} OSThreadQueue;

#define OS_IRQ_TABLE_MAX 22

extern void func_02001138(void);  /* OS_IrqDummy */
extern void OSi_IrqTimer0(void);
extern void OSi_IrqTimer1(void);
extern void OSi_IrqTimer2(void);
extern void OSi_IrqTimer3(void);
extern void OSi_IrqDma0(void);
extern void OSi_IrqDma1(void);
extern void OSi_IrqDma2(void);
extern void OSi_IrqDma3(void);

/* OS_IRQTable */
OSIrqFunction data_027e0000[OS_IRQ_TABLE_MAX] = {
    func_02001138,  /* VBlank */
    func_02001138,  /* HBlank */
    func_02001138,  /* VCounter */
    OSi_IrqTimer0,  /* timer 0 */
    OSi_IrqTimer1,  /* timer 1 */
    OSi_IrqTimer2,  /* timer 2 */
    OSi_IrqTimer3,  /* timer 3 */
    func_02001138,  /* serial communication */
    OSi_IrqDma0,    /* DMA 0 */
    OSi_IrqDma1,    /* DMA 1 */
    OSi_IrqDma2,    /* DMA 2 */
    OSi_IrqDma3,    /* DMA 3 */
    func_02001138,  /* key */
    func_02001138,  /* cartridge */
    func_02001138,  /* (not used) */
    func_02001138,  /* (not used) */
    func_02001138,  /* IPC sync */
    func_02001138,  /* IPC FIFO send */
    func_02001138,  /* IPC FIFO receive */
    func_02001138,  /* card data */
    func_02001138,  /* card IREQ */
    func_02001138,  /* geometry command FIFO */
};

/* OSi_IrqThreadQueue: threads sleeping in OS_WaitIrq (empty). */
#pragma explicit_zero_data on
OSThreadQueue data_027e0058 = { 0, 0 };
#pragma explicit_zero_data off
