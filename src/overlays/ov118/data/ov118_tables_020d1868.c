/* ov118 .rodata tables, 0x020d1868-0x020d1884.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov118_020d0f34 (020d0f34): Pair data_ov118_020d1868[];
 *   Publish the landing: copy the pending anchor into the live slot and ask the placement help (020d10d4): Ev data_ov118_020d1868[];
 *   func_ov118_020d13cc (020d13cc): Pair16 data_ov118_020d1868[]; */
const u8 data_ov118_020d1868[12] = {
    0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0,
};

/* read by func_ov118_020cfc04 (020cfc04): const struct CameraWork data_ov118_020d1874; */
const int data_ov118_020d1874[4] = {
    0, 0, 0, 2560,
};
