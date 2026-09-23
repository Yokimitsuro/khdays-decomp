/* Update hook of the ov237 spark emitter (context = the emitter state): each live record of the owner's
 * +0x90 ring grows in (phase 0: scale 1.0), then (phase 1) while the actor is in move 1 without a
 * +0x4c0 hold and not in mode 3 its 1.125 x 0.25 box pushes the targets it touches away at 0.5 (lifted
 * 0.3125, kind 1) with effect 1 and hit sound 0x12d variant 8; the +0x20 age runs up at the frame rate
 * and past 4.0 the record fades (phase 2: the scale drops by a fifth each frame, dying under 1/16). */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
typedef struct { Vec3 pos; Vec3 axis[3]; int ext[3]; } Box;
typedef struct { int scale; int unk4; Quat rot; int phase; int value; int age; char pad24[8]; Vec3 pos; } Particle;

extern int func_ov107_020c8df0(int owner, void *box, int *hits);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, unsigned char kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;
extern const Vec3 data_02042270;

void func_ov237_020d1610(char *owner, int unused, int *ctx)
{
    int hits[4];
    Box box;
    Vec3 push;
    Vec3 pos;
    Vec3 ax;
    Vec3 ay;
    Vec3 az;
    int scale;
    int j;
    Particle *p;
    int n;
    int i;

    for (i = 0; i < *(int *)(owner + 0x8c); i++) {
        p = &((Particle *)*(int *)(owner + 0x90))[i];
        scale = p->scale;

        if (scale > 0) {
            switch (p->phase) {
            case 0:
                p->scale = 0x1000;
                p->phase = 1;
                break;
            case 1:
                if (*(int *)(ctx[3] + 0x50) == 1 && *(int *)(ctx[3] + 0x4c0) == 0 &&
                    *(signed char *)(ctx[3] + 0x1c6) != 3) {
                    ax = data_02042270;
                    ay = data_02042264;
                    az = data_02042258;
                    box.pos = p->pos;
                    box.axis[0] = ax;
                    box.axis[1] = ay;
                    box.axis[2] = az;
                    box.ext[0] = 0x900;
                    box.ext[1] = 0x200;
                    box.ext[2] = 0x900;
                    n = func_ov107_020c8df0(ctx[3], &box, hits);
                    for (j = 0; j < n; j++) {
                        VEC_Subtract((Vec3 *)(hits[j] + 0x190), &p->pos, &push);
                        func_01ffa724(0x800, &push, &push);
                        push.y += 0x500;
                        if (func_ov107_020ca918(hits[j], ctx[3], ctx[3], 1, &push, 0) != 0) {
                            pos = *(Vec3 *)(hits[j] + 0x190);
                            pos.y += 0x1400;
                            func_ov107_020c0b90(ctx[3], 1, pos, 1);
                            func_ov107_020c5af8(ctx[3], 0x12d, 8, &p->pos);
                        }
                    }
                }
                p->age += *(int *)ctx[2];
                if (p->age >= 0x4000) {
                    p->phase = 2;
                }
                break;
            case 2:
                p->scale = scale + scale * -2 / 10;
                if (p->scale < 0x100) {
                    p->scale = 0;
                }
                break;
            }
        }
    }
}
