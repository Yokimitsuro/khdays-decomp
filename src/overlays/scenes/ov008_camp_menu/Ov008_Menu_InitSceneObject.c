
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
extern void Ov008_Menu_LoadSceneText(int obj, int nCharacter, int c);
extern void Ov008_Menu_BindScenePanels(int obj, int *pCharacter);
extern void Ov008_RefreshMatchingMatrices(void);
/* One per character: its data folder's code (ba/ch/<code>/), then the names of its weapon nodes
 * (Ov008_Menu_BindScenePanels looks them up). */
typedef struct { int pszFolder; unsigned char aWeaponNodeNames[0x30]; } Ov008CampCharacterRecord;
extern Ov008CampCharacterRecord gOv008CampCharacterRecords[];
extern char gOv008BaChDefHbPackPathFmt[];
extern char gOv008BaChDefPackPathFmt[];
extern char gOv008BaChDefHPackPathFmt[];
extern int  gPartyMembers;

/* Ov008_Menu_InitSceneObject: set up the camp's 3D scene for its character (*pCharacter, member 0's,
 * kept at +0x524): the camera, the character's model pack from its data folder (def_hb.p.z for
 * Roxas, def.p.z for Sora, Mickey, Donald and Goofy, def_h.p.z for the others), the camera's turn by
 * character (+0xb4), the render callback, the texts and the weapon panels. */
void Ov008_Menu_InitSceneObject(int *pScene, int *pCharacter)
{
    int nCharacter;
    int pszFolder;
    unsigned short nTurn;
    u32 szPath[32];

    MI_CpuFill8(pScene, 0, 0x528);
    switch (GetFrameRateMode()) {
    case 0: pScene[0x6c] = 0x1000; break;
    case 1: pScene[0x6c] = 0xaaa; break;
    case 2: pScene[0x6c] = 0x2000; break;
    }
    Projection_LoadDefaults(pScene);
    pScene[6] = 0x785;
    pScene[9] = 0x785;
    pScene[10] = 0x2800;
    pScene[0x149] = *pCharacter;
    Ov008_InitLayoutMetrics(pScene);
    Camera_CommitMatrices(pScene);
    NNS_GfdGetFrmTexVramState(pScene + 0x13d);
    GFXi_SaveStateTo(pScene + 0x147);

    nCharacter = *pCharacter;
    pszFolder = (int)gOv008CampCharacterRecords;
    pszFolder = *(int *)(pszFolder + nCharacter * 0x34);
    switch (*(int *)pCharacter) {
    case 0:
        OS_SPrintf((char *)szPath, gOv008BaChDefHbPackPathFmt, pszFolder, pszFolder);
        break;
    case 5:
    case 0x10:
    case 0x11:
    case 0x12:
        OS_SPrintf((char *)szPath, gOv008BaChDefPackPathFmt, pszFolder, pszFolder);
        break;
    default:
        OS_SPrintf((char *)szPath, gOv008BaChDefHPackPathFmt, pszFolder, pszFolder);
        break;
    }

    RegisterSeqAndInit((void *)(pScene + 0xe), szPath, 1, 0xe);
    BindAnimTrack((void *)(pScene + 0xe), 0, (void *)(pScene + 0x46), 0);

    nCharacter = *pCharacter;
    switch (nCharacter) {
    case 1:    nTurn = 0xf8e4; break;
    case 0xe:  nTurn = 0x71c; break;
    case 5:    nTurn = 0x71c; break;
    case 0xb:  nTurn = 0x71c; break;
    case 0x13: nTurn = 0x71c; break;
    default:   nTurn = 0; break;
    }
    *(u16 *)((char *)pScene + 0xb4) = nTurn;
    *(u16 *)((char *)pScene + 0x38) |= 0x20;
    pScene[0x21] = (int)pScene;
    NNS_G3dRenderObjSetCallBack((int)(pScene + 0x16), (int)&Ov008_RefreshMatchingMatrices, 0, 6, 3);
    Ov008_Menu_LoadSceneText((int)pScene, *pCharacter, *(u8 *)((char *)&gPartyMembers + 4));
    Ov008_Menu_BindScenePanels((int)pScene, (int *)pCharacter);
}
