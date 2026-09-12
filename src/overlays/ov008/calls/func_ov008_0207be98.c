/* func_ov008_0207be98 -- Ov008_MissionMenuEnter: the mission menu's entry
 * state.  Stays (returns 0) until Ov008_Fn_bb14 reports ready.  Then creates
 * the scene object (class data_ov008_02090d1c, arg 1), records whether the
 * session is ready, feeds 0207b7e4's result to Ov008_Fn_18a0, fills the four
 * row records (+0x40, 8 bytes each), reads the day counter and the rank
 * (GameState field 0x44e) and builds the feature byte (+0x30): bit 0 from
 * rank 2, bit 3 from rank 3, bit 4 from rank 4, bit 5 from rank 5, bit 2 when
 * item 0x1c8 is owned and bit 1 when item 0x1c9 is owned; applies it
 * (02081864), selects the current row's icon (020819a8), starts the wipe to
 * sub-state 0xe, clears the menu state (+0x2c) and hands over to 0207cd04.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef void (*MissionState)(void);

#define ROW_COUNT   4
#define FIELD_RANK  0x44e
#define ITEM_FEATURE_A 0x1c8
#define ITEM_FEATURE_B 0x1c9

typedef struct Ov006RowInfo {
    u16 id;                   /* 0x00 */
    u8  flag0;                /* 0x02 */
    u8  flag1;                /* 0x03 */
    signed char icon;         /* 0x04 */
    signed char sprite;       /* 0x05 */
    u8  pad6[2];
} Ov006RowInfo;

typedef struct MissionMenuContext {
    void *sceneObject;        /* 0x00 */
    u8  pad_04[0x20 - 0x4];
    u32 sessionReady;         /* 0x20 */
    u8  pad_24[8];
    u32 menuState;            /* 0x2c */
    u8  nFeatures;            /* 0x30 */
    u8  pad_31[0x40 - 0x31];
    Ov006RowInfo rows[ROW_COUNT]; /* 0x40 */
} MissionMenuContext;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern u8 data_ov008_02090d1c;                                          /* scene object class */
extern MissionMenuContext *data_ov008_02090fa0;
extern GameState *data_0204be18;
extern int   func_ov008_0207bb14(void);                                  /* Ov008_Fn_bb14: ready */
extern void *func_02023930(void *pClass, int nArg);                      /* InstantiateClass */
extern int   func_02030694(void);                                        /* Session_IsReady */
extern int   func_ov008_0207b7e4(void);
extern void  func_ov008_020818a0(int nValue);                            /* Ov008_Fn_18a0 */
extern void  func_ov008_0207b960(int nRow, Ov006RowInfo *pOut);          /* fill a row record */
extern u32   func_020235d0(int nField, int nBits);                       /* GameState_GetField */
extern void  func_ov008_02081864(int nFeatures);
extern u16   func_ov008_0207b138(void);                                  /* current row */
extern void  func_ov008_020819a8(int nIcon);
extern void  func_ov008_0208174c(int nSubState);                         /* Ov008_StartWipeToSubState */
extern void  func_ov008_0207cd04(void);                                  /* next state */

MissionState func_ov008_0207be98(void)
{
    MissionState pNext;
    int i;
    u8  nFeatures;
    u32 nRank;

    pNext = 0;
    if (func_ov008_0207bb14() != 0) {
        data_ov008_02090fa0->sceneObject = func_02023930(&data_ov008_02090d1c, 1);
        data_ov008_02090fa0->sessionReady = func_02030694();
        func_ov008_020818a0(func_ov008_0207b7e4());
        for (i = 0; i < ROW_COUNT; i++) {
            func_ov008_0207b960(i, &data_ov008_02090fa0->rows[i]);
        }
        nFeatures = 0;
        func_020235d0(0, 9);
        nRank = func_020235d0(FIELD_RANK, 3) & 0xff;
        if (nRank >= 2) {
            nFeatures |= 0x01;
        }
        if (nRank >= 3) {
            nFeatures |= 0x08;
        }
        if (nRank >= 4) {
            nFeatures |= 0x10;
        }
        if (nRank >= 5) {
            nFeatures |= 0x20;
        }
        if (data_0204be18->aItemCount[ITEM_FEATURE_A] != 0) {
            nFeatures |= 0x04;
        }
        if (data_0204be18->aItemCount[ITEM_FEATURE_B] != 0) {
            nFeatures |= 0x02;
        }
        data_ov008_02090fa0->nFeatures = nFeatures;
        func_ov008_02081864(nFeatures);
        func_ov008_020819a8(data_ov008_02090fa0->rows[func_ov008_0207b138()].icon);
        func_ov008_0208174c(0xe);
        data_ov008_02090fa0->menuState = 0;
        pNext = func_ov008_0207cd04;
    }
    return pNext;
}
