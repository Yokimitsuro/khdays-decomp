/* ov107 .rodata tables, 0x020cb64c-0x020cb68c.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov107_020c5cfc (020c5cfc): const struct Message12 data_ov107_020cb64c; */
const u8 data_ov107_020cb64c[12] = {
    0, 0, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by * Throttles creature updates by distance and update phase, advances timers and (020c6980): const VecFx32 data_ov107_020cb658; */
const u8 data_ov107_020cb658[12] = {
    0, 0, 0, 0, 128, 254, 255, 255, 0, 0, 0, 0,
};

/* read by Collect sphere contacts against polygon fans, then visit child spatial groups. (020c9f64): const ChildOffset data_ov107_020cb664[4];
 *   func_ov107_020ca4b4 (020ca4b4): const ChildOffset data_ov107_020cb664[4]; */
const u8 data_ov107_020cb664[16] = {
    255, 255, 255, 255, 1, 0, 255, 255, 255, 255, 1, 0, 1, 0, 1, 0,
};

/* read by func_ov107_020ca918 (020ca918): const struct HitMsg data_ov107_020cb674; */
const u8 data_ov107_020cb674[12] = {
    0, 0, 8, 6, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by func_ov107_020ca918 (020ca918): const struct HitMsg data_ov107_020cb680; */
const u8 data_ov107_020cb680[12] = {
    0, 0, 8, 5, 0, 0, 0, 0, 0, 0, 0, 0,
};
