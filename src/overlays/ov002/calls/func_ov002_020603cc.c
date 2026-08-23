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

extern void func_02035f84(Ov002Tween *pTween);
extern void func_0202afc4(void *pWidget, int nValue);
extern void func_ov002_0205f5a8(void *pWidget, unsigned int nFileId, int nKind,
                                int nParam);

void func_ov002_020603cc(void)
{
    int i;
    Ov002ResetScene *s;

    s = *(Ov002ResetScene **)&data_ov002_0207f628;
    func_02035f84(&s->tweenTint);
    func_02035f84(&s->tweenDepth);

    func_ov002_0205f5a8(s->totalWidget,
                        0x80000000
                            | ((s->nFileBase + 0x8000) & 0xfffffc) << 7,
                        0x3d, 0x5ec);

    for (i = 0; i < 10; i++) {
        func_02035f84(&s->aRowSlide[i]);
        func_02035f84(&s->aRowFade[i]);
        s->aQueueSign[i] = 0;
    }

    func_ov002_0205f5a8(s->rowWidget,
                        0x80000006
                            | ((s->nFileBase + 0x8000) & 0xfffffc) << 7,
                        0x3d, 0x5ec);
    func_0202afc4(s->rowWidget, 1);
}
