/* Render callback of the ov218 actor's +0x3a8 joint: when the node being drawn is that joint (its
 * 0xae byte when flag bit 4 is set, else -1), the current matrix is read back (02016294) and its
 * translation stored in the actor's +0x39c point. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; Vec3 trans; } MtxFx43;

extern void func_02016294(MtxFx43 *dst, void *src);

void func_ov218_020cbfc4(int node)
{
    int actor = *(int *)(*(int *)(node + 4) + 0x2c);
    MtxFx43 mtx;
    u32 key = (*(u32 *)(node + 8) & 0x10) ? *(u8 *)(node + 0xae) : 0xffffffff;

    if (key != *(u32 *)(actor + 0x3a8)) {
        return;
    }
    func_02016294(&mtx, 0);
    *(Vec3 *)(actor + 0x39c) = mtx.trans;
}
