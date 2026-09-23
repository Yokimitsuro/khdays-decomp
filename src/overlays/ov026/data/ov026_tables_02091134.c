/* ov026 .rodata tables, 0x02091134-0x020911c4.
 *
 * 10 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov008_InitFilterRows: build the five filter rows of the (02086314): const Ov008RowRect data_ov026_02091134[];
 *   Ov008_ShowFilterRow: flip row nRow of the filter panel (02086438): const u8 data_ov026_02091134[];
 *   Ov008_ShopTabSelectTick: one frame of the shop's (0208acc4): Ov008ChoiceBox data_ov026_02091134[]; */
const u8 data_ov026_02091134[1] = {
    80,
};

/* read by Ov008_ShowFilterRow: flip row nRow of the filter panel (02086438): const u8 data_ov026_02091135[]; */
const u8 data_ov026_02091135[19] = {
    24, 96, 16, 80, 48, 96, 16, 80, 72, 96, 16, 80, 96, 96, 16, 80,
    120, 96, 16,
};

/* read by Ov008_InitPanelSlotManagers: create the panel (020855c4): s8 data_ov026_02091148[]; */
const u8 data_ov026_02091148[1] = {
    0,
};

/* read by Ov008_InitPanelSlotManagers: create the panel (020855c4): s8 data_ov026_02091149[]; */
const u8 data_ov026_02091149[1] = {
    4,
};

/* read by Ov008_LoadShopResources: load the shop panel's (0208532c): s8   data_ov026_0209114a[]; */
const u8 data_ov026_0209114a[1] = {
    9,
};

/* read by Ov008_InitPanelSlotManagers: create the panel (020855c4): s8 data_ov026_0209114b[]; */
const u8 data_ov026_0209114b[17] = {
    13, 255, 5, 255, 14, 1, 6, 10, 15, 2, 7, 11, 16, 3, 8, 12,
    17,
};

/* read by func_ov026_0208529c (0208529c): int data_ov026_0209115c[]; */
const int data_ov026_0209115c[7] = {
    9, 10, 11, 24, 25, 26, 27,
};

/* read by Ov008_DrawCounterPanel: redraw the shop's counter (02086af4): const Ov008WidgetTable data_ov026_02091178; */
const int data_ov026_02091178[7] = {
    20, 22, 25, 23, 21, 24, 26,
};

/* read by Ov008_ShopListInput: one frame of input on the (0208b2c0): const Ov008ChoiceBox data_ov026_02091194[16]; */
const u8 data_ov026_02091194[40] = {
    32, 0, 24, 20, 56, 0, 24, 20, 80, 0, 24, 20, 104, 0, 24, 20,
    128, 0, 24, 20, 152, 0, 24, 20, 176, 0, 24, 20, 200, 0, 24, 20,
    16, 0, 40, 20, 56, 0, 40, 20,
};

/* read by Ov008_MergePendingUnlockBits: OR the param table's two (0208e35c): const Ov008BitArrayCounts data_ov026_020911bc; */
const int data_ov026_020911bc[2] = {
    32, 32,
};
