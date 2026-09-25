/* ov297 .rodata tables, 0x020d56b4-0x020d57a4.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Retreat entry of the ov297 enemy: spawns effect 0 and fires reaction 0x176 mode 4 at the + (020d5394): const struct PointTable data_ov297_020d56b4; */
const int data_ov297_020d56b4[60] = {
    -25772, -2454, 44671,
    -28115, -2454, -14078,
    29700, -2454, 47428,
    5673, 0, 9245,
    49779, 1638, -5587,
    27193, 0, 29045,
    -9966, 0, 29196,
    -9146, 0, -11510,
    27116, 0, -11649,
    49779, 1638, 23470,
    -20623, 127, 0,
    22364, 1171, -21963,
    -27615, -8319, 68891,
    17945, -20607, 84206,
    -14787, -127, 40108,
    89453, -8319, 6640,
    93032, -127, -47919,
    26911, 3965, -48509,
    -63070, 3965, -32555,
    -63287, 3650, 29082,
};
