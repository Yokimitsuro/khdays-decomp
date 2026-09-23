/* ov022 .rodata tables, 0x020b2654-0x020b2850.
 *
 * 13 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ov022: pick the cue for a slot, given what the actor is doing. (02098134): const short data_ov022_020b2654[]; */
const u16 data_ov022_020b2654[15] = {
    1, 2, 7, 10, 3, 8, 9, 5,
    6, 4, 11, 65535, 65535, 65535, 13,
};

/* read by ov022: pick the cue for a slot, given what the actor is doing. (02098134): const short data_ov022_020b2672[]; */
const u16 data_ov022_020b2672[15] = {
    27, 28, 33, 36, 29, 34, 35, 31,
    32, 30, 37, 65535, 65535, 65535, 39,
};

/* read by ov022: pick the cue for a slot, given what the actor is doing. (02098134): const short data_ov022_020b2690[]; */
const u8 data_ov022_020b2690[32] = {
    14, 0, 15, 0, 20, 0, 23, 0, 16, 0, 21, 0, 22, 0, 18, 0,
    19, 0, 17, 0, 24, 0, 255, 255, 255, 255, 255, 255, 26, 0, 0, 0,
};

/* read by func_ov022_020a22f0 (020a22f0): struct Ov022MatchTable020a22f0 data_ov022_020b26b0; */
const int data_ov022_020b26b0[8] = {
    67, 7, 68, 3, 69, 11, 70, 2,
};

/* read by func_ov022_0209bec8 (0209bec8): struct tbl9_0209bec8 data_ov022_020b26d0; */
const int data_ov022_020b26d0[9] = {
    9, 7, 3, 11, 6, 5, 10, 12,
    1,
};

/* read by Ov022_StepStuckRespawnState -- state step for a partner that is stuck: (020ac6c8): VecFx32 data_ov022_020b26f4[4]; */
const u8 data_ov022_020b26f4[48] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 255, 255,
    0, 0, 0, 0, 0, 16, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0,
    0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0,
};

/* read by func_ov022_020a4798 (020a4798): struct KindIdTable data_ov022_020b2724; */
const u8 data_ov022_020b2724[120] = {
    234, 0, 0, 0, 238, 0, 0, 0, 240, 0, 0, 0, 242, 0, 0, 0,
    244, 0, 0, 0, 8, 1, 0, 0, 246, 0, 0, 0, 6, 1, 0, 0,
    0, 1, 0, 0, 248, 0, 0, 0, 4, 1, 0, 0, 16, 1, 0, 0,
    254, 0, 0, 0, 252, 0, 0, 0, 250, 0, 0, 0, 2, 1, 0, 0,
    10, 1, 0, 0, 12, 1, 0, 0, 14, 1, 0, 0, 236, 0, 0, 0,
    0, 12, 0, 0, 12, 0, 0, 0, 0, 16, 0, 0, 3, 0, 0, 0,
    3, 0, 0, 0, 3, 0, 0, 0, 0, 8, 0, 0, 0, 64, 0, 0,
    0, 24, 0, 0, 0, 160, 0, 0,
};

/* read by Ov022_StepPartnerSlot -- one frame of a partner's slot AI against its (020ad9b0): const struct IdTriple data_ov022_020b279c; */
const int data_ov022_020b279c[6] = {
    4, 3, 2, 7, 6, 5,
};

/* read by Ov022_StepPartnerSlot -- one frame of a partner's slot AI against its (020ad9b0): const struct IdTriple data_ov022_020b27b4; */
const int data_ov022_020b27b4[3] = {
    14, 13, 12,
};

/* read by Ov022_StepPartnerSlot -- one frame of a partner's slot AI against its (020ad9b0): const VecFx32 data_ov022_020b27c0; */
const int data_ov022_020b27c0[3] = {
    0, 1, 0,
};

/* read by Ov022_StepPartnerSlot -- one frame of a partner's slot AI against its (020ad9b0): const struct IdCols data_ov022_020b27cc; */
const int data_ov022_020b27cc[4] = {
    7, 3, 11, 2,
};

/* read by Ov022_StepPartnerSlot -- one frame of a partner's slot AI against its (020ad9b0): const struct IdRow data_ov022_020b27dc; */
const u8 data_ov022_020b27dc[56] = {
    2, 0, 0, 0, 5, 0, 0, 0, 8, 0, 0, 0, 11, 0, 0, 0,
    1, 0, 0, 0, 4, 0, 0, 0, 7, 0, 0, 0, 10, 0, 0, 0,
    0, 0, 0, 0, 3, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0,
    0, 80, 0, 0, 0, 64, 0, 0,
};

/* read by ov022: split a slot's video memory between its part blocks. (020b15b0): const struct SizeTable data_ov022_020b2814; */
const u8 data_ov022_020b2814[60] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 144, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 0, 0, 0, 64, 0, 0,
    0, 0, 0, 0, 0, 80, 0, 0, 0, 32, 0, 0, 0, 32, 0, 0,
    0, 64, 0, 0, 0, 48, 0, 0, 0, 32, 0, 0,
};
