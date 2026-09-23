/* ov023 .rodata tables, 0x02089d74-0x02089e10.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov023_RequestGroupResources: request the resources the event's actor (02083c14): const Ov023KindResTable data_ov023_02089d74; */
const int data_ov023_02089d74[26] = {
    396, 408, 397, 409, 402, 414, 405, 417,
    398, 410, 403, 415, 404, 416, 400, 412,
    401, 413, 399, 411, 406, 418, 396, 408,
    396, 408,
};

/* read by Ov023_CmdSeatMembers: script command that seats the party actors. (02086cb8): const Ov023SeatHeights data_ov023_02089ddc; */
const u8 data_ov023_02089ddc[52] = {
    0, 0, 0, 0, 31, 209, 255, 255, 231, 218, 255, 255, 118, 131, 255, 255,
    209, 151, 255, 255, 190, 165, 255, 255, 120, 187, 255, 255, 186, 198, 255, 255,
    17, 140, 255, 255, 99, 192, 255, 255, 99, 199, 255, 255, 8, 184, 255, 255,
    45, 160, 255, 255,
};
