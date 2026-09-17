/* main .data, 0x020427f0-0x02042910: a handful of flags read by the world-loading code and the default
 * transform records (fixed-point identity matrices and zero vectors) that 02027b18 / 02027d7c /
 * 020287e8 copy when they set up an object.
 */
typedef int fx32;
typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22; } MtxFx33;
typedef struct { fx32 _00, _01, _02, _10, _11, _12, _20, _21, _22, _30, _31, _32; } MtxFx43;
#define FX32_ONE 0x1000

/* Set at boot; 0201f634, 02025138, 0202a3cc and ov022 020b1264 test it. */
int data_020427f0 = 1;
/* Read by 020280a4 / 02028314. */
int data_020427f4 = 0x2a;
int data_020427f8[2] = { 0, 0x2a };
#pragma explicit_zero_data on
int data_02042800 = 0;
#pragma explicit_zero_data off
/* Sixteen words, only [10] and [15] set (0x10000), read by 02028314. */
int data_02042804[16] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0x10000, 0,
    0, 0, 0, 0x10000,
};

/* Default record read by 02027b18: four byte parameters, two ids, a 3x3 identity and two zero vectors. */
unsigned char data_02042844[4] = { 0x12, 0x10, 0x17, 0x1b };
int data_02042848[2] = { 1, 2 };
MtxFx33 data_02042850 = { FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0, FX32_ONE };
#pragma explicit_zero_data on
VecFx32 data_02042874 = { 0, 0, 0 };
VecFx32 data_02042880 = { 0, 0, 0 };
#pragma explicit_zero_data off

/* The same default record for 02027d7c, followed by a zero 3x2 block and a 4x3 identity for 020287e8. */
unsigned char data_0204288c[4] = { 0x12, 0x10, 0x17, 0x1b };
int data_02042890[2] = { 1, 2 };
MtxFx33 data_02042898 = { FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0, FX32_ONE };
#pragma explicit_zero_data on
VecFx32 data_020428bc = { 0, 0, 0 };
VecFx32 data_020428c8[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
#pragma explicit_zero_data off
MtxFx43 data_020428e0 = { FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0 };
