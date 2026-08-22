/*
 * Ov002_ResetViewToDefault - point the global camera straight down -Z at the
 * origin and rebuild both matrices.
 *
 * Same shape as Camera_CommitMatrices (func_02023cc0), which commits an actor's
 * camera: build the projection, clear GX dirty bits 0x50, cache the eye/up/
 * target vectors into the global camera state, build the view matrix, clear
 * dirty bits 0xe8. The difference is that this one uses fixed vectors rather
 * than an actor's - eye 8.0 units back along +Z, target at the origin, up +Y -
 * so the three vectors are built on the stack and copied out.
 *
 * ARM. The three stack vectors are declared in reverse of their frame order so
 * the last declared lands lowest: up at sp+0x10, target at sp+0x1c, eye at
 * sp+0x28, with sp+0x00..0x0c reserved for the projection call's stacked
 * arguments. Each vector's components are assigned z, y, x: the ROM's
 * zero-stores go in descending offset order within every vector.
 */

typedef struct { int x, y, z; } VecFx32;

/* Global camera-commit state (GX dirty flags + cached vectors, data_02047394). */
extern struct {
    char    _p00[0xd4];
    int     flags;          /* +0xd4 */
    char    _pd8[0x218 - 0xd8];
    VecFx32 cachePos;       /* +0x218 (data_020475ac) */
    VecFx32 cacheUp;        /* +0x224 (data_020475b8) */
    VecFx32 cacheTarget;    /* +0x230 (data_020475c4) */
} data_02047394;

extern char data_0204739c[];   /* projection matrix output */
extern char data_020473e0[];   /* view (look-at) matrix output */

extern void func_02004eac(int a, int b, int c, int d, int e, int f, int g,
                          void *projOut);
extern void func_01ff9c04(const VecFx32 *pos, const VecFx32 *up,
                          const VecFx32 *target, void *viewOut);

void func_ov002_02050e64(void)
{
    VecFx32 vPos;
    VecFx32 vTarget;
    VecFx32 vUp;

    func_02004eac(0, 0xc0000, 0, 0x100000, 0, 0x3000, 0x400000,
                  data_0204739c);
    data_02047394.flags &= ~0x50;
    vPos.z = 0x400000;
    vPos.y = 0;
    vPos.x = 0;
    data_02047394.cachePos = vPos;
    vUp.z = 0;
    vUp.y = 0x1000;
    vUp.x = 0;
    data_02047394.cacheUp = vUp;
    vTarget.z = 0;
    vTarget.y = 0;
    vTarget.x = 0;
    data_02047394.cacheTarget = vTarget;
    func_01ff9c04(&vPos, &vUp, &vTarget, data_020473e0);
    data_02047394.flags &= ~0xe8;
}
