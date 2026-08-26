typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct MtxFx43 {
    s32 value[12];
} MtxFx43;

typedef struct VecFx32 {
    s32 x;
    s32 y;
    s32 z;
} VecFx32;

typedef struct RenderMatrixCache {
    u8 pad000[0x514];
    u32 slotIds514[3];
    u8 pad520[0x528 - 0x520];
    MtxFx43 matrices528[3];
    u8 pad5b8[0x694 - 0x5b8];
    u8 flags694;
} RenderMatrixCache;

typedef struct RenderOwner {
    u8 pad00[0x2c];
    RenderMatrixCache *matrixCache2c;
} RenderOwner;

typedef struct RenderContext {
    u8 pad00[4];
    RenderOwner *owner04;
    u32 flags08;
    u8 pad0c[0xae - 0x0c];
    u8 selectedSlotAE;
} RenderContext;

extern void func_02016294(MtxFx43 *position, VecFx32 *vector);

void func_01fffe68(RenderContext *context)
{
    u32 flags = context->flags08;
    RenderOwner *owner = context->owner04;
    u32 selected;
    RenderMatrixCache *cache;
    int index;

    selected = (flags & 0x10) != 0
                   ? context->selectedSlotAE
                   : (u32)-1;
    cache = owner->matrixCache2c;
    index = 0;
    do {
        if (selected == cache->slotIds514[index]) {
            func_02016294(&cache->matrices528[index], 0);
            cache->flags694 |= 4;
            return;
        }
        index++;
    } while (index < 3);
}
