#pragma thumb on
/* func_020308a0 -- lay out the packet slots of the session context (data_0204c22c), MAIN. Modes 1/2
 * use five slots, mode 3 two; the slot table sits at the DTCM area data_027e07fc, followed by the
 * slot buffers. The slot sizes follow the connection kind (CARD_GetResultCode_0x0203065c is
 * misnamed): kinds 1/2 give the first two slots 0x3d8 bytes and the rest 0xc0, kind 3 gives every
 * slot 0x3c0. Each slot then gets its word-aligned buffer, a zero length and a zero state, and a
 * 0x3c0-byte scratch block is allocated from the default heap (+0x5c). */
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PacketSlot {
    void *buf;                          /* +0x0 */
    u16 len;                            /* +0x4 */
    u16 size;                           /* +0x6 */
    int state;                          /* +0x8 */
} PacketSlot;

typedef struct PacketCtx {
    int pad00;
    PacketSlot *slot;                   /* +0x04 */
    int slotCount;                      /* +0x08 */
    char pad0c[0x5c - 0xc];
    void *scratch;                      /* +0x5c */
} PacketCtx;

extern PacketCtx *data_0204c22c;
extern char data_027e07fc[];
extern int **data_0204c024;
extern int CARD_GetResultCode_0x0203065c(void);
extern void *func_020236cc(u32 size, int **heap);

void func_020308a0(int mode)
{
    PacketCtx *ctx = data_0204c22c;
    char *buf = data_027e07fc;
    int i;

    switch (mode) {
    case 1:
    case 2:
        ctx->slotCount = 5;
        break;
    case 3:
        ctx->slotCount = 2;
        break;
    }
    ctx->slot = (PacketSlot *)buf;
    buf += (ctx->slotCount * sizeof(PacketSlot) + 3) & ~3;
    switch (CARD_GetResultCode_0x0203065c()) {
    case 1:
    case 2:
        for (i = 0; i < 2; i++) {
            ctx->slot[i].size = 0x3d8;
        }
        for (i = 2; i < ctx->slotCount; i++) {
            ctx->slot[i].size = 0xc0;
        }
        break;
    case 3:
        for (i = 0; i < ctx->slotCount; i++) {
            ctx->slot[i].size = 0x3c0;
        }
        break;
    }
    for (i = 0; i < ctx->slotCount; i++) {
        ctx->slot[i].buf = buf;
        buf += (ctx->slot[i].size + 3) / 4 * 4;
        ctx->slot[i].len = 0;
        ctx->slot[i].state = 0;
    }
    ctx->scratch = func_020236cc(0x3c0, data_0204c024);
}
