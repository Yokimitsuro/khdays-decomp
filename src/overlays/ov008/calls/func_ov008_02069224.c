/* func_ov008_02069224 -- Ov008_RefreshSaveRowDigits: for each of the three save
 * summary rows in state 1, split the row's count (capped at 999) into its three
 * digit glyphs (func_ov008_02069a64) and push them, the row's session word and
 * the "empty" sign (-1 when the row's flag at +0x24 is clear, else 0) to the
 * row's tags 5..7, 4 and 3 through Ov008_ConfigureTagBySign.  pMenu (the save
 * menu, passed by Ov008_SaveMenuTick) is unused.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROW_COUNT   3
#define DIGIT_COUNT 3
#define COUNT_MAX   999

/* Row i lives at ctx + 0x10 + i * 0x1c, but the ROM walks the context pointer
 * itself in 0x1c steps and folds the 0x10 into every field offset, so the row
 * is modelled as a 0x28-byte view whose first 0x1c bytes overlap the walker.
 */
typedef struct Ov009SummaryRowView {
    u8  pad_00[0x10];
    u16 nCount;               /* 0x10 */
    u8  pad_12[6];
    int nSession;             /* 0x18 */
    u8  pad_1c[4];
    int state;                /* 0x20 */
    int nFlag24;              /* 0x24 */
} Ov009SummaryRowView;

#define ROW_STRIDE 0x1c

extern const int data_ov008_0208f588[3][8];
extern u8 *func_ov008_02050cd4(void);                            /* Ov008_GetMenuContext */
extern int func_ov008_02069a64(int nDigit, u32 nValue);          /* digit glyph */
extern void func_ov008_020698f8(int nTag, u32 nSign);            /* Ov008_ConfigureTagBySign */

void func_ov008_02069224(void *pMenu)
{
    int aDigit[DIGIT_COUNT] = { 0, 0, 0 };
    u8 *ctx;
    Ov009SummaryRowView *row;
    int i;
    int j;
    u32 nCount;

    ctx = func_ov008_02050cd4();
    for (i = 0; i < ROW_COUNT; i++, ctx += ROW_STRIDE) {
        row = (Ov009SummaryRowView *)ctx;
        if (row->state == 1) {
            nCount = row->nCount;
            if ((int)nCount > COUNT_MAX) {
                nCount = COUNT_MAX;
            }
            for (j = 0; j < DIGIT_COUNT; j++) {
                aDigit[j] = func_ov008_02069a64(j, nCount);
            }
            func_ov008_020698f8(data_ov008_0208f588[i][5], aDigit[0]);
            func_ov008_020698f8(data_ov008_0208f588[i][6], aDigit[1]);
            func_ov008_020698f8(data_ov008_0208f588[i][7], aDigit[2]);
            func_ov008_020698f8(data_ov008_0208f588[i][4], row->nSession);
            func_ov008_020698f8(data_ov008_0208f588[i][3], -(row->nFlag24 == 0));
        }
    }
}
