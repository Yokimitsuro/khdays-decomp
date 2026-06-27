typedef unsigned int u32;
typedef unsigned short u16;
typedef signed int s32;

extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern void DC_FlushRange(const void *start, u32 size);
extern void MI_DmaCopy16(u32 dmaNo, const void *src, void *dst, u32 size);

extern u16 *data_02041ac0[];
extern u32 data_020422b8;

typedef struct {
    u16 pad0;
    u16 field_2;
    u16 field_4;
} Rect;

typedef struct {
    u32 field_0;
    u32 field_4;
    u32 field_8;
    u32 field_c;
    u32 size;       /* 0x10 */
    void *data;     /* 0x14 */
} BgData;

void func_02012e90(u32 a, BgData *bg, Rect *r) {
    u32 off = 0;
    u32 block;
    u32 dma;
    void *src;
    u32 size;

    if (r != 0) {
        u32 wh = r->field_2 * r->field_4;
        u32 t = (bg->field_4 == 4) ? 0x40 : 0x20;
        off = wh * t;
    }
    DC_FlushRange(bg->data, bg->size);

    size = bg->size;
    src = bg->data;
    block = (*data_02041ac0[a] & 0x3c) >> 2;
    if ((s32)a > 3) {
        a = 0x06200000;
    } else {
        a = ((*(volatile u32 *)0x04000000) & 0x07000000) >> 24 << 16;
        a += 0x06000000;
    }

    {
        u32 dst = a + (block << 14);
        dma = data_020422b8;
        if (dma != 0xFFFFFFFF) {
            MI_DmaCopy16(dma, src, (void *)(dst + off), size);
        } else {
            MIi_CpuCopy16(src, (void *)(dst + off), size);
        }
    }
}
