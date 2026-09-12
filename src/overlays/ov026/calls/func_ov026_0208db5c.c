/* func_ov026_0208db5c -- Ov008_IsRewardItemShown: whether reward item nItemId may
 * be listed.  With the table's "show all" word (+0x144) clear, a fixed set of
 * late items (0x1e7, 0x1ea, 0x1eb, 0x1ed..0x1ef, 0x1f1..0x1ff) is hidden; then,
 * while the 3-bit story field 0x44e is below 2, items 0xca, 0xcc, 0xd2, 0xd3, 0xd8
 * and 0xda are hidden too.  Returns 1 otherwise.
 */
typedef unsigned char u8;
typedef unsigned int  u32;

#define FIELD_STORY_STAGE 0x44e

typedef struct Ov008ParamTable {
    u8  pad_000[0x144];
    int bShowAll;             /* 0x144 */
} Ov008ParamTable;

extern Ov008ParamTable *data_ov026_0209136c;
extern u32 func_020235d0(int nField, int nBits);                         /* GameState_GetField */

int func_ov026_0208db5c(int nItemId)
{
    if (data_ov026_0209136c->bShowAll == 0) {
        switch (nItemId) {
        case 0x1e7:
        case 0x1ea:
        case 0x1eb:
        case 0x1ed:
        case 0x1ee:
        case 0x1ef:
        case 0x1f1:
        case 0x1f2:
        case 0x1f3:
        case 0x1f4:
        case 0x1f5:
        case 0x1f6:
        case 0x1f7:
        case 0x1f8:
        case 0x1f9:
        case 0x1fa:
        case 0x1fb:
        case 0x1fc:
        case 0x1fd:
        case 0x1fe:
        case 0x1ff:
            return 0;
        }
    }
    if (func_020235d0(FIELD_STORY_STAGE, 3) < 2) {
        switch (nItemId) {
        case 0xca:
        case 0xcc:
        case 0xd2:
        case 0xd3:
        case 0xd8:
        case 0xda:
            return 0;
        }
    }
    return 1;
}
