/*
 * Ov002_SceneResetPanelFrame - put the panel's frame widget back to its opening
 * state.
 *
 * The widget is placed at its fixed spot with cell 2 of the archive the
 * backdrop is cut from, switched on, given its palette tag, bound to its
 * sub-node and rewound.
 *
 * THUMB.
 */

#include "nitro/fx_types.h"
#include "game/archive.h"

typedef struct {
    char pad000[0xe0];
    char sub0e0[0x28];
} Ov002Widget;

typedef struct {
    char pad000[0x40];
    int nFileBase;
    char pad044[0x5cc];
    Ov002Widget frameWidget;
} Ov002FrameScene;

extern int data_ov002_0207f628;
extern const VecFx32 data_ov002_0207e184;

extern void SceneNode_SetFlag40(void *pWidget, int nValue);
extern void Widget_SetTagWord(void *pWidget, int nTag);
extern void BindAnimTrack(void *pWidget, int nSlot, void *pNode, int nFlags);
extern void SceneNode_Enable(void *pWidget);

extern void Ov002_PlaceWidget(void *pWidget, unsigned int nFileId,
                                const VecFx32 *pPos, int nTint, int nKind);

void Ov002_SceneResetPanelFrame(void)
{
    VecFx32 v;
    Ov002FrameScene *s;

    s = *(Ov002FrameScene **)&data_ov002_0207f628;
    v = data_ov002_0207e184;

    Ov002_PlaceWidget(&s->frameWidget,
                        ARCHIVE_HANDLE(s->nFileBase, 2),
                        &v, 0xa000, 5);
    SceneNode_SetFlag40(&s->frameWidget, 1);
    Widget_SetTagWord(&s->frameWidget, 0x7fff);
    BindAnimTrack(&s->frameWidget, 4, s->frameWidget.sub0e0, 0);
    SceneNode_Enable(&s->frameWidget);
}
