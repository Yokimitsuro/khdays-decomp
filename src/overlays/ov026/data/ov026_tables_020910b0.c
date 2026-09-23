/* ov026 .rodata tables, 0x020910b0-0x02091120.
 *
 * 13 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by For each variable-stride record, build a sprite via func_ov026_02083294 (kind-mapped prior (02082bfc): unsigned char data_ov026_020910b0; */
const u8 data_ov026_020910b0[4] = {
    8, 9, 10, 11,
};

/* read by For each variable-stride record, build a sprite via func_ov026_02083294 (kind-mapped prior (02082bfc): unsigned char data_ov026_020910b4; */
const u8 data_ov026_020910b4[4] = {
    24, 25, 26, 27,
};

/* read by Ov008_RebuildShopList: rebuild the shop's record (02087570): s16 data_ov026_020910b8[]; */
const u8 data_ov026_020910b8[4] = {
    0, 0, 1, 0,
};

/* read by Ov008_CounterDialogInput: one frame of input on (0208bbf4): const u16 data_ov026_020910bc[ROW_COUNT]; */
const u8 data_ov026_020910bc[8] = {
    32, 0, 64, 0, 16, 0, 128, 0,
};

/* read by Ov008_ShopListInput: one frame of input on the (0208b2c0): const Ov008ChoiceBox data_ov026_020910c4[2]; */
const u8 data_ov026_020910c4[8] = {
    40, 24, 160, 16, 24, 24, 192, 16,
};

/* read by Ov008_OpenShopDetailPanel: open the shop's detail (02089d2c): Ov008ChoiceBox data_ov026_020910cc[];
 *   Ov008_ShopDetailConfirmTick: one frame of the shop (0208c2d8): u8  data_ov026_020910cc[]; */
const u8 data_ov026_020910cc[4] = {
    32, 104, 96, 16,
};

/* read by Ov008_ShopDetailConfirmTick: one frame of the shop (0208c2d8): u8  data_ov026_020910d0[]; */
const u8 data_ov026_020910d0[4] = {
    128, 104, 96, 16,
};

/* read by Ov008_ShopListInput: one frame of input on the (0208b2c0): const Ov008ChoiceBox data_ov026_020910d4[2]; */
const u8 data_ov026_020910d4[8] = {
    200, 24, 16, 128, 216, 24, 16, 128,
};

/* read by func_ov026_02088c84 (not yet decompiled)
 *   Ov008_CounterDialogInput: one frame of input on (0208bbf4): const Ov008ChoiceBox data_ov026_020910dc[1]; */
const u8 data_ov026_020910dc[4] = {
    32, 117, 96, 16,
};

/* read by Ov008_CounterDialogInput: one frame of input on (0208bbf4): const Ov008ChoiceBox data_ov026_020910e0[1]; */
const u8 data_ov026_020910e0[16] = {
    128, 117, 96, 16, 255, 255, 0, 0, 1, 0, 5, 0, 4, 0, 6, 0,
};

/* read by Ov008_ShopTabSelectTick: one frame of the shop's (0208acc4): u8  data_ov026_020910f0[]; */
const u8 data_ov026_020910f0[15] = {
    0, 0, 1, 4, 4, 0, 0, 1, 2, 4, 0, 1, 2, 3, 4,
};

/* read by Ov008_CounterDialogInput: one frame of input on (0208bbf4): const Ov008ChoiceBox data_ov026_020910ff[ROW_COUNT]; */
const u8 data_ov026_020910ff[17] = {
    80, 88, 16, 16, 104, 76, 16, 16, 120, 88, 16, 16, 101, 100, 16, 16,
    0,
};

/* read by Ov008_RebuildShopList: rebuild the shop's record (02087570): s16 data_ov026_02091110[]; */
const u8 data_ov026_02091110[16] = {
    255, 255, 0, 0, 3, 0, 1, 0, 5, 0, 4, 0, 6, 0, 2, 0,
};
