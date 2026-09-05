/* Second step of the ov038 charge: while the actor is still in stage 0x30 and
 * the gauge has passed 0x1b000, it retunes channel 0xc8, re-arms the sequence
 * block, and places the effect a fixed offset in front of the actor -- the
 * offset is rotated by the actor's own heading through the shared sin/cos
 * table and added to the anchor at +0x48c. The heading is stored back on the
 * record, the visible bit is raised and the state advances to 2, where the
 * emitter runs until it reports done. */
typedef unsigned short u16;

struct Vec3 { int x, y, z; };
struct Mtx33 { int m[9]; };

extern void func_ov022_020a4490(int self, int a, int b);
extern void func_ov038_020b42f4(int self, void *block);
extern void MTX_RotY33_(struct Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const struct Vec3 *v, const struct Mtx33 *m, struct Vec3 *dst);
extern void VEC_Add(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *dst);
extern unsigned int func_0202a818(void *p, int a);

extern int data_ov038_020b4ca0;
extern short data_0203d210[];

void func_ov038_020b3e5c(int self, int *p2, int p3) {
    struct Vec3 vAnchor;
    struct Vec3 vOffset;
    struct Mtx33 mtx;
    char *blk = (char *)(*(int *)&data_ov038_020b4ca0 + 0x2c + 0x2c00);
    u16 angle;
    int idx;

    if (*p2 == 1 && *(int *)(self + 0x6bc) != 0x30) {
        *p2 = 0;
    }
    switch (*p2) {
    case 1:
        if (*(int *)(self + 0x7b0) < 0x1b000) {
            return;
        }
        func_ov022_020a4490(self, 0xc8, 1);
        func_ov038_020b42f4(self, blk + 0x118);

        vOffset.x = 0x148;
        vOffset.y = 0;
        vOffset.z = 0x1800;
        vAnchor = *(struct Vec3 *)(self + 0x48c);

        angle = *(u16 *)(*(char **)(self + 0x20) + 0x80);
        angle = (u16)(angle - 0x8000);
        angle = (u16)(angle + 0x8000);
        idx = angle >> 4;
        MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        MTX_MultVec33(&vOffset, &mtx, &vOffset);
        VEC_Add(&vAnchor, &vOffset, &vAnchor);

        *(u16 *)((char *)p2 + 0x80) = angle;
        *(u16 *)((char *)p2 + 4) |= 0x20;
        *(struct Vec3 *)((char *)p2 + 0xa8) = vAnchor;
        *p2 = 2;
        return;
    case 2:
        if (func_0202a818((void *)((char *)p2 + 4), p3) != 0) {
            *p2 = 0;
        }
        return;
    }
}
