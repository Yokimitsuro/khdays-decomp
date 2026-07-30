/* func_ov008_020798a8 -- Ov008_SendPacket (164 B, 4 relocs).
 * Queues one outgoing packet on the singleton send context data_ov008_02090f24, if it is idle.
 * Returns 0 immediately when a send is already in flight (busy != 0). Otherwise it bumps the
 * sequence counter, marks the context busy, writes the sequence into the packet buffer header
 * (word 0), copies the caller's payload right after it (buf + 4, MI_CpuCopy8), and hands the
 * whole buffer -- header + payload, (u16)(size + 4) bytes total -- to the transport send call
 * with func_ov008_02079850 as the completion callback. On a successful hand-off it returns 1
 * with the context left busy (cleared later by the callback); if the send call reports failure
 * it clears the busy flag again and returns 0. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov008SendCtx {
    char *buf;       /* 0x00: packet buffer: word[0]=seq counter, [4..]=payload */
    int   seq;       /* 0x04: outgoing sequence counter */
    u8    pad_08[0x24];
    int   busy;      /* 0x2c: 1 while a send is in flight */
} Ov008SendCtx;

extern Ov008SendCtx *data_ov008_02090f24;
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern int  WM_EndKeySharing_0x020bf900(void *buf, u16 size, void *callback);
extern void func_ov008_02079850(void);

int func_ov008_020798a8(const void *src, int size)
{
    if (data_ov008_02090f24->busy != 0) {
        return 0;
    }
    data_ov008_02090f24->seq += 1;
    data_ov008_02090f24->busy = 1;
    *(int *)data_ov008_02090f24->buf = data_ov008_02090f24->seq;
    MI_CpuCopy8(src, data_ov008_02090f24->buf + 4, size);
    if (WM_EndKeySharing_0x020bf900(data_ov008_02090f24->buf, (u16)(size + 4),
                                    func_ov008_02079850) != 0) {
        return 1;
    }
    data_ov008_02090f24->busy = 0;
    return 0;
}
