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

typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

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
extern const Ov002Vec3 data_ov002_0207e184;

extern void func_0202afc4(void *pWidget, int nValue);
extern void func_0202afdc(void *pWidget, int nTag);
extern void func_0202accc(void *pWidget, int nSlot, void *pNode, int nFlags);
extern void func_0202af1c(void *pWidget);

extern void func_ov002_0205f5e0(void *pWidget, unsigned int nFileId,
                                const Ov002Vec3 *pPos, int nTint, int nKind);

void func_ov002_020613f0(void)
{
    Ov002Vec3 v;
    Ov002FrameScene *s;

    s = *(Ov002FrameScene **)&data_ov002_0207f628;
    v = data_ov002_0207e184;

    func_ov002_0205f5e0(&s->frameWidget,
                        0x80000002
                            | ((s->nFileBase + 0x8000) & 0xfffffc) << 7,
                        &v, 0xa000, 5);
    func_0202afc4(&s->frameWidget, 1);
    func_0202afdc(&s->frameWidget, 0x7fff);
    func_0202accc(&s->frameWidget, 4, s->frameWidget.sub0e0, 0);
    func_0202af1c(&s->frameWidget);
}
