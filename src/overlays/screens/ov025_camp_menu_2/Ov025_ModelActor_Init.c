/* Ov025_ModelActor_Init -- Ov025_ModelActor_Init: initialise the menu's character model actor
 * (twin of ov008 0205a3dc).  The 0x528-byte object is cleared, its zoom (+0x1b0) set by the
 * frame-rate flag (02023c40: 0x1000 / 0xaaa / 0x2000), the projection defaults loaded (02023c60)
 * with the three view words 0x785 / 0x785 / 0x2800, the scene id kept (+0x524), the camera
 * matrices committed (02023cc0), the matrix (+0x4d4) and graphics state (+0x4fc) captured.  The
 * sequence path is ba/ch/ro/def_hb.p.z for scene 0, def.p.z for scenes 5 and 0x10..0x12 and
 * def_h.p.z otherwise (0202a634 / 0202accc); the controller (+0x58) gets the matrix re-read
 * callback 0208c868, the model file is loaded for the character kind (0208c8e4) and the
 * dictionary of the controller's resource (+0x5c, at +0x40 of it) searched for "ro_w_tg_R"
 * (02016f10, -1 without a resource); then
 * the panel sub-object (+0x31c) is cleared, set up for the scene (0208c434) and its id summary
 * (+0x480) built (0208c65c), its byte 0 taking bit 0 when its byte 1 is set.  Codegen: the "ro"
 * name in a local shared by the three OS_SPrintf calls (as the ov008 twin). */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov025ModelActor {
    u8   pad_000[0x18];
    int  nField018;           /* 0x018 */
    u8   pad_01c[8];
    int  nField024;           /* 0x024 */
    int  nField028;           /* 0x028 */
    u8   pad_02c[0xc];
    u8   sequence[0x20];      /* 0x038: the animation sequence (0202a634) */
    int  nCtrl058;            /* 0x058: the controller (02014e18) */
    void *pResource;          /* 0x05c: the loaded model resource */
    u8   ctrl060[0x24];       /* 0x060 */
    void *pOwner;             /* 0x084 */
    u8   pad_088[0x90];
    u8   blendTable[0x2c];    /* 0x118: 0202accc */
    int  nField144;           /* 0x144 */
    u8   pad_148[4];
    int  nDictIndex;          /* 0x14c: "ro_w_tg_R" in the model's dictionary, -1 when absent */
    u8   pad_150[0x60];
    int  nZoom;               /* 0x1b0: 0x1000 / 0xaaa / 0x2000 by the frame-rate flag */
    void *pModelFile;         /* 0x1b4 */
    u8   pad_1b8[0x31c - 0x1b8];
    u8   panel[0x164];        /* 0x31c: the menu panel sub-object (0208c434) */
    u8   summary[0x54];       /* 0x480: the panel-id summary (0208c65c) */
    u8   weaponRow[0x20];     /* 0x4d4: the packed weapon row (ov002 020522c8); byte 0 = the character flags */
    u8   matrix[0x28];        /* 0x4f4: 020110f4 */
    u8   gfxState[8];         /* 0x51c: GFXi_SaveStateTo */
    int  nSceneId;            /* 0x524 */
} Ov025ModelActor;            /* 0x528 */

typedef struct Ov025ModelParams {
    int  nSceneId;            /* 0x00 */
} Ov025ModelParams;

extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern void  Camera_CommitMatrices(Ov025ModelActor *pActor);                /* Camera_CommitMatrices */
extern void  NNS_GfdGetFrmTexVramState(void *pMatrix);
extern void  GFXi_SaveStateTo(void *pState);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void  BindAnimTrack(void *pSequence, int nTrack, void *pBlend, int nArg); /* BindAnimTrack */
extern void  NNS_G3dRenderObjSetCallBack(void *pController, void *pCallback, int nA, int nB, int nC); /* Obj_SetValueAndTwoBytes */
extern void  Ov025_RefreshMatchingMatrices(int nNode);                        /* the matrix re-read callback */
extern void  Ov025_LoadCharacterMsgAndWeapon(Ov025ModelActor *pActor, int nSceneId, int nKind); /* load the model file */
extern u32   NNS_G3dGetResDictIdxByName(void *pDictionary, const void *pszName); /* ResDict_FindIndexByName */
extern void  Ov025_ClearBytes01AndWord160(void *pPanel);                     /* clear the panel header */
extern void  Ov025_Menu_InitPanelSubObject(u8 *pPanel, void *pResBase, int nSubId, int nSceneId, u32 nCharFlags, int nSlot); /* Ov008_Menu_InitPanelSubObject */
extern void  Ov025_BuildPanelIdSummary(void *pPanel, void *pSummary, int nSrc); /* build the panel-id summary */
extern u8    gPartyMembers[];                                       /* kOv022KindRecords: byte 4 = the character kind */
extern const char gOv025RoName[];                            /* "ro" */
extern const char gOv025BaChDefHbPackPathFmt[];                            /* "ba/ch/%s/def_hb.p.z" */
extern const char gOv025BaChDefPackPathFmt[];                            /* "ba/ch/%s/def.p.z" */
extern const char gOv025BaChDefHPackPathFmt[];                            /* "ba/ch/%s/def_h.p.z" */
extern const char gOv025RoWTgRName[];                            /* "ro_w_tg_R" */

void Ov025_ModelActor_Init(Ov025ModelActor *pActor, Ov025ModelParams *pParams)
{
    char szPath[0x80];
    const char *pszName;
    void *pDict;

    MI_CpuFill8(pActor, 0, 0x528);
    switch (GetFrameRateMode()) {
    case 0: pActor->nZoom = 0x1000; break;
    case 1: pActor->nZoom = 0xaaa; break;
    case 2: pActor->nZoom = 0x2000; break;
    }
    Projection_LoadDefaults(pActor);
    pActor->nField018 = 0x785;
    pActor->nField024 = 0x785;
    pActor->nField028 = 0x2800;
    pActor->nSceneId = pParams->nSceneId;
    Camera_CommitMatrices(pActor);
    NNS_GfdGetFrmTexVramState(pActor->matrix);
    GFXi_SaveStateTo(pActor->gfxState);
    pszName = gOv025RoName;
    switch (pParams->nSceneId) {
    case 0:
        OS_SPrintf(szPath, gOv025BaChDefHbPackPathFmt, pszName, pszName);
        break;
    case 5:
    case 0x10:
    case 0x11:
    case 0x12:
        OS_SPrintf(szPath, gOv025BaChDefPackPathFmt, pszName, pszName);
        break;
    default:
        OS_SPrintf(szPath, gOv025BaChDefHPackPathFmt, pszName, pszName);
        break;
    }
    RegisterSeqAndInit(pActor->sequence, szPath, 1, 0xe);
    BindAnimTrack(pActor->sequence, 0, pActor->blendTable, 0);
    pActor->pOwner = pActor;
    NNS_G3dRenderObjSetCallBack(&pActor->nCtrl058, Ov025_RefreshMatchingMatrices, 0, 6, 3);
    Ov025_LoadCharacterMsgAndWeapon(pActor, pParams->nSceneId, gPartyMembers[4]);
    pDict = pActor->pResource != 0 ? (u8 *)pActor->pResource + 0x40 : 0;
    pActor->nDictIndex = pDict != 0 ? NNS_G3dGetResDictIdxByName(pDict, gOv025RoWTgRName) : -1;
    pActor->nField144 = 1;
    Ov025_ClearBytes01AndWord160(pActor->panel);
    Ov025_Menu_InitPanelSubObject(pActor->panel, pActor->pModelFile, 0, pParams->nSceneId, pActor->weaponRow[0], 2);
    Ov025_BuildPanelIdSummary(pActor->panel, pActor->summary, 0);
    if (*(signed char *)&pActor->panel[1] != 0) {
        pActor->panel[0] |= 1;
    }
}
