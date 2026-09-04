/* ov002 .data tables, 0x0207eb08-0x0207eb10.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Read by Ov002_DrawPanelRowText (0x0207eb08, 0x0207eb0c).
 */

typedef unsigned char u8;
typedef unsigned short u16;

int data_ov002_0207eb08[1] = {
    0,
};

u8 data_ov002_0207eb0c[4] = {
    252, 48, 0, 0,
};
