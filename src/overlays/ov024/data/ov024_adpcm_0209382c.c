/* ov024 .rodata 0x0209382c-0x020938f0: the IMA ADPCM tables the audio path uses.
 *
 * Both are the standard IMA ADPCM constants, unmodified.
 *
 * data_ov024_0209382c is the index adjustment table, {-1,-1,-1,-1,2,4,6,8},
 * stored twice: the decoder reads one row per nibble half so it never has to
 * mask the sample index down first. The -1 entries are what makes the step
 * walk back down on the four smallest codes.
 *
 * data_ov024_0209383c is the 89-entry step-size table, 7 through 32767 with a
 * ratio of about 1.1 per step, followed by a zero terminator the walker stops
 * on. These are the published IMA values, not a MobiClip variant.
 */
typedef signed char s8;
typedef unsigned short u16;

const s8 data_ov024_0209382c[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8,
    -1, -1, -1, -1, 2, 4, 6, 8,
};

const u16 data_ov024_0209383c[90] = {
        7,     8,     9,    10,    11,    12,    13,    14,    16,    17,
       19,    21,    23,    25,    28,    31,    34,    37,    41,    45,
       50,    55,    60,    66,    73,    80,    88,    97,   107,   118,
      130,   143,   157,   173,   190,   209,   230,   253,   279,   307,
      337,   371,   408,   449,   494,   544,   598,   658,   724,   796,
      876,   963,  1060,  1166,  1282,  1411,  1552,  1707,  1878,  2066,
     2272,  2499,  2749,  3024,  3327,  3660,  4026,  4428,  4871,  5358,
     5894,  6484,  7132,  7845,  8630,  9493, 10442, 11487, 12635, 13899,
    15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767,     0,
};
