/* Dispatches a queued command packet: each record (skipping zero padding bytes) is a u16 header
 * (handler index in bits 1-5, payload size in bits 6-15) followed by its payload, which is copied to
 * the effect list's scratch buffer (+0x5c) and handed to the registered handler (+0xc table) with
 * its size. A packet whose records do not end exactly at its length is walked again (the release
 * build keeps the empty check loop). The packet is then emptied and marked idle. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 flag : 1;
    u16 handler : 5;
    u16 size : 10;
} CmdHeader;

typedef struct {
    u8 *data;           /* 0x00 */
    u16 len;            /* 0x04 */
    int busy;           /* 0x08 */
} CmdPacket;

typedef struct {
    char pad00[0xc];
    void (*handlers[20])(void *buf, int size);    /* 0x0c */
    void *buf;                                    /* 0x5c */
} EffectMgr;

extern EffectMgr *data_0204c22c;
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void func_02030a4c(CmdPacket *pk)
{
    EffectMgr *m = data_0204c22c;
    u8 *p;     /* one cursor for the dispatch pass and the resync pass */

    if (pk->len == 0) {
        return;
    }
    pk->busy = 1;
    p = pk->data;
    do {
        if (*p == 0) {
            p++;
            if (p - pk->data >= pk->len) {
                break;
            }
        }
        {
            CmdHeader *hdr = (CmdHeader *)p;

            p += 2;
            if (m->handlers[hdr->handler] != 0) {
                MI_CpuCopy8(p, m->buf, hdr->size);
                m->handlers[hdr->handler](m->buf, (u8)hdr->size);
            }
            p += hdr->size;
        }
    } while (p - pk->data < pk->len);
    if (pk->len != p - pk->data) {
        p = pk->data;
        do {
            if (*p == 0) {
                p++;
            }
            {
                CmdHeader *hdr = (CmdHeader *)p;

                p += 2;
                p += hdr->size;
            }
        } while (p - pk->data < pk->len);
    }
    pk->len = 0;
    pk->busy = 0;
}
