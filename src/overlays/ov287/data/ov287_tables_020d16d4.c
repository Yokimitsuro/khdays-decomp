/* ov287 .rodata tables, 0x020d16d4-0x020d16dc.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by * func_ov287_020d0304 -- Ov287_Actor_ResolveHit. (020d0304): const struct ImpactIdPairs data_ov287_020d16d4; */
const u8 data_ov287_020d16d4[8] = {
    2, 3, 0, 1, 0, 16, 0, 0,
};
