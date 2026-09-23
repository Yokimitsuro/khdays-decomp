/* ov256 .rodata tail 0x020d2594-0x020d2660: the local initializer templates of the actor's
 * functions, one object per function in the original unit's order (not the function order, which
 * is why they live here). Objects with a trailing unused vector carry an initializer the function
 * declares but never reads. Q12 fixed point throughout. */

typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 used; Vec3 unused; } VecPair;
typedef struct { Vec3 v[4]; } Vec3x4;
typedef struct { Vec3 spot[5]; Vec3 unused; } SpotTemplates;

/* Ov256_Update (020cd740): arena anchor (-0.25, 3.25, -1.5); an unread point (1.25, 6.5, 7.0). */
const VecPair data_ov256_020d2594 = { { -0x1000, 0xd000, -0x6000 }, { 0x5000, 0x1a000, 0x1c000 } };

/* Ov256_LungeTick (020cf474): strike direction (0, 1.0, 1.0). */
const Vec3 data_ov256_020d25ac = { 0, 0x1000, 0x1000 };

/* Ov256_SweepTick (020cee70): push direction (0, -1.0, 0.75). */
const Vec3 data_ov256_020d25b8 = { 0, -0x1000, 0xc00 };

/* 020ce0dc: arena anchor again, for the return flight. */
const Vec3 data_ov256_020d25c4 = { -0x1000, 0xd000, -0x6000 };

/* 020cea18: the four arena corners a warp picks the nearest of. */
const Vec3x4 data_ov256_020d25d0 = { {
    { -0x4000, 0x9000, -0xf000 }, { 0x8000, 0x10000, 0x4000 },
    { -0x10000, 0xe000, 0x11000 }, { 0x1b000, 0xd000, -0x14000 },
} };

/* 020cea18: the five random warp spots; an unread (0, 0, 2.0). */
const SpotTemplates data_ov256_020d2600 = {
    { { -0x1000, 0xd000, -0x6000 }, { -0x15000, 0x13000, -0x19000 }, { -0x12000, 0x20000, 0xd000 },
      { -0xd000, 0x9000, 0x14000 }, { -0x11000, 0x9000, -0xa000 } },
    { 0, 0, 0x2000 },
};

/* Ov256_StrafeTick (020d1ed0): sidestep (0.22, -0.04, 0); an unread (0, 0, -2.0). */
const VecPair data_ov256_020d2648 = { { 0x380, -0xa0, 0 }, { 0, 0, -0x2000 } };
