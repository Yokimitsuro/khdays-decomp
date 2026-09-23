/* ov288 .rodata tables, 0x020d5314-0x020d531c.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by * func_ov288_020d3f44 -- Ov287_Actor_ResolveHit. (020d3f44): const struct ImpactIdPairs data_ov288_020d5314; */
const u8 data_ov288_020d5314[8] = {
    2, 3, 0, 1, 0, 16, 0, 0,
};
