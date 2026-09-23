/* ov258 .rodata 0x020d16f4-0x020d1850: the local initializer templates of the actor's functions,
 * one object per function in the original unit's order. Q12 fixed point for the vectors. */

typedef struct { int x, y, z; } Vec3;

/* func_ov258_020cce70: per-move poses of the +0x384 body rig and the +0x3ac tail rig. */
typedef struct { int id[16]; } MovePoses;

/* func_ov258_020cbfc8 (constructor): poses of the 43 hidden parts. */
typedef struct { int id[43]; } PartPoses;

/* func_ov258_020d02f8: the five hit reaction variants a strike picks from at random; the object
 * pads to the section end. */
typedef struct { short mode[5]; short pad; } ReactionVariants;

const MovePoses data_ov258_020d16f4 = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 } };
const MovePoses data_ov258_020d1734 = { { 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33 } };

const PartPoses data_ov258_020d1774 = { {
    34, 35, 36, 37, 38, 39, 41, 42, 43, 44, 45, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
    48, 49, 49, 50, 50, 51, 51, 51, 51, 51, 51, 52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
} };

/* func_ov258_020ce0a0: strike push (0, 1.25, 0). */
const Vec3 data_ov258_020d1820 = { 0, 0x1400, 0 };

/* func_ov258_020ce0a0: reach 7.875 ahead, turned by the heading. */
const Vec3 data_ov258_020d182c = { 0, 0, 0x7e00 };

/* func_ov258_020ce63c: offset 5.0 behind. */
const Vec3 data_ov258_020d1838 = { 0, 0, -0x5000 };

const ReactionVariants data_ov258_020d1844 = { { 1, 9, 5, 6, 10 }, 0 };
