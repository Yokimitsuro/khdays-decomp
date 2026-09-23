/* ov152 .rodata tables, 0x020d6460-0x020d64c0.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov151 enemy (and its byte-identical twin): installs the handlers (+8 ti (020d3844): const struct PoolIds data_ov152_020d6460; */
const int data_ov152_020d6460[5] = {
    10, 2, 3, 4, 5,
};

/* read by Constructor of the ov151 enemy's summoned pet (and its byte-identical twin): installs the (020d4248): const int data_ov152_020d6474[2]; */
const int data_ov152_020d6474[2] = {
    7, 8,
};

/* read by Shot tick of the ov151 enemy (and its byte-identical twin): the +0x38 clock accumulates th (020d4c2c): const PosMsg data_ov152_020d647c; */
const u16 data_ov152_020d647c[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Shot launch of the ov151 enemy (and its byte-identical twin): clears the +0x38 hit count,  (020d49ec): const PosMsg data_ov152_020d648a; */
const u16 data_ov152_020d648a[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by broadcast this node's position. When the caller's flag word has both (020d4594): struct Msg data_ov152_020d6498; */
const u16 data_ov152_020d6498[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Shot tick of the ov151 enemy (and its byte-identical twin): the +0x38 clock accumulates th (020d4c2c): const PosMsg data_ov152_020d64a6; */
const u16 data_ov152_020d64a6[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Projectile action enter step (Ghidra: Ov149_ProjectileAction_Enter). (020d5d70): u16 data_ov152_020d64b4[4];
 *   func_ov152_020d5e24 (020d5e24): unsigned short data_ov152_020d64b4[];
 *   func_ov152_020d61b0 (020d61b0): unsigned short data_ov152_020d64b4[]; */
const u8 data_ov152_020d64b4[12] = {
    0, 0, 5, 0, 0, 0, 5, 1, 0, 0, 5, 2,
};
