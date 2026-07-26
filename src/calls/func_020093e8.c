/* func_020093e8 -- push one PXI packet onto the IPC FIFO to the ARM7.
 *
 * The NitroSDK PXI_SendWordByFifo: a 32-bit word made of a 5-bit tag, a 1-bit error
 * flag and 26 bits of payload, written to REG_IPCFIFOSEND with interrupts masked.
 * Returns 0 on success, -1 if the FIFO reports an error (which it also acknowledges
 * and re-enables), -2 if the send queue is full.
 *
 * The `ldr ip,[sp]` right after the prologue is not a spill being reloaded -- it is the
 * read half of a read-modify-write on an UNINITIALISED local. That is what three bitfield
 * assignments compile to, and it is the reason the packet must be a bitfield struct
 * rather than shifts and masks: hand-rolled `(tag & 0x1f) | (err << 5) | (data << 6)`
 * never touches the stack slot at all.
 *
 * Both registers come off ONE pool word: the FIFO control halfword at 0x04000184 and the
 * send word four bytes later, reached as fields of a held pointer. Two independent
 * volatile casts would pool two addresses and the function grows. */
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     s32;

typedef struct PxiPacket {
    u32 nTag  : 5;
    u32 bErr  : 1;
    u32 nData : 26;
} PxiPacket;

typedef struct IpcFifoRegs {
    volatile u16 wCnt;
    u16          pad_02;
    volatile u32 dwSend;
} IpcFifoRegs;

extern int  OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

s32 func_020093e8(u32 nTag, u32 nData, u32 bErr)
{
    IpcFifoRegs *pFifo = (IpcFifoRegs *)0x04000184;
    PxiPacket packet;
    int state;

    packet.nTag = nTag;
    packet.bErr = bErr;
    packet.nData = nData;

    if (pFifo->wCnt & 0x4000) {
        pFifo->wCnt |= 0xc000;
        return -1;
    }
    state = OS_DisableInterrupts();
    if (pFifo->wCnt & 2) {
        OS_RestoreInterrupts(state);
        return -2;
    }
    pFifo->dwSend = *(u32 *)&packet;
    OS_RestoreInterrupts(state);
    return 0;
}
