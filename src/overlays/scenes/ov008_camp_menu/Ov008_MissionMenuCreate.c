/* Ov008_MissionMenuCreate -- Ov008_MissionMenuCreate: create the mission menu
 * context from the root heap (0x70 bytes, zeroed) and pick its first state.
 * The input header (+0x4) is initialised with the limits taken from the
 * config record data_ov008_0208fc8c (+0xa rows, +0xc columns); the "single
 * row" word (+0x28) mirrors game flag 0x200d and the menu state (+0x2c) is
 * cleared.  As a host (bHost) the scene object is created with arg 1, the
 * wipe to sub-state 0xd started, the wireless callback armed, the session
 * flag (+0x20) set and +0x28 taken from the first input tick; the next state
 * is Ov008_MissionMenuWaitReady.  As a guest with a live session (+0x28 set,
 * or a session that exists and is active) the next state is 0207be6c;
 * otherwise the scene object is created with arg 0, the callback disarmed,
 * the wipe to sub-state 0 started and 0207c1cc follows.  Either way the
 * text loader (+0x60) is released and re-pointed at "UI/mlt/mlt_%s.z".
 */

#include "nitro/types.h"

typedef void (*MissionState)(void);

#define FLAG_SINGLE_ROW 0x200d

typedef struct MissionMenuConfig {
    u8  pad_00[0xa];
    u16 nRows;                /* 0x0a */
    u16 nColumns;             /* 0x0c */
} MissionMenuConfig;

typedef struct MissionMenuLimits {
    short nRows;
    short nColumns;
} MissionMenuLimits;

typedef struct MissionMenuContext {
    void *sceneObject;        /* 0x00 */
    u16 inputHeader[13];      /* 0x04 */
    u8  pad_1e[2];
    u32 sessionReady;         /* 0x20 */
    u8  pad_24[4];
    u32 singleRowMode;        /* 0x28 */
    u32 menuState;            /* 0x2c */
    u8  pad_30[8];
    u32 nHandle;              /* 0x38 */
    u8  pad_3c[0x60 - 0x3c];
    u8  textLoader[0xc];      /* 0x60 */
    u8  tail[4];
} MissionMenuContext;

extern MissionMenuConfig data_ov008_0208fc8c;
extern MissionMenuContext *data_ov008_02090fa0;
extern u8 data_ov008_02090d1c;                                          /* scene object class */
extern const char gOv008UiMltMltTextPath[];                                 /* "UI/mlt/mlt_%s.z" */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern int   GameState_IsFlagSet(int nFlag);                                   /* GameState_IsFlagSet */
extern int   Header_InitWithLimits(void *pHeader, short *pLimits);               /* Header_InitWithLimits */
extern void *InstantiateClass(void *pClass, int nArg);                      /* InstantiateClass */
extern void  Ov008_StartWipeToSubState(int nSubState);                         /* Ov008_StartWipeToSubState */
extern void  Ov008_OpenMissionLobby(int bArm);                              /* Ov008_OpenMissionLobby */
extern int   Ov008_TickInputUpdate(void);                                  /* Ov008_TickInputUpdate */
extern int   Session_Exists(void);                                        /* Session_Exists */
extern int   Session_IsActive(void);                                        /* Session_IsActive */
extern void  Ov008_FreeResourceRecordBuffer(void *pLoader);                         /* release a text loader */
extern void  Ov008_VarTable_Load(void *pLoader, const char *pPath);      /* Ov008_Set_5c4c */
extern void  Ov008_MissionMenuWaitReady(void);                                  /* Ov008_MissionMenuWaitReady */
extern void  Ov008_MissionMenuArmWireless(void);
extern void  Ov008_MissionMenuTick(void);

MissionState Ov008_MissionMenuCreate(int bHost)
{
    MissionMenuLimits limits;
    MissionState pNext;

    {
        char *pSource = (char *)&data_ov008_0208fc8c;
        u16 nUpper = *(u16 *)(pSource + 12);
        u16 nLower = *(u16 *)(pSource + 10);
        *(volatile u16 *)&limits.nColumns = nUpper;
        *(volatile u16 *)&limits.nRows = nLower;
    }
    data_ov008_02090fa0 = NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(data_ov008_02090fa0, 0, sizeof(MissionMenuContext));
    data_ov008_02090fa0->nHandle = 0;
    data_ov008_02090fa0->singleRowMode = GameState_IsFlagSet(FLAG_SINGLE_ROW) != 0;
    data_ov008_02090fa0->menuState = 0;
    Header_InitWithLimits(data_ov008_02090fa0->inputHeader, &limits.nRows);
    if (bHost != 0) {
        data_ov008_02090fa0->sceneObject = InstantiateClass(&data_ov008_02090d1c, 1);
        Ov008_StartWipeToSubState(0xd);
        Ov008_OpenMissionLobby(1);
        data_ov008_02090fa0->sessionReady = 1;
        data_ov008_02090fa0->singleRowMode = Ov008_TickInputUpdate();
        pNext = Ov008_MissionMenuWaitReady;
    } else if (data_ov008_02090fa0->singleRowMode != 0 || (Session_Exists() != 0 && Session_IsActive() != 0)) {
        pNext = Ov008_MissionMenuArmWireless;
    } else {
        data_ov008_02090fa0->sceneObject = InstantiateClass(&data_ov008_02090d1c, 0);
        Ov008_OpenMissionLobby(0);
        Ov008_StartWipeToSubState(0);
        pNext = Ov008_MissionMenuTick;
    }
    Ov008_FreeResourceRecordBuffer(data_ov008_02090fa0->textLoader);
    Ov008_VarTable_Load(data_ov008_02090fa0->textLoader, gOv008UiMltMltTextPath);
    return pNext;
}
