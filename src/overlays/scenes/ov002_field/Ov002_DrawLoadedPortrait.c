/*
 * Ov002_DrawLoadedPortrait - finish a portrait load and put the caption under
 * it.
 *
 * Without a live text context the load node is thrown away. Otherwise what was
 * loaded is copied into the context's tile buffer: the wide layout copies two
 * 0x140-byte halves and captions itself from message 9, the narrow one copies a
 * single block whose size the context carries and captions itself from whatever
 * 0206333c hands back.
 *
 * In the narrow case the second screen also gets its own surface and the same
 * block, and the message caption is drawn there.
 *
 * THUMB.
 */

#include "game/engine.h"

typedef struct {
    char pad000[0xfc];
    char textCtx[0xc];
    int nCopySize;
    char pad10c[8];
    void *pTiles;
    char pad118[0x60];
    void *pSurface;
    char pad17c[0x38];
    char msgCtx[0x40];
} Ov002TextScene;

extern int data_ov002_0207f62c;
extern int data_0204c240;

extern void GetResourceSubBlock_CHAR(int nId, void **ppOut);
extern void MIi_CpuCopyFast(const void *pSrc, void *pDst, unsigned int nSize);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern void *TileSurface_AddCanvas(void *pCtx, int nFlags);

extern void Ov002_DestroyOwnedEntry(void *pNode, int nMode);
extern void *Ov002_VariadicMapForward(void *pMsg, int nKind, void *pOut, int nSize, ...);
extern int Ov002_GetPanelField0058(void);
extern void *Ov002_Field_GetWordB8(void);
extern void Ov002_DrawMessageCaption(void);
extern void Ov002_TickOptionsPage(void);

void Ov002_DrawLoadedPortrait(void *pNode)
{
    void *pText;
    void *pSub;
    char aText[0x20];
    Ov002TextScene *s;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    if (s == 0) {
        Ov002_DestroyOwnedEntry(pNode, 1);
        return;
    }

    GetResourceSubBlock_CHAR(*(int *)((char *)pNode + 8), &pSub);
    if (Ov002_GetPanelField0058() != 0) {
        MIi_CpuCopyFast(*(void **)((char *)pSub + 0x14),
                        *(void **)((char *)s->pTiles + 0x20), 0x140);
        MIi_CpuCopyFast((char *)*(void **)((char *)pSub + 0x14) + 0x320,
                        (char *)*(void **)((char *)s->pTiles + 0x20) + 0x140,
                        0x140);
        Ov002_VariadicMapForward(s->msgCtx, 0, aText, 0x10, GameState_GetField(0, 9));
        Text_DrawWithShadow(s->textCtx, 0, 0, 0xf, aText, 0);
    } else {
        MI_CpuCopy8(*(void **)((char *)pSub + 0x14),
                    *(void **)((char *)s->pTiles + 0x20), s->nCopySize);
        pText = Ov002_Field_GetWordB8();
        if ((*(unsigned char *)&data_0204c240 & 6) == 2) {
            s->pSurface = TileSurface_AddCanvas(s->textCtx, 0);
            MI_CpuCopy8(*(void **)((char *)pSub + 0x14),
                        *(void **)((char *)s->pSurface + 0x20), s->nCopySize);
            Ov002_DrawMessageCaption();
        }
        if (pText != 0) {
            Text_DrawWithShadow(s->textCtx, 0, 0, 0xf, pText, 0);
        }
    }

    Ov002_DestroyOwnedEntry(pNode, 1);
    Ov002_TickOptionsPage();
}
