/* Node callback of the ov144 enemy (and its byte-identical twin) that runs when the node's key
 * (its +0xae byte when flag bit 4 is set, else -1) matches the actor's +0x3a0 slot: reads the
 * current matrix, copies its translation to the +0x388 item's +0x40 point (raised by 0x1000),
 * raises the +0x9c part's +0x44 height by 0x400, and rebuilds the +0x398 transform's +0x30
 * child from the actor's +0xa0 rotation at (+0xb0, part height, +0xb8); the node's +0x24 word
 * and +0x92 byte are cleared. */
typedef unsigned char u8;
typedef unsigned int u32;
struct Vecx32 { int x, y, z; };
struct MtxFx43 { int m[9]; struct Vecx32 t; };

extern void func_02016294(struct MtxFx43 *dst, void *src);
extern void func_0203c960(void *transform);
extern void func_0203c9d0(void *transform, void *quat);
extern void func_0203ca30(void *transform, struct Vecx32 *pos);

void func_ov144_020cbfc4(char *node)
{
    int actor = *(int *)(*(int *)(node + 4) + 0x2c);
    struct MtxFx43 mtx;
    struct Vecx32 pos;
    u32 key;

    key = (*(u32 *)(node + 8) & 0x10) ? *(u8 *)(node + 0xae) : 0xffffffff;
    if (*(unsigned short *)(actor + 0x3a0) != key) {
        return;
    }
    func_02016294(&mtx, 0);
    pos = mtx.t;
    *(struct Vecx32 *)(*(int *)(actor + 0x388) + 0x40) = pos;
    *(int *)(*(int *)(actor + 0x388) + 0x44) += 0x1000;
    *(int *)(*(int *)(actor + 0x9c) + 0x44) += 0x400;
    pos.y = *(int *)(*(int *)(actor + 0x9c) + 0x44);
    func_0203c960((void *)(*(int *)(actor + 0x398) + 0x30));
    pos.x = *(int *)(actor + 0xb0);
    pos.z = *(int *)(actor + 0xb8);
    func_0203c9d0((void *)(*(int *)(actor + 0x398) + 0x30), (void *)(actor + 0xa0));
    func_0203ca30((void *)(*(int *)(actor + 0x398) + 0x30), &pos);
    *(int *)(node + 0x24) = 0;
    *(u8 *)(node + 0x92) = 0;
}
