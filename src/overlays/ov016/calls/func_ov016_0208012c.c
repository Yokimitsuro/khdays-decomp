/* func_ov016_0208012c -- Ov016_PlatformMoveTo: move the platform to pPos, remembering the
 * offset from its rest position (+0xd0) at +0x1a0 and pushing the new position into the
 * render node (+0x28, 0202b450). */
typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016Platform {
    unsigned char pad_000[0x28];
    unsigned char node[0xd0 - 0x28];   /* 0x28: render node */
    VecFx32 rest;                      /* 0xd0 */
    unsigned char pad_0dc[0x1a0 - 0xdc];
    VecFx32 offset;                    /* 0x1a0 */
} Ov016Platform;

extern void func_0202b450(void *pNode, VecFx32 *pPos);   /* Actor_SetVecAndSyncChild */

void func_ov016_0208012c(Ov016Platform *pSelf, VecFx32 *pPos)
{
    VecFx32 rest;

    rest = pSelf->rest;
    pSelf->offset.x = pPos->x - rest.x;
    pSelf->offset.y = pPos->y - rest.y;
    pSelf->offset.z = pPos->z - rest.z;
    func_0202b450(pSelf->node, pPos);
}
