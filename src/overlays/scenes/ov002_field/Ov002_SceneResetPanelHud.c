/*
 * Ov002_SceneResetPanelHud - put the panel's HUD widget back to its opening
 * state.
 *
 * The two pending-change words are cleared and the current fade mask is
 * latched. The widget is then bound to cell 0 of the scene's archive as kind
 * 0xe, switched on, given its tint - pushed down the three colour slots the
 * way every widget in this scene takes one - and bound to its sub-node.
 *
 * THUMB.
 */

#include "nitro/fx_types.h"
#include "game/archive.h"

typedef struct {
    char pad000[0x78];
    int nList;
    char pad07c[0x28];
    VecFx32 vPos;
    int aTint[3];
    char pad0bc[0x24];
    char sub0e0[0x28];
} Ov002Widget;

typedef struct {
    char pad000[0x3c];
    int nFileBase;
    char pad040[0x98];
    int bHudDirty;
    int bHudHeld;
    char pad0e0[0x1134];
    Ov002Widget hudWidget;
    char pad131c[8];
    int nFadeMask;
} Ov002HudScene;

extern int data_ov002_0207f628;

extern int Obj_GetFrameCount(void);
extern void RegisterSeqAndInit(void *pWidget, unsigned int nFileId, int nSlot,
                          int nKind);
extern void SceneNode_SetFlag40(void *pWidget, int nValue);
extern void BindAnimTrack(void *pWidget, int nSlot, void *pNode, int nFlags);

void Ov002_SceneResetPanelHud(void)
{
    Ov002HudScene *s;

    s = *(Ov002HudScene **)&data_ov002_0207f628;
    s->bHudDirty = 0;
    s->bHudHeld = 0;
    s->nFadeMask = Obj_GetFrameCount();

    RegisterSeqAndInit(&s->hudWidget,
                  ARCHIVE_HANDLE(s->nFileBase, 0),
                  1, 0xe);
    SceneNode_SetFlag40(&s->hudWidget, 1);

    s->hudWidget.aTint[2] = 0xa99a;
    s->hudWidget.aTint[1] = s->hudWidget.aTint[2];
    s->hudWidget.aTint[0] = s->hudWidget.aTint[1];

    BindAnimTrack(&s->hudWidget, 3, s->hudWidget.sub0e0, 0);
}
