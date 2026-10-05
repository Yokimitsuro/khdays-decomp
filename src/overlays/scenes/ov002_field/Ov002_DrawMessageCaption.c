/*
 * Ov002_DrawMessageCaption - draw the caption for the current message.
 *
 * The text surface is opened with the style the context carries, the message
 * whose id the language table gives for the current entry is expanded into a
 * 256-byte buffer, the line is drawn, and the surface is closed again.
 *
 * ARM.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct {
    char pad000[0xfc];
    char textCtx[0x7c];
    int nStyle;
    char pad17c[0x38];
    char msgCtx[0x40];
} Ov002TextScene;

extern int data_ov002_0207f62c;
extern int data_0204c254;
extern const int data_ov002_0207e3a0[];

extern void TileSurface_SetCurrentItem(void *pCtx, int nStyle, int nFlags);

extern int Ov002_GetVarRecordByIndex(void *pMsg, int nId);
extern void *Ov002_VariadicMapForward(void *pMsg, int nKind, void *pOut, int nSize, ...);

void Ov002_DrawMessageCaption(void)
{
    int nEntry;
    char aText[0x100];
    Ov002TextScene *s;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    TileSurface_SetCurrentItem(s->textCtx, s->nStyle, 0);

    nEntry = Ov002_GetVarRecordByIndex(
        s->msgCtx,
        data_ov002_0207e3a0[*(u16 *)((char *)&data_0204c254 + 0xe)]);
    Ov002_VariadicMapForward(s->msgCtx, 0xe, aText, 0x80, nEntry);

    Text_DrawWithShadow(s->textCtx, 0, 0, 5, aText, 0);
    TileSurface_SetCurrentItem(s->textCtx, 0, 0);
}
