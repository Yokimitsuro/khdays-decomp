/* func_ov008_0207cd04 -- Ov008_MissionMenuWaitReady: the mission menu state
 * after entry.  Applies the current selection (0208187c with 0207b7b4's row)
 * every frame and waits for the session phase (0207b8f0) to reach 2 and the
 * wipe sub-state (020816c0) to be 0xe.  Then the feature byte (+0x30) is
 * rebuilt exactly as in Ov008_MissionMenuEnter (rank bits from field 0x44e,
 * items 0x1c8 / 0x1c9) and applied; without parameters (+0x28) the four row
 * records are refilled from 0207b7e4's value, otherwise only row 0; the value
 * goes to Ov008_Fn_18a0, the text layers are reset and flushed, the local
 * player's row is highlighted (02081d88), menu state 4 requested with an
 * animated transition, the local row's icon selected, and the selection
 * cursor / repeat words (+0x32 / +0x34) set to 0x35 / 0.  Hands over to
 * 0207ce84.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef void (*MissionState)(void);

#define ROW_COUNT       4
#define FIELD_RANK      0x44e
#define ITEM_FEATURE_A  0x1c8
#define ITEM_FEATURE_B  0x1c9
#define SESSION_PHASE_READY 2
#define WIPE_SUBSTATE_DONE  0xe

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
    u8  pad_04[0x28 - 0x4];
    u32 parametersReady;      /* 0x28 */
    u32 menuState;            /* 0x2c */
    u8  nFeatures;            /* 0x30 */
    u8  pad_31;
    u16 nCursorText;          /* 0x32 */
    u16 nRepeatFrames;        /* 0x34 */
    u8  pad_36[0x40 - 0x36];
    Ov006RowInfo rows[ROW_COUNT]; /* 0x40 */
} MissionMenuContext;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern MissionMenuContext *data_ov008_02090fa0;
extern GameState *data_0204be18;
extern int   func_ov008_0207b7b4(void);                                  /* current row */
extern void  func_ov008_0208187c(int nSelection);
extern int   func_ov008_0207b8f0(void);                                  /* session phase */
extern int   func_ov008_020816c0(void);                                  /* wipe sub-state */
extern u32   func_020235d0(int nField, int nBits);                       /* GameState_GetField */
extern void  func_ov008_02081864(int nFeatures);
extern int   func_ov008_0207b7e4(void);
extern void  func_ov008_0207b960(int nRow, Ov006RowInfo *pOut);          /* fill a row record */
extern void  func_ov008_020818a0(int nValue);                            /* Ov008_Fn_18a0 */
extern void  func_ov008_02081da0(void);                                  /* Ov008_ResetTextLayers */
extern void  func_ov008_02081e08(void);                                  /* Ov008_FlushTextLayers */
extern u32   func_02030788(void);                                        /* Session_GetLocalPlayerIndex */
extern void  func_ov008_02081d88(int nRow);
extern void  func_ov008_020817c4(int nState, int bAnimate, int nValue);  /* Ov008_RequestMenuState */
extern void  func_ov008_020819a8(int nIcon);
extern void  func_ov008_0207ce84(void);                                  /* next state */

MissionState func_ov008_0207cd04(void)
{
    MissionState pNext;
    u8  nFeatures;
    u32 nRank;
    int nValue;
    u8  i;

    pNext = 0;
    func_ov008_0208187c(func_ov008_0207b7b4());
    if (func_ov008_0207b8f0() == SESSION_PHASE_READY) {
        if (func_ov008_020816c0() != WIPE_SUBSTATE_DONE) {
            return 0;
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
        if (data_ov008_02090fa0->parametersReady != 0) {
            func_ov008_0207b960(0, &data_ov008_02090fa0->rows[0]);
        } else {
            nValue = func_ov008_0207b7e4();
            for (i = 0; i < ROW_COUNT; i++) {
                func_ov008_0207b960(i, &data_ov008_02090fa0->rows[i]);
            }
        }
        func_ov008_020818a0(nValue);
        func_ov008_02081da0();
        func_ov008_02081e08();
        func_ov008_02081d88(func_02030788());
        func_ov008_020817c4(4, 1, 1);
        func_ov008_020819a8(data_ov008_02090fa0->rows[func_02030788()].icon);
        data_ov008_02090fa0->nCursorText = 0x35;
        data_ov008_02090fa0->nRepeatFrames = 0;
        pNext = func_ov008_0207ce84;
    }
    return pNext;
}
