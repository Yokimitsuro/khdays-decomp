/* func_ov008_0208b4ac -- Ov008_MergePendingUnlockBits: OR the param table's two
 * pending unlock bit arrays (32 words each, counts from the 0208ff64 pair) into
 * its committed arrays, then OR the two pending summary words into the game
 * state's unlock summary at 0x1160.
 */
typedef unsigned char u8;
typedef unsigned int  u32;

#define BIT_ARRAY_COUNT 2

typedef struct Ov008BitArrayCounts {
    int aCount[BIT_ARRAY_COUNT];
} Ov008BitArrayCounts;

typedef struct Ov008ParamTable {
    u8   pad_0000[0x28];
    u32 *apPendingBits[BIT_ARRAY_COUNT];   /* 0x28 */
    u32 *apUnlockBits[BIT_ARRAY_COUNT];    /* 0x30 */
    u8   pad_0038[0x13c - 0x38];
    u32  aPendingSummary[BIT_ARRAY_COUNT]; /* 0x13c */
} Ov008ParamTable;

typedef struct GameState {
    u8  pad_0000[0x1160];
    u32 aUnlockSummary[BIT_ARRAY_COUNT];   /* 0x1160 */
} GameState;

extern const Ov008BitArrayCounts data_ov008_0208ff64;   /* { 32, 32 } */
extern Ov008ParamTable *data_ov008_02090fb0;
extern GameState *data_0204be18;

void func_ov008_0208b4ac(void)
{
    Ov008BitArrayCounts counts = data_ov008_0208ff64;
    int i;
    int j;

    for (i = 0; i < BIT_ARRAY_COUNT; i++) {
        for (j = 0; j < counts.aCount[i]; j++) {
            data_ov008_02090fb0->apUnlockBits[i][j] |= data_ov008_02090fb0->apPendingBits[i][j];
        }
        data_0204be18->aUnlockSummary[i] |= data_ov008_02090fb0->aPendingSummary[i];
    }
}
