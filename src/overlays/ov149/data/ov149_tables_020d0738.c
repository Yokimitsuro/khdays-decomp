/* ov149 .rodata tables, 0x020d0738-0x020d0798.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ov149 actor initializer: install the callback table, seed the camera pose, (020cdde4): struct Ov149Kinds data_ov149_020d0738; */
const int data_ov149_020d0738[5] = {
    9, 2, 3, 4, 5,
};

/* read by Projectile action enter step (Ghidra: Ov149_ProjectileAction_Enter). (020cf0d4): u16 data_ov149_020d074c[4];
 *   func_ov149_020cf188 (020cf188): unsigned short data_ov149_020d074c[];
 *   func_ov149_020cf510 (020cf510): unsigned short data_ov149_020d074c[]; */
const u8 data_ov149_020d074c[12] = {
    0, 0, 5, 0, 0, 0, 5, 1, 0, 0, 5, 2,
};

/* read by Constructor for this enemy: install the five entry points, set the appearance (020cf804): const struct ChildIds data_ov149_020d0758; */
const int data_ov149_020d0758[2] = {
    7, 8,
};

/* read by Charge step of an ov149 enemy action: push anything caught in front and end (020cff3c): const struct Msg data_ov149_020d0760; */
const u16 data_ov149_020d0760[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Charge step of an ov149 enemy action: push anything caught in front and end (020cff3c): const struct Msg data_ov149_020d076e; */
const u16 data_ov149_020d076e[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by broadcast this node's position. When the caller's flag word has both (020cfad8): struct Msg data_ov149_020d077c; */
const u16 data_ov149_020d077c[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Charge step of an ov149 enemy action: push anything caught in front and end (020cff3c): const struct Msg data_ov149_020d078a; */
const u16 data_ov149_020d078a[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
