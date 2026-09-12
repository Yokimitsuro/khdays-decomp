/* func_ov008_0206fc24 -- Ov008_CountGroupFlagsSet: find the flag group with the
 * given id in the owner's group table and report how many of its entries have
 * their game flag (entry flag + 9) set, plus the group's entry count.  Either
 * output pointer may be null.  The group count is a u8 local read through
 * pOwner->pTable (no table local); the entries are indexed, which walks a pointer
 * from the group with the +8 folded into the load.  Twin of 020743e4 (table at +0x174).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008FlagEntry {
    short nFlag;               /* 0x00: game flag - 9 */
    u8    pad_02[0x12];
} Ov008FlagEntry;

typedef struct Ov008FlagGroup {
    u16   nId;                 /* 0x00 */
    signed char nCount;        /* 0x02 */
    u8    pad_03[5];
    Ov008FlagEntry aEntry[1];  /* 0x08 */
} Ov008FlagGroup;

typedef struct Ov008FlagTable {
    u8    nGroups;             /* 0x00 */
    u8    pad_01[3];
    Ov008FlagGroup *apGroup[1]; /* 0x04 */
} Ov008FlagTable;

typedef struct Ov008FlagOwner {
    u8    pad_00[0x58];
    Ov008FlagTable *pTable;    /* 0x58 */
} Ov008FlagOwner;

#define FLAG_BASE 9

extern int func_02023588(int nFlag);   /* GameState_IsFlagSet */

void func_ov008_0206fc24(Ov008FlagOwner *pOwner, u32 nId, int *pnSet, u32 *pnCount)
{
    u8 nGroups;
    int i;
    int k;
    int nSet;
    Ov008FlagGroup *pGroup;
    nGroups = pOwner->pTable->nGroups;
    for (i = 0; i < nGroups; i++) {
        pGroup = pOwner->pTable->apGroup[i];
        if (nId == pGroup->nId) {
            if (pnCount != 0) {
                *pnCount = pGroup->nCount;
            }
            nSet = 0;
            for (k = 0; k < pGroup->nCount; k++) {
                if (func_02023588(pGroup->aEntry[k].nFlag + FLAG_BASE) != 0) {
                    nSet++;
                }
            }
            if (pnSet != 0) {
                *pnSet = nSet;
            }
            return;
        }
    }
}
