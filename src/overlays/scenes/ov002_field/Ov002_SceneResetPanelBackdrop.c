/*
 * Ov002_SceneResetPanelBackdrop - put the panel's backdrop widget back to its
 * opening state.
 *
 * Its tween is cleared, it is pointed at its own cell of the scene's archive,
 * rewound, and parked at the far back of the scene. The word that says whether
 * it is being held is cleared last.
 *
 * THUMB.
 */

#include "nitro/fx_types.h"
#include "game/engine.h"
#include "game/archive.h"

typedef struct {
    char pad000[0x78];
    int nList;
    char pad07c[0x28];
    VecFx32 vPos;
    int aTint[3];
    char pad0bc[0x4c];
} Ov002Widget;

typedef struct {
    int nMode;
    int nDuration;
    int nFrom;
    int nTo;
    int aStart[2];
    unsigned int dwFlags;
} Ov002Tween;

typedef struct {
    char pad000[0x40];
    int nFileBase;
    char pad044[0x90];
    int nBackdropHeld;
    char pad0d8[0xce8];
    Ov002Widget backdropWidget;
    char padec8[0x108];
    Ov002Tween tweenBackdrop;
} Ov002BackdropScene;

extern int data_ov002_0207f628;

extern void Tween_Clear(Ov002Tween *pTween);
extern void Ov002_RetargetWidget(void *pWidget, unsigned int nFileId, int nKind,
                                int nParam);

void Ov002_SceneResetPanelBackdrop(void)
{
    VecFx32 v;
    Ov002BackdropScene *s;

    s = *(Ov002BackdropScene **)&data_ov002_0207f628;
    Tween_Clear(&s->tweenBackdrop);

    Ov002_RetargetWidget(&s->backdropWidget,
                        ARCHIVE_HANDLE(s->nFileBase, 1),
                        0x38, 0x614);
    SceneNode_Enable(&s->backdropWidget);

    v.x = -0x3e80;
    v.y = 0x2a94;
    v.z = -0x100000;
    s->backdropWidget.vPos = v;
    s->nBackdropHeld = 0;
}
