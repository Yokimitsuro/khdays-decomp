/* func_0202e844 -- SubOam_SetupBitmapGrid, MAIN (THUMB). Switches the sub engine's bitmap OBJ
 * mapping (DISPCNT_SUB bits 5-6 = 1), parks all 128 sub OBJs at y 192, then lays out a 4 x 3 grid
 * of 64x64 bitmap OBJs covering the sub screen (priority 3, alpha 15), each naming the bitmap
 * character at (x / 8) + (y / 8) * 32, and loads the table into the sub OAM. */
#pragma thumb on
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 attr01;
    union {
        u32 attr23;
        struct {
            u16 attr2;
            u16 affineParam;
        } s;
    } u;
} GXOamAttr;

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void DC_FlushRange(const void *start, u32 size);
extern void GXS_LoadOAM(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

void func_0202e844(void)
{
    GXOamAttr *oam = NNS_FndAllocFromDefaultExpHeapEx(0x400, 0x20);
    int i;
    int x;
    int y;
    GXOamAttr *p;

    *(volatile u32 *)0x04001000 = (*(volatile u32 *)0x04001000 & ~0x60) | 0x20;
    for (i = 0; i < 0x80; i++) {
        oam[i].attr01 = 0xc0;
        oam[i].u.attr23 = 0;
    }
    p = oam;
    for (y = 0; y < 0xc0; y += 0x40) {
        for (x = 0; x < 0x100; x += 0x40, p++) {
            p->attr01 = ((x & 0x1ff) << 16) | (0xc0000c00 | (y & 0xff));
            p->u.s.attr2 = (u16)(((x >> 3) + ((y >> 3) << 5)) | (3 << 10) | (15 << 12));
        }
    }
    DC_FlushRange(oam, 0x400);
    GXS_LoadOAM(oam, 0, 0x400);
    NNSi_FndFreeFromDefaultHeap(oam);
}
