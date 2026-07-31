/* func_02030fdc = MsgQueue_Enqueue (ARM). Appends a packet (id param1, payload
 * param3 of param2 bytes) to the active send buffer of the queue slot selected by
 * param1. No-op (returns 0) if the packet would overflow the buffer (cap 0x1e0 when
 * the session is ready, else 0x60) or the slot is locked (state==1); returns 1 on
 * success.
 *
 * ctx = data_0204c230; the target buffer is entries[func_01fff99c(param1)].pActive.
 * A 2-byte packet header is written in place at pBuffer[writeOffset] as three
 * bitfields (chan:5 @bit1 = param1, len:10 @bit6 = param2, valid:1 @bit0), the
 * payload is MI_CpuCopy8'd right after it, and writeOffset advances by param2+2
 * (+1 padding byte when param2 is odd).
 *
 * Byte-exact levers: the len field is inserted as ((unsigned)param2<<22)>>16 (the
 * mwcc 10-bit-field-at-offset-6 idiom: lsl #22 then orr ...,lsr #16) -- writing
 * `param2<<6` instead fuses into one orr and comes up an instruction short; the
 * payload pointer reuses the materialized pBuffer+off (payload = (u8*)hdr + 2), which
 * also fixes the param->register colouring to match; writeOffset update is grouped
 * `wo + (param2 + 2)`; and the odd-length pad test is the signed `% 2` ROR idiom. */
typedef struct { int state; unsigned char *pBuffer; unsigned short writeOffset; unsigned short pad; } MsgQueueBuf;
typedef struct { MsgQueueBuf slots[2]; MsgQueueBuf *pActive; int field1c; } MsgQueueEntry;
typedef struct { int f0; MsgQueueEntry *entries; int count; } MsgQueueCtx;

extern MsgQueueCtx *data_0204c230;
extern int func_01fff99c(int id);
extern int func_02030694(void);   /* Session_IsReady */
extern void MI_CpuCopy8(void *src, void *dst, unsigned int size);

int func_02030fdc(int param1, int param2, unsigned short *param3)
{
    MsgQueueCtx *ctx = data_0204c230;
    int idx = func_01fff99c(param1);
    MsgQueueBuf *buf = ctx->entries[idx].pActive;
    int cap;
    int off, need;
    unsigned short *hdr;
    unsigned char *payload;

    cap = func_02030694() != 0 ? 0x1e0 : 0x60;
    off = buf->writeOffset;
    need = off + 2 + param2;
    if (param2 & 1) need++;
    if (need >= cap) return 0;
    if (buf->state == 1) return 0;

    hdr = (unsigned short *)(buf->pBuffer + off);
    *hdr = (unsigned short)((*hdr & ~0x3e) | (((unsigned short)param1 & 0x1f) << 1));
    *hdr = (unsigned short)((*hdr & ~0xffc0) | (((unsigned int)param2 << 22) >> 16));
    payload = (unsigned char *)hdr + 2;
    *hdr = (unsigned short)((*hdr & ~1) | 1);
    MI_CpuCopy8(param3, payload, param2);
    buf->writeOffset = (unsigned short)(buf->writeOffset + (param2 + 2));
    if (param2 % 2 != 0) {
        payload[param2] = 0;
        buf->writeOffset = (unsigned short)(buf->writeOffset + 1);
    }
    return 1;
}
