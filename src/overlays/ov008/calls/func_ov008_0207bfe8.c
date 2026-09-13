/* func_ov008_0207bfe8 -- Ov008_MissionMenuCreate: create the mission menu
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
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
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
extern const char data_ov008_02090cf8[];                                 /* "UI/mlt/mlt_%s.z" */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern int   func_02023588(int nFlag);                                   /* GameState_IsFlagSet */
extern int   func_02036298(void *pHeader, short *pLimits);               /* Header_InitWithLimits */
extern void *func_02023930(void *pClass, int nArg);                      /* InstantiateClass */
extern void  func_ov008_0208174c(int nSubState);                         /* Ov008_StartWipeToSubState */
extern void  func_ov008_0207b84c(int bArm);                              /* Ov008_ArmWirelessCallback */
extern int   func_ov008_0207b3d0(void);                                  /* Ov008_TickInputUpdate */
extern int   func_02030640(void);                                        /* Session_Exists */
extern int   func_02030670(void);                                        /* Session_IsActive */
extern void  func_ov008_02055c74(void *pLoader);                         /* release a text loader */
extern void  func_ov008_02055c4c(void *pLoader, const char *pPath);      /* Ov008_Set_5c4c */
extern void  func_ov008_0207cd04(void);                                  /* Ov008_MissionMenuWaitReady */
extern void  func_ov008_0207be6c(void);
extern void  func_ov008_0207c1cc(void);

MissionState func_ov008_0207bfe8(int bHost)
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
    data_ov008_02090fa0->singleRowMode = func_02023588(FLAG_SINGLE_ROW) != 0;
    data_ov008_02090fa0->menuState = 0;
    func_02036298(data_ov008_02090fa0->inputHeader, &limits.nRows);
    if (bHost != 0) {
        data_ov008_02090fa0->sceneObject = func_02023930(&data_ov008_02090d1c, 1);
        func_ov008_0208174c(0xd);
        func_ov008_0207b84c(1);
        data_ov008_02090fa0->sessionReady = 1;
        data_ov008_02090fa0->singleRowMode = func_ov008_0207b3d0();
        pNext = func_ov008_0207cd04;
    } else if (data_ov008_02090fa0->singleRowMode != 0 || (func_02030640() != 0 && func_02030670() != 0)) {
        pNext = func_ov008_0207be6c;
    } else {
        data_ov008_02090fa0->sceneObject = func_02023930(&data_ov008_02090d1c, 0);
        func_ov008_0207b84c(0);
        func_ov008_0208174c(0);
        pNext = func_ov008_0207c1cc;
    }
    func_ov008_02055c74(data_ov008_02090fa0->textLoader);
    func_ov008_02055c4c(data_ov008_02090fa0->textLoader, data_ov008_02090cf8);
    return pNext;
}
