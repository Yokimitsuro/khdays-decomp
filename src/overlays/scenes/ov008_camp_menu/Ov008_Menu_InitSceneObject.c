
#include "nitro/types.h"
#include "game/engine.h"

extern int  MI_CpuFill8(void *dest, int data, int size);
extern void Ov008_InitLayoutMetrics(int *obj);
extern void Camera_CommitMatrices(void *obj);
extern void NNS_GfdGetFrmTexVramState(void *p);
extern void GFXi_SaveStateTo(void *p);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void BindAnimTrack(void *seq, int b, void *track, int d);
extern void NNS_G3dRenderObjSetCallBack(int a, int b, int c, int d, int e);
extern void Ov008_Menu_LoadSceneText(int obj, int sceneId, int c);
extern void Ov008_Menu_BindScenePanels(int obj, int *param2);
extern void Ov008_RefreshMatchingMatrices(void);
typedef struct { int f0; unsigned char pad[0x30]; } SceneParam;
extern SceneParam data_ov008_0208e9c4[];
extern char gOv008BaChDefHbPackPathFmt[];
extern char gOv008BaChDefPackPathFmt[];
extern char gOv008BaChDefHPackPathFmt[];
extern int  gPartyMembers;

/* Ov008_Menu_InitSceneObject: initialize the menu scene object and resources. */
void Ov008_Menu_InitSceneObject(int *param_1, int *param_2)
{
    int sceneId;
    int val;
    unsigned short h;
    u32 auStack[32];

    MI_CpuFill8(param_1, 0, 0x528);
    switch (GetFrameRateMode()) {
    case 0: param_1[0x6c] = 0x1000; break;
    case 1: param_1[0x6c] = 0xaaa; break;
    case 2: param_1[0x6c] = 0x2000; break;
    }
    Projection_LoadDefaults(param_1);
    param_1[6] = 0x785;
    param_1[9] = 0x785;
    param_1[10] = 0x2800;
    param_1[0x149] = *param_2;
    Ov008_InitLayoutMetrics(param_1);
    Camera_CommitMatrices(param_1);
    NNS_GfdGetFrmTexVramState(param_1 + 0x13d);
    GFXi_SaveStateTo(param_1 + 0x147);

    sceneId = *param_2;
    val = (int)data_ov008_0208e9c4;
    val = *(int *)(val + sceneId * 0x34);
    switch (*(int *)param_2) {
    case 0:
        OS_SPrintf((char *)auStack, gOv008BaChDefHbPackPathFmt, val, val);
        break;
    case 5:
    case 0x10:
    case 0x11:
    case 0x12:
        OS_SPrintf((char *)auStack, gOv008BaChDefPackPathFmt, val, val);
        break;
    default:
        OS_SPrintf((char *)auStack, gOv008BaChDefHPackPathFmt, val, val);
        break;
    }

    RegisterSeqAndInit((void *)(param_1 + 0xe), auStack, 1, 0xe);
    BindAnimTrack((void *)(param_1 + 0xe), 0, (void *)(param_1 + 0x46), 0);

    sceneId = *param_2;
    switch (sceneId) {
    case 1:    h = 0xf8e4; break;
    case 0xe:  h = 0x71c; break;
    case 5:    h = 0x71c; break;
    case 0xb:  h = 0x71c; break;
    case 0x13: h = 0x71c; break;
    default:   h = 0; break;
    }
    *(u16 *)((char *)param_1 + 0xb4) = h;
    *(u16 *)((char *)param_1 + 0x38) |= 0x20;
    param_1[0x21] = (int)param_1;
    NNS_G3dRenderObjSetCallBack((int)(param_1 + 0x16), (int)&Ov008_RefreshMatchingMatrices, 0, 6, 3);
    Ov008_Menu_LoadSceneText((int)param_1, *param_2, *(u8 *)((char *)&gPartyMembers + 4));
    Ov008_Menu_BindScenePanels((int)param_1, (int *)param_2);
}
