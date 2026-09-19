/* Ride step: while bit 0 of the actor's +0x3d4 is set its +0xa0 pose is copied from the +0x384
 * mount; otherwise the +0x28 yaw steps towards the +0x2c target by the +0x24 rate (with the
 * +0x3c step state) and the pose
 * is rebuilt about world Y. Outside kind 0xb an emptied +0x21a health requests pose 0xb. The +8
 * velocity is handed to the actor's +0xf0 motion slot and cleared. */
typedef struct { int x, y, z; } Vec3;
struct blk11 { int w[11]; };
struct Bits3d4 { int b0 : 1; };
struct Ov236ActorPose { char pad[0xa0]; struct blk11 pose; };
extern int func_0203d040(int cur, int want, int step, int *state);
extern void func_0203c9b4(void *quat, const Vec3 *axis, int angle);
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

void func_ov236_020d3f50(int *self) {
    int *ctx = (int *)self[1];
    int actor = ctx[0];
    if (((struct Bits3d4 *)(actor + 0x3d4))->b0 != 0) {
        ((struct Ov236ActorPose *)actor)->pose = ((struct Ov236ActorPose *)*(int *)(actor + 0x384))->pose;
    } else {
        ctx[0xa] = func_0203d040(ctx[0xa], ctx[0xb], ctx[9], ctx + 0xf);
        func_0203c9b4((void *)(ctx[0] + 0xa0), &data_02042264, ctx[0xa]);
    }
    actor = ctx[0];
    if (*(signed char *)(actor + 0x100 + 0xc6) != 0xb) {
        if (*(short *)(actor + 0x200 + 0x1a) == 0) {
            *(unsigned char *)(actor + 0x1c7) = 0xb;
        }
    }
    {
        Vec3 *p8 = (Vec3 *)(ctx + 2);
        *(Vec3 *)(ctx[0] + 0xf0) = *p8;
        *p8 = data_02041dc8;
    }
}
