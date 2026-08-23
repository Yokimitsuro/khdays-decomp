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

typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    char pad000[0x78];
    int nList;
    char pad07c[0x28];
    Ov002Vec3 vPos;
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

extern void func_02035f84(Ov002Tween *pTween);
extern void func_0202af1c(void *pWidget);
extern void func_ov002_0205f5a8(void *pWidget, unsigned int nFileId, int nKind,
                                int nParam);

void func_ov002_02060488(void)
{
    Ov002Vec3 v;
    Ov002BackdropScene *s;

    s = *(Ov002BackdropScene **)&data_ov002_0207f628;
    func_02035f84(&s->tweenBackdrop);

    func_ov002_0205f5a8(&s->backdropWidget,
                        0x80000001
                            | ((s->nFileBase + 0x8000) & 0xfffffc) << 7,
                        0x38, 0x614);
    func_0202af1c(&s->backdropWidget);

    v.x = -0x3e80;
    v.y = 0x2a94;
    v.z = -0x100000;
    s->backdropWidget.vPos = v;
    s->nBackdropHeld = 0;
}
