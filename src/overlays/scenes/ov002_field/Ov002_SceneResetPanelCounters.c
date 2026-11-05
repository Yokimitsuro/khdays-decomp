/*
 * Ov002_SceneResetPanelCounters - put the counter half of the panel back to its
 * opening state.
 *
 * The two standing tweens are cleared, the total's digit widget is pointed at
 * its own cell of the scene's archive, every row's pair of tweens is cleared
 * along with the sign it was carrying, and the rows' shared digit widget is
 * pointed at the next cell and switched on.
 *
 * THUMB.
 */

#include "game/engine.h"
#include "game/archive.h"

typedef struct {
    int nMode;
    int nDuration;
    int nFrom;
    int nTo;
    int aStart[2];
    unsigned int dwFlags;
} Ov002Tween;

typedef struct {
    char pad000[0x3c];
    int nFileBase;
    char pad040[0x14];
    int aQueueSign[10];
    char pad07c[0x850];
    char totalWidget[0x108];
    char rowWidget[0x108];
    char padadc[0x14];
    Ov002Tween tweenTint;
    Ov002Tween tweenDepth;
    Ov002Tween aRowSlide[10];
    Ov002Tween aRowFade[10];
} Ov002ResetScene;

extern int data_ov002_0207f628;

extern void Tween_Clear(Ov002Tween *pTween);
extern void Ov002_RetargetWidget(void *pWidget, unsigned int nFileId, int nKind,
                                int nParam);

void Ov002_SceneResetPanelCounters(void)
{
    int i;
    Ov002ResetScene *s;

    s = *(Ov002ResetScene **)&data_ov002_0207f628;
    Tween_Clear(&s->tweenTint);
    Tween_Clear(&s->tweenDepth);

    Ov002_RetargetWidget(s->totalWidget,
                        ARCHIVE_HANDLE(s->nFileBase, 0),
                        0x3d, 0x5ec);

    for (i = 0; i < 10; i++) {
        Tween_Clear(&s->aRowSlide[i]);
        Tween_Clear(&s->aRowFade[i]);
        s->aQueueSign[i] = 0;
    }

    Ov002_RetargetWidget(s->rowWidget,
                        ARCHIVE_HANDLE(s->nFileBase, 6),
                        0x3d, 0x5ec);
    SceneNode_SetFlag40(s->rowWidget, 1);
}
