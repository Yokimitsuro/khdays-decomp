/* func_ov008_0205cc04 -- Ov008_CheckPageItemLimits (212 B, 4 relocs).
 * Capacity check for one save/equip page. Allocates a 1 KB per-item counter buffer and clears it,
 * then walks the u16 cell grid at *data_0204be18 + 0xc10 -- a [page][3][40] array -- for the given
 * page. Each non-zero cell v is an entry index into the 0x9c-stride table at ctx->table (held at
 * ctx+0x207c); the entry's itemId (field 0x14) selects a counter. It tallies each item, and as soon
 * as a count would exceed that item's per-item limit (base + itemId + 0x810) it stops and returns 1
 * (over capacity); otherwise it returns 0. The counter buffer is freed on both exits. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct SlotEntry {
    u8  pad_0000[0x14];
    int itemId;          /* 0x14 */
    u8  pad_0018[0x84];
} SlotEntry;             /* 0x9c */

typedef struct Ov008SlotCtx {
    u8         pad_0000[0x207c];
    SlotEntry *table;    /* 0x207c */
} Ov008SlotCtx;

extern char *data_0204be18;
extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void  MI_CpuFill8(void *dst, int val, unsigned int n);
extern void  NNSi_FndFreeFromDefaultHeap(void *p);

int func_ov008_0205cc04(Ov008SlotCtx *ctx, int page)
{
    int result = 0;
    u8 *buf = NNSi_FndAllocFromDefaultExpHeap(0x400);
    int i, j;

    MI_CpuFill8(buf, 0, 0x400);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 40; j++) {
            char *base = data_0204be18;
            u16 v = ((u16 (*)[3][40])(base + 0xc10))[page][i][j];
            if (v != 0) {
                int p = ctx->table[v].itemId;
                if (buf[p] < *(u8 *)(base + p + 0x810)) {
                    buf[p]++;
                } else {
                    result = 1;
                    goto done;
                }
            }
        }
    }
done:
    if (buf != 0)
        NNSi_FndFreeFromDefaultHeap(buf);
    return result;
}
