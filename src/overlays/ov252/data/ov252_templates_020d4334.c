/* ov252 .rodata tail 0x020d4334-0x020d450c: the local initializer templates of the actor's
 * functions, one object per function in the order the original unit laid them out (not the
 * function order, which is why they live here rather than in the functions' own files). Some
 * objects carry a second initializer the function declares but never reads; mwcc keeps its
 * template even though the copy is dropped. Q12 fixed point throughout. */

typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

/* Ov252_HitFilter (020ce5c4): reaction mode pairs, then three unread tuning words (the blast
 * window 0x1c28 / 0x990 of Ov252_BlastTick and the 6.5 hover height of 020cec2c). */
typedef struct { u8 normal[2]; u8 special[2]; int unused[3]; } HitFilterTemplates;

typedef struct { Vec3 used; Vec3 unused; } VecPair;
typedef struct { Vec3 ray; Vec3 unusedHome[2]; } GroundCheckTemplates;
typedef struct { Vec3 v[2]; } Vec3x2;
typedef struct { Vec3 v[5]; } Vec3x5;
typedef struct { Vec3 v[10]; } Vec3x10;
typedef struct { Vec3 v[8]; } Vec3x8;

const HitFilterTemplates data_ov252_020d4334 = { { 0, 1 }, { 2, 3 }, { 0x1c28, 0x6800, 0x990 } };

/* 020d1c7c: offset (0, 2.5, -2.5). */
const Vec3 data_ov252_020d4344 = { 0, 0x2800, -0x2800 };

/* Ov252_SinkTick (020d0cc0): respawn point 3.0 below the origin. */
const Vec3 data_ov252_020d4350 = { 0, -0x30000, 0 };

/* Ov252_GroundCheck (020cdc78): ground ray (0, -896.0, 66.0); two unread home points. */
const GroundCheckTemplates data_ov252_020d435c = {
    { 0, -0x380000, 0x42000 },
    { { 0x36000, 0, 0x74000 }, { 0x36000, 0x480, 0x74000 } },
};

/* 020d1c7c: ground ray (0, -896.0, 0). */
const Vec3 data_ov252_020d4380 = { 0, -0x380000, 0 };

/* Ov252_BlastTick (020d1674): blast offset 2.0 ahead; an unread 1.0 offset. */
const VecPair data_ov252_020d438c = { { 0, 0, 0x2000 }, { 0, 0, 0x1000 } };

/* Ov252_RetreatDecision (020cf3b8): home point (3.375, 0, 7.25). */
const Vec3 data_ov252_020d43a4 = { 0x36000, 0, 0x74000 };

/* 020cec2c: shot aim 1.8125 behind; an unread box half-extent (0.5, 0.8125, 0.5). */
const VecPair data_ov252_020d43b0 = { { 0, 0, -0x1d000 }, { 0x2000, 0x3400, 0x2000 } };

/* 020cec2c: shot ground probe 3.5 down. */
const Vec3 data_ov252_020d43c8 = { 0, -0x38000, 0 };

/* 020d1c7c: box centre (0, 0, 0.25) and half-extents (2.5, 4.0625, 2.5). */
const Vec3x2 data_ov252_020d43d4 = { { { 0, 0, 0x400 }, { 0x2800, 0x4100, 0x2800 } } };

/* 020d0a8c: five points. */
const Vec3x5 data_ov252_020d43ec = { {
    { -0x4000, -0xb000, -0xd000 }, { 0xb0000, -0xb000, -0x100000 }, { 0xf0000, -0xb000, 0x28000 },
    { -0x440000, -0xb000, 0xd0000 }, { 0x35000, -0xb000, 0x78000 },
} };

/* 020d1c7c: ten points on a ring of radius ~1.8 around the actor (y = 0). */
const Vec3x10 data_ov252_020d4428 = { {
    { 0, 0, -0x1d000 }, { 0x14600, 0, -0x17600 }, { 0x16000, 0, -0x14600 }, { 0x16000, 0, 0x14600 },
    { 0x14600, 0, 0x17600 }, { 0, 0, 0x1d000 }, { -0x14600, 0, 0x17600 }, { -0x16000, 0, 0x14600 },
    { -0x16000, 0, -0x14600 }, { -0x14600, 0, -0x17600 },
} };

/* Ov252_SpawnBomb (020d3988): ground probe 3.125 down. */
const Vec3 data_ov252_020d44a0 = { 0, -0x32000, 0 };

/* Ov252_SpawnBomb (020d3988): ring of eight avoidance offsets at 6.0 (axes and diagonals). */
const Vec3x8 data_ov252_020d44ac = { {
    { 0x6000, 0, 0 }, { -0x6000, 0, 0 }, { 0x6000, 0, 0x6000 }, { 0x6000, 0, -0x6000 },
    { -0x6000, 0, 0x6000 }, { -0x6000, 0, -0x6000 }, { 0, 0, 0x6000 }, { 0, 0, -0x6000 },
} };
