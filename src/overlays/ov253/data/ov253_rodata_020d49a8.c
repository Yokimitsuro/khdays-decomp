/* ov253 .rodata tables 0x020d49a8-0x020d4a00 (split by alignment so the objects tile their run). */

typedef unsigned char u8;
typedef unsigned short u16;

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
