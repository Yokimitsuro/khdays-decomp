/* func_ov025_02099b90 -- Ov008_BeginSaveToSlot: prepare and start a save into
 * slot nSlot.  Copies the 9-bit day counter (field 0) into field 0x452, rolls
 * a random reward tier for the slot (0..2 while the day is below 26, else
 * 0..3) into the slot's entry (+0x28 + 0x1c * slot) and fields 0xc4b (tier) /
 * 0xc98 (slot); bumps the save counter (+0x1ef8) into the two 16-bit halves of
 * fields 0xc77 / 0xc87; latches the two "changed" flags (0x18bd / 0x18c9) into
 * bytes +0x1efc / +0x1efd and clears them; starts the card write, marks card
 * op 3 and returns the write's result (kept live across the store: that is
 * why the constant 3 goes to r1).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008SaveTierEntry {
    u32 nTier;                /* +0 (= save entry +0x18) */
    u8  pad_04[0x1c - 0x4];
} Ov008SaveTierEntry;

typedef struct Ov008SaveMenu {
    u8  pad_0000[0x28];
    Ov008SaveTierEntry aTier[3]; /* 0x028: the save entries' reward tier words, stride 0x1c */
    u8  pad_007c[0x238 - 0x7c];
    int nCardOp;              /* 0x238 */
    u8  pad_023c[0x1ef8 - 0x23c];
    u32 nSaveCount;           /* 0x1ef8 */
    u8  bChangedA;            /* 0x1efc */
    u8  bChangedB;            /* 0x1efd */
} Ov008SaveMenu;

#define FIELD_DAY        0
#define FIELD_DAY_COPY   0x452
#define FIELD_TIER       0xc4b
#define FIELD_TIER_SLOT  0xc98
#define FIELD_COUNT_HI   0xc77
#define FIELD_COUNT_LO   0xc87
#define FLAG_CHANGED_A   0x18bd
#define FLAG_CHANGED_B   0x18c9
#define CARD_OP_TRANSFER 3
#define TIER_DAY_SPLIT   26

extern u32  func_020235d0(int nField, int nBits);                       /* GameState_GetField */
extern void func_020235e8(int nField, int nBits, int nValue);           /* GameState_SetField */
extern u32  func_02023e80(u16 nRange);                                  /* Rand16NextScaled */
extern int  func_02023588(int nFlag);                                   /* GameState_IsFlagSet */
extern void func_020235bc(int nFlag);                                   /* GameState_ClearFlag */
extern int func_ov025_020b0d00(int nSlot);                             /* Ov008_CommitSaveToSlot */

int func_ov025_02099b90(Ov008SaveMenu *pMenu, u32 nSlot)
{
    u32 nTier;
    u32 nCount;
    int nRange;
    int nResult;

    func_020235e8(FIELD_DAY_COPY, 9, (u16)func_020235d0(FIELD_DAY, 9));
    nRange = func_020235d0(FIELD_DAY, 9) >= TIER_DAY_SPLIT ? 3 : 2;
    pMenu->aTier[nSlot].nTier = func_02023e80((u16)nRange);
    nTier = pMenu->aTier[nSlot].nTier;
    func_020235e8(FIELD_TIER, 2, (u16)nTier);
    func_020235e8(FIELD_TIER_SLOT, 2, (u16)nSlot);
    nCount = pMenu->nSaveCount + 1;
    func_020235e8(FIELD_COUNT_HI, 16, (u16)(nCount >> 16));
    func_020235e8(FIELD_COUNT_LO, 16, (u16)nCount);
    pMenu->bChangedA = func_02023588(FLAG_CHANGED_A);
    pMenu->bChangedB = func_02023588(FLAG_CHANGED_B);
    func_020235bc(FLAG_CHANGED_A);
    func_020235bc(FLAG_CHANGED_B);
    nResult = func_ov025_020b0d00(nSlot);
    pMenu->nCardOp = CARD_OP_TRANSFER;
    return nResult;
}
