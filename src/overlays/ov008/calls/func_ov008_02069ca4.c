/* func_ov008_02069ca4 -- Ov008_LoadItemCounts: fill the item menu's per-item
 * remaining counts (+0x4e, 25 halfwords) from the game state fields.  When
 * the player owns no copy of item 0x1a0 (GameState 0x810 + id) field 0x3c29
 * is first set to 1.  Counts 8 and 9 are the 2-bit fields 0x37c7 / 0x35bf
 * modulo 3; count 7 is not loaded.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed short   s16;

#define ITEM_LAST_UNLOCK 0x1a0
#define FIELD_LAST_UNLOCK 0x3c29

typedef struct Ov008SelCtx {
    u8  pad_0000[0x4c];
    s16 sel;                  /* 0x4c: highlighted item */
    s16 counts[0x19];         /* 0x4e: per-item remaining counts */
} Ov008SelCtx;

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern GameState *data_0204be18;
extern Ov008SelCtx *func_ov008_02050cd4(void);                    /* Ov008_GetMenuContext */
extern void func_020235e8(int nField, int nBits, u32 nValue);      /* GameState_SetField */
extern u32  func_020235d0(int nField, int nBits);                  /* GameState_GetField */

void func_ov008_02069ca4(void)
{
    Ov008SelCtx *pCtx;

    pCtx = func_ov008_02050cd4();
    if (data_0204be18->aItemCount[ITEM_LAST_UNLOCK] == 0) {
        func_020235e8(FIELD_LAST_UNLOCK, 2, 1);
    }
    pCtx->counts[0] = func_020235d0(0x37c4, 1);
    pCtx->counts[1] = func_020235d0(0x37bf, 1);
    pCtx->counts[2] = func_020235d0(0x37c0, 2);
    pCtx->counts[3] = func_020235d0(0x37c3, 1);
    pCtx->counts[4] = func_020235d0(0x37c2, 1);
    pCtx->counts[5] = func_020235d0(0x37c5, 1);
    pCtx->counts[6] = func_020235d0(0x37c6, 1);
    pCtx->counts[8] = func_020235d0(0x37c7, 2) % 3;
    pCtx->counts[9] = func_020235d0(0x35bf, 2) % 3;
    pCtx->counts[10] = func_020235d0(0x3c15, 1);
    pCtx->counts[11] = func_020235d0(0x3c16, 1);
    pCtx->counts[12] = func_020235d0(0x3c17, 2);
    pCtx->counts[13] = func_020235d0(0x3c19, 2);
    pCtx->counts[14] = func_020235d0(0x3c1b, 2);
    pCtx->counts[15] = func_020235d0(0x3c1d, 2);
    pCtx->counts[16] = func_020235d0(0x3c26, 1);
    pCtx->counts[17] = func_020235d0(0x3c1f, 1);
    pCtx->counts[18] = func_020235d0(0x3c20, 1);
    pCtx->counts[19] = func_020235d0(0x35c1, 2);
    pCtx->counts[20] = func_020235d0(0x3c23, 2);
    pCtx->counts[21] = func_020235d0(0x3c21, 2);
    pCtx->counts[22] = func_020235d0(0x3c25, 1);
    pCtx->counts[23] = func_020235d0(0x3c27, 2);
    pCtx->counts[24] = func_020235d0(FIELD_LAST_UNLOCK, 2);
}
