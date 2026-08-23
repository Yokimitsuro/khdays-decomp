/*
 * Ov002_SceneStepPanel - the panel scene's per-frame step.
 *
 * Nothing runs while the owning system reports it has no slot. Otherwise the
 * camera is committed with the tight bounds the flat widgets are drawn in, the
 * counter half is stepped and drawn while it is in one of its three live
 * states, and the backdrop while it is in one of its two.
 *
 * The camera is then committed again with the wide bounds the world markers
 * need, the markers and the HUD are drawn, and the camera is committed one last
 * time from the actor itself.
 *
 * ARM.
 */

typedef struct {
    char pad000[4];
    char aCamera[0x38];
    char pad03c[0xa8];
    int nHeaderFrame;
    char pad0e8[0xc70];
    int nCounterState;
    char padd5c[0x290];
    int nBackdropState;
} Ov002PanelScene;

extern int data_ov002_0207f628;

extern int func_ov022_02083f0c(void);
extern void *func_ov002_0204cb68(void);
extern void func_02023d70(void *pCam, int a, int b, int c, int d);
extern void func_02023cc0(void *pCam);

extern void func_ov002_0205f82c(void);
extern void func_ov002_0205fda4(void);
extern void func_ov002_0205ffd4(void);
extern void func_ov002_02060254(void);
extern void func_ov002_02060508(void);
extern void func_ov002_02060800(void);
extern void func_ov002_020609a8(void);
extern void func_ov002_02060eb0(void *pCam);
extern void func_ov002_02061184(void);
extern void func_ov002_02061308(void *pCam);
extern void func_ov002_02061474(void);

void *func_ov002_020616a0(void)
{
    Ov002PanelScene *s;
    void *pCam;

    s = *(Ov002PanelScene **)&data_ov002_0207f628;
    if (func_ov022_02083f0c() == -1) {
        return 0;
    }
    pCam = func_ov002_0204cb68();
    func_02023d70(s->aCamera, 0x3b33, -0x3b33, -0x4d9a, 0x4d9a);

    switch (s->nCounterState) {
    case 0:
    case 1:
    case 2:
        switch (s->nHeaderFrame) {
        case 0:
        case 1:
            func_ov002_0205f82c();
            break;
        }
        func_ov002_02060508();
        func_ov002_02060254();
        break;
    }
    switch (s->nBackdropState) {
    case 0:
    case 1:
        func_ov002_020609a8();
        break;
    }
    func_ov002_0205fda4();
    func_ov002_0205ffd4();
    func_ov002_02060800();

    func_02023d70(s->aCamera, 0x5f000, -0x5f000, -0x7f000, 0x7f000);
    func_ov002_02060eb0(pCam);
    func_ov002_02061184();
    func_ov002_02061308(pCam);
    func_ov002_02061474();
    func_02023cc0(pCam);
    return 0;
}
