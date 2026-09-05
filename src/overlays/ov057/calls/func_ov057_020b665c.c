/* Forward-effect sequence for ov057: while the actor is still in stage 0x30 and
 * the gauge has passed 0x1b000, it retunes channel 0xc8, re-arms the sequence
 * block, and places the effect a fixed offset in front of the actor -- the
 * offset is rotated by the actor's own heading through the shared sin/cos
 * table and added to the anchor at +0x48c. The heading is stored back on the
 * record, the visible bit is raised and the state advances to 2, where the
 * emitter runs until it reports done. */
typedef unsigned short u16;

struct Vec3 { int x, y, z; };
struct Mtx33 { int m[9]; };

extern void func_ov022_020a4490(int pActor, int a, int b);
extern void func_ov057_020b6af4(int pActor, void *block);
extern void MTX_RotY33_(struct Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const struct Vec3 *v, const struct Mtx33 *m, struct Vec3 *dst);
extern void VEC_Add(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *dst);
extern unsigned int func_0202a818(void *p, int a);

extern int data_ov057_020b74a0;
extern short data_0203d210[];

void func_ov057_020b665c(int pActor, int *pEffect, int delta) {
    struct Vec3 effectPosition;
    struct Vec3 effectOffset;
    struct Mtx33 rotation;
    char *pSceneBlock = (char *)(*(int *)&data_ov057_020b74a0 + 0x2c + 0x2c00);
    u16 heading;
    int sinCosIndex;

    if (*pEffect == 1 && *(int *)(pActor + 0x6bc) != 0x30) {
        *pEffect = 0;
    }
    switch (*pEffect) {
    case 1:
        if (*(int *)(pActor + 0x7b0) < 0x1b000) {
            return;
        }
        func_ov022_020a4490(pActor, 0xc8, 1);
        func_ov057_020b6af4(pActor, pSceneBlock + 0x118);

        effectOffset.x = 0x148;
        effectOffset.y = 0;
        effectOffset.z = 0x1800;
        effectPosition = *(struct Vec3 *)(pActor + 0x48c);

        heading = *(u16 *)(*(char **)(pActor + 0x20) + 0x80);
        heading = (u16)(heading - 0x8000);
        heading = (u16)(heading + 0x8000);
        sinCosIndex = heading >> 4;
        MTX_RotY33_(&rotation, data_0203d210[sinCosIndex * 2], data_0203d210[sinCosIndex * 2 + 1]);
        MTX_MultVec33(&effectOffset, &rotation, &effectOffset);
        VEC_Add(&effectPosition, &effectOffset, &effectPosition);

        *(u16 *)((char *)pEffect + 0x80) = heading;
        *(u16 *)((char *)pEffect + 4) |= 0x20;
        *(struct Vec3 *)((char *)pEffect + 0xa8) = effectPosition;
        *pEffect = 2;
        return;
    case 2:
        if (func_0202a818((void *)((char *)pEffect + 4), delta) != 0) {
            *pEffect = 0;
        }
        return;
    }
}
