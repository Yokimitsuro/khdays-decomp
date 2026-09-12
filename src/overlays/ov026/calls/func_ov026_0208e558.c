/* func_ov026_0208e558 -- Ov008_CountAffordableRecords: for the two reward lists
 * (param table entries 3 and 4, 0x34-byte records) count the records that are
 * either already flagged (game flag 0x8db + 0x28 * list + index) or affordable
 * (price at +8 no more than the matching reward total from the game state) and
 * enabled (+0x20).  Writes one u16 count per list into aCount.
 *
 * `nFlagBase + (int)j`: with the unsigned j mwcc strength-reduces the flag id into
 * its own induction variable and spills the base; the signed add keeps the ROM's
 * base register + j.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define LIST_COUNT      2
#define LIST_FIRST      3
#define FLAG_REWARD_BASE 0x8db
#define FLAGS_PER_LIST  0x28

typedef struct Ov008RewardRecord {
    u8  pad_00[8];
    u32 nPrice;               /* 0x08 */
    u8  pad_0c[0x20 - 0xc];
    int bEnabled;             /* 0x20 */
    u8  pad_24[0x34 - 0x24];
} Ov008RewardRecord;

typedef struct Ov008ParamTable {
    u32 aCount[5];                    /* 0x00 */
    Ov008RewardRecord *apRecords[5];  /* 0x14 */
} Ov008ParamTable;

typedef struct GameState {
    u8  pad_0000[0x1968];
    u16 mode8RewardTotal;     /* 0x1968 */
    u16 otherRewardTotal;     /* 0x196a */
} GameState;

extern GameState *data_0204be18;
extern Ov008ParamTable *data_ov026_0209136c;
extern int func_020235d0(int nField, int nBits);                         /* GameState_GetField */
extern int func_02023588(int nFlag);                                     /* GameState_IsFlagSet */

void func_ov026_0208e558(u16 *aCount)
{
    int i;
    u16 aTotal[LIST_COUNT];
    u32 j;
    int nList;
    int nFlagBase;

    func_020235d0(0x44e, 3);
    i = 0;
    aTotal[0] = data_0204be18->otherRewardTotal;
    aTotal[1] = data_0204be18->mode8RewardTotal;
    nFlagBase = FLAG_REWARD_BASE;
    do {
        aCount[i] = 0;
        nList = i + LIST_FIRST;
        for (j = 0; j < data_ov026_0209136c->aCount[nList]; j++) {
            if (func_02023588(nFlagBase + (int)j) != 0
                || (data_ov026_0209136c->apRecords[nList][j].nPrice <= aTotal[i]
                    && data_ov026_0209136c->apRecords[nList][j].bEnabled != 0)) {
                aCount[i]++;
            }
        }
        nFlagBase += FLAGS_PER_LIST;
        i++;
    } while (i < LIST_COUNT);
}
