/* ov253 .rodata 0x020d482c-0x020d4a24: the actor's tables in one unit, in address order. The
 * pointer tables are all zero in the ROM image (every entry is a relocation onto the unit's
 * resource name strings); the other tables are written in the width their contents are in. */

typedef unsigned char u8;
typedef unsigned short u16;

extern int data_ov253_020d4a40;
extern int data_ov253_020d4a4c;
extern int data_ov253_020d4a58;
extern int data_ov253_020d4a64;
extern int data_ov253_020d4a70;
extern int data_ov253_020d4a7c;
extern int data_ov253_020d4a88;
extern int data_ov253_020d4a94;
extern int data_ov253_020d4aa0;
extern int data_ov253_020d4aac;
extern int data_ov253_020d4ab8;
extern int data_ov253_020d4ac8;
extern int data_ov253_020d4ad8;
extern int data_ov253_020d4ae8;
extern int data_ov253_020d4af8;
extern int data_ov253_020d4b08;
extern int data_ov253_020d4b18;
extern int data_ov253_020d4b28;
extern int data_ov253_020d4b38;
extern int data_ov253_020d4b48;
extern int data_ov253_020d4ba0;
extern int data_ov253_020d4ba8;
extern int data_ov253_020d4bb0;
extern int data_ov253_020d4bb8;

/* read by func_ov253_020cc358 (not yet decompiled) */
const int data_ov253_020d482c[2] = {
    32, 43,
};

/* read by carried item update: after the base update (0203bc78) the +0x84 (020cc248): const struct vec4 data_ov253_020d4834; */
const int data_ov253_020d4834[4] = {
    0, 2896, 2896, 0,
};

void *const data_ov253_020d4844[5] = {
    &data_ov253_020d4ad8,
    &data_ov253_020d4a94,
    &data_ov253_020d4a88,
    &data_ov253_020d4b28,
    &data_ov253_020d4b48,
};

void *const data_ov253_020d4858[5] = {
    &data_ov253_020d4b08,
    &data_ov253_020d4a40,
    &data_ov253_020d4a58,
    &data_ov253_020d4a7c,
    &data_ov253_020d4ae8,
};

void *const data_ov253_020d486c[5] = {
    &data_ov253_020d4ab8,
    &data_ov253_020d4a64,
    &data_ov253_020d4a70,
    &data_ov253_020d4b18,
    &data_ov253_020d4b38,
};

void *const data_ov253_020d4880[5] = {
    &data_ov253_020d4af8,
    &data_ov253_020d4a4c,
    &data_ov253_020d4aac,
    &data_ov253_020d4aa0,
    &data_ov253_020d4ac8,
};

/* read by func_ov253_020ccd00 (not yet decompiled) */
const int data_ov253_020d4894[13] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13,
};

/* read by func_ov253_020ccd00 (not yet decompiled) */
const int data_ov253_020d48c8[13] = {
    15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 27,
};

/* read by recover entry: sends message data_ov253_020d48fc (kind 4) to the (020cd9e8): const struct hpair data_ov253_020d48fc; */
const u8 data_ov253_020d48fc[4] = {
    0, 0, 5, 1,
};

/* read by func_ov253_020cda5c (not yet decompiled) */
const u8 data_ov253_020d4900[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by facing tick: the +0x30 delay runs down while non-negative; the +0xc (020cd484): const struct Ov253Axes data_ov253_020d4910; */
const u8 data_ov253_020d4910[48] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 240, 255, 255, 0, 240, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
};

void *const data_ov253_020d4940[4] = {
    &data_ov253_020d4bb8,
    &data_ov253_020d4bb0,
    &data_ov253_020d4ba8,
    &data_ov253_020d4ba0,
};

/* read by func_ov253_020ce50c (not yet decompiled) */
const int data_ov253_020d4950[5] = {
    32, 31, 33, 41, 42,
};

/* read by shout entry: dispatches sprite request 4 (data_ov253_020d4964 + 0x10 (020cfbc4): int data_ov253_020d4964;
 *   carry hold tick: the +0x18 speed follows twice the frame step (020d01c0): int data_ov253_020d4964;
 *   Build the sprite request (mirroring the object's facing) and dispatch. (020d0410): int data_ov253_020d4964;
 *   carry tick: seats the +0x3bc target's +0x18c rider (its +0x20 child) (020d0674): const struct hpair data_ov253_020d4964[];
 *   taunt tick: the +0x18 speed follows six times the frame step (30 / 5); (020d0a04): const struct hpair data_ov253_020d4964[];
 *   stun entry: sends message data_ov253_020d4964 + 8 (kind 4) to the (020d0bbc): int data_ov253_020d4964; */
const u16 data_ov253_020d4964[13] = {
    0, 1541, 0, 517, 0, 1029, 0, 261,
    0, 1797, 0, 1285, 0,
};

/* read by func_ov253_020cfd20 (not yet decompiled) */
const u16 data_ov253_020d497e[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by release wait tick: the +0x18 speed follows twice the frame step (020cf66c): const PosMsg data_ov253_020d498c; */
const u16 data_ov253_020d498c[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by roar tick: the +0x18 speed follows twice the frame step (30 / 15); (020cfa44): const PosMsg data_ov253_020d499a; */
const u16 data_ov253_020d499a[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Ov253_HeadButtTick (020d0d18): const Cmd14 data_ov253_020d49a8; */
const u8 data_ov253_020d49a8[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by roam entry: the +0x18 speed follows twice the frame step (30 / 15); (020cf08c): const struct Ov253Bounds data_ov253_020d49b8; */
const u8 data_ov253_020d49b8[20] = {
    0, 0, 0, 0, 34, 25, 0, 0, 68, 50, 0, 0, 102, 75, 0, 0,
    136, 100, 0, 0,
};

/* read by turn entry: the +0x18 speed follows twice the frame step (30 / 15) and (020cf830): const struct Ov253Bounds data_ov253_020d49cc; */
const u8 data_ov253_020d49cc[20] = {
    0, 0, 0, 0, 34, 25, 0, 0, 68, 50, 0, 0, 102, 75, 0, 0,
    136, 100, 0, 0,
};

/* read by Ov253_QueueActorConstruct (020d2140): const int data_ov253_020d49e0;
 *   queue-driven sub-state tick: while the +0x50 phase is 1 and the actor's (020d25e4): const struct Ov253SubMap data_ov253_020d49e0; */
const u8 data_ov253_020d49e0[12] = {
    4, 5, 6, 0, 38, 0, 0, 0, 40, 0, 0, 0,
};

/* read by summon entry: sends message data_ov253_020d49ec (kind 4) to the actor's (020d3038): const struct hpair data_ov253_020d49ec; */
const u8 data_ov253_020d49ec[4] = {
    0, 0, 5, 0,
};

/* read by grow tick: the +0x1c timer runs up and its 32.32 ratio over 0.5 (020d2be8): const PosMsg data_ov253_020d49f0; */
const u8 data_ov253_020d49f0[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by item construction: installs the handlers (+8 020d3c38, +0xc 020d3c78, (020d3aac): const struct Ov253Poses data_ov253_020d4a00; */
const int data_ov253_020d4a00[2] = {
    34, 36,
};

/* read by burst entry: the overlay's 14-byte message (data_ov253_020d4a08) (020d40d0): const PosMsg data_ov253_020d4a08; */
const u16 data_ov253_020d4a08[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by box entry: the overlay's 14-byte message (data_ov253_020d4a16) (020d4548): const PosMsg data_ov253_020d4a16; */
const u16 data_ov253_020d4a16[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
