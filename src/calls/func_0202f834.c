/*
 * func_0202f834 - attach a tile-text surface to one of the eight BG layers.
 *
 * Records the caller's resource handle and the layer it is being attached to,
 * then snapshots that layer's live BG control register (BG0CNT..BG3CNT on the
 * main engine, BG0CNT_SUB..BG3CNT_SUB on the sub engine) into this frame's
 * per-layer backup slots and reads the screen-size and color-depth bitfields
 * back out of the snapshot. Screen size picks the 32- or 64-tile map width used
 * to lay the tile map out (func_02014174) over the screen base that layer's
 * dispatch entry hands back (func_02024950). Color depth picks 32 or 64 bytes
 * per tile, which sizes the pixel buffer allocated from the default expanded
 * heap and cleared, and picks the 4- or 8-bit sub-buffer set up by
 * func_02014148. Finally the object's internal links are wired: the self-
 * pointing context pointer, a copy of the resource handle, and the Frame's
 * trailing two fields.
 *
 * The per-layer backup slots are written but never read back after this call;
 * only the snapshot copy chain inside each case consumes them.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 x;         /* +0x00 */
    u16 y;         /* +0x02 */
    u16 width;     /* +0x04 */
    u16 height;    /* +0x06 */
    u16 charBase;  /* +0x08 */
    u16 palette;   /* +0x0a */
    u16 field_0c;  /* +0x0c */
    u16 field_0e;  /* +0x0e */
} Frame;

typedef struct {
    void *res;         /* +0x00 */
    u8 field_04[0x18]; /* +0x04, opaque sub-buffer handed to func_02014148 */
    void *field_1c;    /* +0x1c */
    void *field_20;    /* +0x20 */
    u32 field_24;      /* +0x24 */
    u32 field_28;      /* +0x28 */
    void *pixels;      /* +0x2c */
    int mode;          /* +0x30 */
    u32 size;          /* +0x34 */
    u16 field_38;      /* +0x38 */
    u16 width;         /* +0x3a */
    u16 height;        /* +0x3c */
    u8 tileBytes;      /* +0x3e */
    u8 layer;          /* +0x3f */
} Obj;

/* NDS BGxCNT, LSB-first. */
typedef union {
    u16 raw;
    struct {
        u16 priority:2;
        u16 charBase:4;
        u16 mosaic:1;
        u16 colorMode:1;
        u16 screenBase:5;
        u16 extPalette:1;
        u16 screenSize:2;
    } f;
} BgControl;

typedef struct {
    BgControl field_00;
    BgControl field_02;
} BgControlBackup;

extern int func_02024950(int index);
extern void func_02014174(u16 *dst, int width, int height, int x, int y,
                          int mapW, int tile, int palette);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void MIi_CpuClearFast(unsigned int data, void *dest, unsigned int size);
extern void func_02014148(void *a, void *b, int c, int d, int e);

int func_0202f834(Obj *obj, int layer, void *res, Frame *frame)
{
    BgControlBackup backup0, backup1, backup2, backup3;
    BgControlBackup backup4, backup5, backup6, backup7;
    BgControl saved0, saved1, saved2, saved3;
    BgControl saved4, saved5, saved6, saved7;
    int screenSize;
    int colorMode;
    int mapW;

    obj->res = res;
    obj->layer = (u8)layer;

    switch (layer) {
    case 0:
        obj->mode = 4;
        saved0.raw = *(volatile u16 *)0x4000008;
        backup0.field_02 = saved0;
        screenSize = backup0.field_02.f.screenSize;
        backup0.field_00 = backup0.field_02;
        colorMode = backup0.field_00.f.colorMode;
        break;
    case 1:
        obj->mode = 5;
        saved1.raw = *(volatile u16 *)0x400000a;
        backup1.field_02 = saved1;
        screenSize = backup1.field_02.f.screenSize;
        backup1.field_00 = backup1.field_02;
        colorMode = backup1.field_00.f.colorMode;
        break;
    case 2:
        obj->mode = 6;
        saved2.raw = *(volatile u16 *)0x400000c;
        backup2.field_02 = saved2;
        screenSize = backup2.field_02.f.screenSize;
        backup2.field_00 = backup2.field_02;
        colorMode = backup2.field_00.f.colorMode;
        break;
    case 3:
        obj->mode = 7;
        saved3.raw = *(volatile u16 *)0x400000e;
        backup3.field_02 = saved3;
        screenSize = backup3.field_02.f.screenSize;
        backup3.field_00 = backup3.field_02;
        colorMode = backup3.field_00.f.colorMode;
        break;
    case 4:
        obj->mode = 0x14;
        saved4.raw = *(volatile u16 *)0x4001008;
        backup4.field_02 = saved4;
        screenSize = backup4.field_02.f.screenSize;
        backup4.field_00 = backup4.field_02;
        colorMode = backup4.field_00.f.colorMode;
        break;
    case 5:
        obj->mode = 0x15;
        saved5.raw = *(volatile u16 *)0x400100a;
        backup5.field_02 = saved5;
        screenSize = backup5.field_02.f.screenSize;
        backup5.field_00 = backup5.field_02;
        colorMode = backup5.field_00.f.colorMode;
        break;
    case 6:
        obj->mode = 0x16;
        saved6.raw = *(volatile u16 *)0x400100c;
        backup6.field_02 = saved6;
        screenSize = backup6.field_02.f.screenSize;
        backup6.field_00 = backup6.field_02;
        colorMode = backup6.field_00.f.colorMode;
        break;
    case 7:
        obj->mode = 0x17;
        saved7.raw = *(volatile u16 *)0x400100c;
        backup7.field_02 = saved7;
        screenSize = backup7.field_02.f.screenSize;
        backup7.field_00 = backup7.field_02;
        colorMode = backup7.field_00.f.colorMode;
        break;
    }

    obj->field_38 = frame->charBase;
    if (screenSize == 0 || screenSize == 2) {
        mapW = 0x20;
    } else {
        mapW = 0x40;
    }

    func_02014174((u16 *)func_02024950(layer), frame->width, frame->height,
                  frame->x, frame->y, mapW, frame->charBase, frame->palette);

    obj->tileBytes = (u8)(colorMode == 0 ? 0x20 : 0x40);
    obj->width = frame->width;
    obj->height = frame->height;
    obj->size = obj->tileBytes * frame->width * frame->height;

    obj->pixels = NNSi_FndAllocFromDefaultExpHeap(obj->size);
    MIi_CpuClearFast(0, obj->pixels, obj->size);

    func_02014148(obj->field_04, obj->pixels, frame->width, frame->height,
                  colorMode == 0 ? 4 : 8);

    {
        u16 field_0e = frame->field_0e;
        u16 field_0c = frame->field_0c;
        void *resource = obj->res;

        obj->field_1c = obj->field_04;
        obj->field_20 = resource;
        obj->field_24 = field_0c;
        obj->field_28 = field_0e;
    }
    obj->field_20 = obj->res;

    return 1;
}
