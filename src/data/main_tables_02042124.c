/* main .rodata 0x02042124-0x02042288: script-slot kinds, party reward/skill tables, the key-repeat
 * key tables and the six signed unit axes. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef int fx32;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

#define PAD_BUTTON_A      0x0001
#define PAD_BUTTON_B      0x0002
#define PAD_KEY_RIGHT     0x0010
#define PAD_KEY_LEFT      0x0020
#define PAD_KEY_UP        0x0040
#define PAD_KEY_DOWN      0x0080
#define PAD_BUTTON_R      0x0100
#define PAD_BUTTON_L      0x0200
#define PAD_BUTTON_X      0x0400
#define PAD_BUTTON_Y      0x0800

/* Kind of each of the 48 script slots (0..3, 99 = reserved), consulted by the per-frame command
 * dispatcher func_02032f5c before it links two slots (kind 1 targeting kind 2). */
const u8 data_02042124[48] = {
    0, 2, 1, 3, 0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0,
    1, 2, 0, 0, 3, 3, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 0, 3, 0, 0, 0, 99, 0, 0, 0, 3, 0, 0, 0,
};

/* The three fixed rewards every party member gets after its growth rewards (func_02035444). */
const struct {
    int id[3];
} data_02042154 = { { 2, 3, 4 } };

/* Signature skill of each character kind, set by func_02035328 when a save record is reset
 * (-1 = none). */
const struct {
    int skill[22];
} data_02042160 = { {
    12, 7, 1, 6, 2, 12, 8, 11, 4, 9, 10, -1,
    3, 0, 12, 5, 12, 12, 12, 12, 12, 12,
} };

/* Reward ids granted by the growth entries (func_02035444): 1..15 through func_02035794,
 * the rest through func_020358c0. */
const struct {
    int id[24];
} data_020421b8 = { {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    21, 34, 37, 40, 88, 62, 33, 20,
} };

/* Key-repeat (func_0203617c): index of each key's press stamp in data_0204c194 ... */
const u16 data_02042218[10] = { 6, 7, 5, 4, 0, 1, 10, 11, 9, 8 };

/* ... and the key bit of each slot, in the same order. */
const u16 data_0204222c[10] = {
    PAD_KEY_UP, PAD_KEY_DOWN, PAD_KEY_LEFT, PAD_KEY_RIGHT,
    PAD_BUTTON_A, PAD_BUTTON_B, PAD_BUTTON_X, PAD_BUTTON_Y,
    PAD_BUTTON_L, PAD_BUTTON_R,
};

/* Signed unit axes shared by the movement, camera and collision code. */
const VecFx32 data_02042240 = { 0, -0x1000, 0 };     /* -Y (down) */
const VecFx32 data_0204224c = { -0x1000, 0, 0 };     /* -X */
const VecFx32 data_02042258 = { 0, 0, 0x1000 };      /* +Z */
const VecFx32 data_02042264 = { 0, 0x1000, 0 };      /* +Y (up) */
const VecFx32 data_02042270 = { 0x1000, 0, 0 };      /* +X */
const VecFx32 data_0204227c = { 0, 0, -0x1000 };     /* -Z */
