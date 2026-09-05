typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov012OpeningEvent {
    u32 nTriggerThreadDelta;
    u16 uHandlerIndex;
    u16 uSpriteResourceIndex;
    u16 uBackgroundLayer;
    u16 uAuxValue;
} Ov012OpeningEvent;

typedef struct NNSG2dScreenData {
    u8 reserved00[8];
    u32 szByte;
    u8 rawData[1];
} NNSG2dScreenData;

extern void GX_LoadBG0Scr(const void *pSource, u32 destinationOffset, u32 size);
extern void GX_LoadBG1Scr(const void *pSource, u32 destinationOffset, u32 size);
extern void GX_LoadBG2Scr(const void *pSource, u32 destinationOffset, u32 size);

int func_ov012_0205b32c(void *pContext, u32 nThreadDelta,
                             Ov012OpeningEvent *pEvent) {
    char *context;
    NNSG2dScreenData *pScreenResource;

    context = (char *)pContext;
    pScreenResource = *(NNSG2dScreenData **)(0x8c00 + context +
        pEvent->uSpriteResourceIndex * 0xc);

    if (pEvent->uBackgroundLayer == 0) goto bg0;
    if (pEvent->uBackgroundLayer == 1) goto bg1;
    if (pEvent->uBackgroundLayer != 2) goto done;
    goto bg2;

bg0:
    GX_LoadBG0Scr(pScreenResource->rawData, 0, pScreenResource->szByte);
    goto done;

bg1:
    GX_LoadBG1Scr(pScreenResource->rawData, 0, pScreenResource->szByte);
    goto done;

bg2:
    GX_LoadBG2Scr(pScreenResource->rawData, 0, pScreenResource->szByte);

done:
    return 1;
}
