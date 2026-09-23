/* ov289 .rodata tables, 0x020d7134-0x020d713c.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by * func_ov289_020d5d64 -- Ov287_Actor_ResolveHit. (020d5d64): const struct ImpactIdPairs data_ov289_020d7134; */
const u8 data_ov289_020d7134[8] = {
    2, 3, 0, 1, 0, 16, 0, 0,
};
