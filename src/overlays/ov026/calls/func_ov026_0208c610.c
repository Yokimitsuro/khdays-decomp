/* func_ov026_0208c610 -- Ov008_GrantRewardItem: give the reward nReward
 * (0 .. 0x14) to the player.  Each reward adds a fixed number of one item to
 * the item counts of the game state (0204be18, +0x810), caps the count at
 * 99 and sets the item's "owned" flag (0x4db + item).  Rewards 0 .. 4 and 7,
 * 8, 10, 11, 16 are the synthesis materials 0x5d .. 0x6a (3 each, 2 for
 * 0x5e / 0x64 / 0x6a / 0x61), 5, 6, 9, 12 .. 15, 17 .. 19 the recovery
 * items 2 .. 0xb (10 each, 5 for 0xb / 9) and 20 item 0x13e (2).  Codegen:
 * one static inline helper per case (the state pointer is re-read after the
 * byte store); every case returns.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ITEM_COUNT_MAX  99
#define FLAG_ITEM_OWNED 0x4db

typedef struct GameState {
    u8 pad_0000[0x810];
    u8 aItemCount[0x8d0];     /* 0x810 */
} GameState;

extern GameState *data_0204be18;                                       /* g_pTallySource */
extern void func_020235a8(int nFlag);                                  /* GameState_SetFlag */

static inline void Ov008_AddItemCount(int nItem, int nCount)
{
    data_0204be18->aItemCount[nItem] += nCount;
    if (data_0204be18->aItemCount[nItem] > ITEM_COUNT_MAX) {
        data_0204be18->aItemCount[nItem] = ITEM_COUNT_MAX;
    }
    func_020235a8(FLAG_ITEM_OWNED + nItem);
}

void func_ov026_0208c610(int nReward)
{
    switch (nReward) {
    case 0:
        Ov008_AddItemCount(0x5d, 3);
        return;
    case 1:
        Ov008_AddItemCount(0x69, 3);
        return;
    case 2:
        Ov008_AddItemCount(0x63, 3);
        return;
    case 3:
        Ov008_AddItemCount(0x5e, 2);
        return;
    case 4:
        Ov008_AddItemCount(0x64, 2);
        return;
    case 5:
        Ov008_AddItemCount(2, 10);
        return;
    case 6:
        Ov008_AddItemCount(5, 10);
        return;
    case 7:
        Ov008_AddItemCount(0x60, 3);
        return;
    case 8:
        Ov008_AddItemCount(0x66, 3);
        return;
    case 9:
        Ov008_AddItemCount(0xa, 10);
        return;
    case 10:
        Ov008_AddItemCount(0x6a, 2);
        return;
    case 11:
        Ov008_AddItemCount(0x61, 2);
        return;
    case 12:
        Ov008_AddItemCount(3, 10);
        return;
    case 13:
        Ov008_AddItemCount(6, 10);
        return;
    case 14:
        Ov008_AddItemCount(8, 10);
        return;
    case 15:
        Ov008_AddItemCount(0xb, 5);
        return;
    case 16:
        Ov008_AddItemCount(0x67, 3);
        return;
    case 17:
        Ov008_AddItemCount(4, 10);
        return;
    case 18:
        Ov008_AddItemCount(7, 10);
        return;
    case 19:
        Ov008_AddItemCount(9, 5);
        return;
    case 20:
        Ov008_AddItemCount(0x13e, 2);
        return;
    }
}
