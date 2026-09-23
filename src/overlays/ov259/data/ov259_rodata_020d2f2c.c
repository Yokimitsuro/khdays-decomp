/* ov259 .rodata 0x020d2f2c-0x020d2fac: the local initializer templates of the actor's functions,
 * one object per function in the original unit's order. Q12 fixed point for the vectors. */

typedef struct { int x, y, z; } Vec3;

/* func_ov259_020cc218 (constructor): the thirteen hidden part poses. */
typedef struct { int id[13]; } PartPoses;

/* func_ov259_020cd524: pose -> partner motion map (-1 = none), 27 entries (the function copies
 * exactly 27); the trailing zero is the section's alignment pad, kept so the object ends at 0x2fac. */
typedef struct { signed char motion[27]; signed char pad; } PartnerMotionMap;

const PartPoses data_ov259_020d2f2c = { { 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 73 } };

/* func_ov259_020d06b0: lift offsets (0, 0.8125, 0) and (0, 0.375, 0). */
const Vec3 data_ov259_020d2f60 = { 0, 0xd00, 0 };
const Vec3 data_ov259_020d2f6c = { 0, 0x600, 0 };

/* func_ov259_020cff54: lift offset (0, 1.25, 0). */
const Vec3 data_ov259_020d2f78 = { 0, 0x1400, 0 };

/* func_ov259_020d06b0: drop offset (0, -0.375, 0). */
const Vec3 data_ov259_020d2f84 = { 0, -0x600, 0 };

const PartnerMotionMap data_ov259_020d2f90 = { {
    -1, 0, -1, 1, -1, 2, 3, 4, 5, 6, 7, 8, -1, -1, -1, 9, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1,
}, 0 };
