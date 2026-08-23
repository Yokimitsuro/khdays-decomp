/*
 * Ov002_SceneResetPanelMarker - put the panel's world marker back to its
 * opening state.
 *
 * The marker widget is placed at the origin with its own cell of the scene's
 * archive, switched on and bound to its sub-node. The projection matrix the
 * marker is drawn through is rebuilt from the five view parameters the scene
 * carries, and the three tweens that drive the marker are cleared.
 *
 * THUMB. The marker's position is cleared through a walking pointer rather than
 * by name: writing v.x/v.y/v.z folds the three stores to sp-relative form and
 * leaves the address to be computed just before the call, while the pointer
 * keeps it in a register from the start, which is what the ROM does.
 */

typedef signed long fx32;

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct {
    fx32 a[16];
} MtxFx44;

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
    int nMode;
    int nDuration;
    int nFrom;
    int nTo;
    int aStart[2];
    unsigned int dwFlags;
} Ov002Tween;

typedef struct {
    char pad000[4];
    int aView[5];
    char pad018[0x24];
    int nFileBase;
    char pad040[0x1028];
    Ov002Widget markerWidget;
    MtxFx44 mtxProj;
    Ov002Tween aMarkerTween[3];
} Ov002MarkerScene;

extern int data_ov002_0207f628;

extern void func_02035f84(Ov002Tween *pTween);
extern void func_0202afc4(void *pWidget, int nValue);
extern void func_0202accc(void *pWidget, int nSlot, void *pNode, int nFlags);
extern void func_02004d60(int a, int b, int c, int d, int e, int f,
                          MtxFx44 *pOut);

extern void func_ov002_0205f5e0(void *pWidget, unsigned int nFileId,
                                const VecFx32 *pPos, int nTint, int nKind);

void func_ov002_02060c70(void)
{
    VecFx32 v;
    fx32 *pWrite;
    int i;
    Ov002MarkerScene *s;

    s = *(Ov002MarkerScene **)&data_ov002_0207f628;
    pWrite = (fx32 *)&v;
    pWrite[0] = 0;
    pWrite[1] = 0;
    pWrite[2] = 0;
    func_ov002_0205f5e0(&s->markerWidget,
                        0x80000006
                            | ((s->nFileBase + 0x8000) & 0xfffffc) << 7,
                        &v, 0xa000, 0xe);
    func_0202afc4(&s->markerWidget, 1);
    func_0202accc(&s->markerWidget, 3, s->markerWidget.sub0e0, 0);

    func_02004d60(s->aView[0], s->aView[1], s->aView[2], s->aView[3],
                  s->aView[4], 0x1000, &s->mtxProj);

    for (i = 0; i < 3; i++) {
        func_02035f84(&s->aMarkerTween[i]);
    }
}
