/* ov146 .rodata 0x020cf4f8-0x020cf514: the two initializer templates of the ov146 actor. */

typedef unsigned char u8;

typedef struct PartIds {
    int id[5];
} PartIds;

/* Ids of the hidden parts the constructor (func_ov146_020cbfc4, Ov146_Actor_Construct) attaches. */
const PartIds data_ov146_020cf4f8 = { { 0, 3, 0, 0x16, 0x17 } };

/* Reaction mode pairs of the hit filter (func_ov146_020cc658): {2, 3} while hurt, {0, 1}
 * otherwise, followed by the word 0x60 of an initializer whose copy the compiler dropped. */
const u8 data_ov146_020cf50c[8] = { 2, 3, 0, 1, 0x60, 0, 0, 0 };
