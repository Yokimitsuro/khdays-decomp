/*
 * Ov002_StepPanelPointer - walk the panel's pointer widget towards a world
 * position.
 *
 * The animation is advanced by a step that depends on the transition currently
 * running, and the caller is told whether it has finished. While it has not,
 * the widget is moved to the projected position and refreshed; once it has, it
 * is left where it stands.
 *
 * ARM.
 */

typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    char pad000[0xa4];
    Ov002Vec3 vPos;
    char pad0b0[0x58];
} Ov002Widget;

typedef struct {
    char pad000[0x132c];
    Ov002Widget pointerWidget;
} Ov002PointerScene;

extern int data_ov002_0207f628;

extern int func_02023c40(void);
extern unsigned int func_0202a818(void *pWidget, int nStep);
extern void func_0202aa9c(void *pWidget);

extern void func_ov002_02060b4c(Ov002Vec3 *pOut, const Ov002Vec3 *pIn,
                                const void *pCam);

unsigned int func_ov002_02061370(const void *pCam, const Ov002Vec3 *pIn)
{
    Ov002PointerScene *s;
    unsigned int nDone;
    int nStep;
    Ov002Vec3 v;

    s = *(Ov002PointerScene **)&data_ov002_0207f628;
    if (func_02023c40() == 1) {
        nStep = 0x1800;
    } else {
        nStep = 0x1000;
    }
    func_ov002_02060b4c(&v, pIn, pCam);

    nDone = func_0202a818(&s->pointerWidget, nStep);
    if (nDone == 0) {
        s->pointerWidget.vPos = v;
        func_0202aa9c(&s->pointerWidget);
    }
    return nDone;
}
