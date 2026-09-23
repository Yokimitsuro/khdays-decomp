/* ov150 .rodata tables, 0x020d2558-0x020d25b8.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ov150 actor initializer: install the callback table, seed the camera pose, (020cfc04): struct Ov150Kinds data_ov150_020d2558; */
const int data_ov150_020d2558[5] = {
    9, 2, 3, 4, 5,
};

/* read by Projectile action enter step (Ghidra: Ov150_ProjectileAction_Enter). (020d0ef4): u16 data_ov150_020d256c[4];
 *   func_ov150_020d0fa8 (020d0fa8): unsigned short data_ov150_020d256c[];
 *   func_ov150_020d1330 (020d1330): unsigned short data_ov150_020d256c[]; */
const u8 data_ov150_020d256c[12] = {
    0, 0, 5, 0, 0, 0, 5, 1, 0, 0, 5, 2,
};

/* read by Constructor for this enemy: install the five entry points, set the appearance (020d1624): const struct ChildIds data_ov150_020d2578; */
const int data_ov150_020d2578[2] = {
    7, 8,
};

/* read by Charge step of an ov150 enemy action: push anything caught in front and end (020d1d5c): const struct Msg data_ov150_020d2580; */
const u16 data_ov150_020d2580[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Charge step of an ov150 enemy action: push anything caught in front and end (020d1d5c): const struct Msg data_ov150_020d258e; */
const u16 data_ov150_020d258e[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by broadcast this node's position. When the caller's flag word has both (020d18f8): struct Msg data_ov150_020d259c; */
const u16 data_ov150_020d259c[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Charge step of an ov150 enemy action: push anything caught in front and end (020d1d5c): const struct Msg data_ov150_020d25aa; */
const u16 data_ov150_020d25aa[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
