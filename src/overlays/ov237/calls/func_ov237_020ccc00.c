/* Per-frame update of the ov237 actor: the +0x488 and +0x3ec rigs follow the +0x444 body transform
 * (the first 0.5 lower); in move 0xc or +0x49e mode 3 and up the loop effects stop (020ccbac), and a
 * +0x4b4 hold releases the three +0x490 effect handles. The +0x3f0 part points from the +0x448 joint
 * to the +0x44c joint, the +0x48c rig copies its +0x58 pose, and both take the actor transform (+0xa0).
 * In move 10 a linked partner's +0x384 / +0x3ac rigs follow the actor's frame; outside move 9 a
 * pending +0x498 item is dropped (020cb100). Each segment of both arms (+0x3f4) points along its joint
 * chain (+0x41c, from the +0x44c joint for the first) and takes its joint's transform; the +0x45c
 * transform copies the actor's, the +0x470 clock advances by 2.5 and the base update runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[11]; } SrtTransform;
typedef struct { int w[8]; } Pose32;
struct Xf10 { char pad[0x10]; SrtTransform srt; };
struct Xf4 { char pad[4]; SrtTransform srt; };
struct Pose58 { char pad[0x58]; Pose32 pose; };
struct Ov237Body { char pad[0x3f4]; int arms[2][5]; int joints[2][5]; };

extern void func_ov237_020ccbac(char *self);
extern void func_0203c650(int model, int handle);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_0203bec0(int rig, int channel);
extern void func_0203be9c(int rig, int channel, int frame);
extern void func_ov107_020cb100(int item);
extern void func_ov107_020c7ca4(char *self);

void func_ov237_020ccc00(char *self)
{
    Vec3 d;
    Vec3 e;
    int k;
    long m;
    int part;

    ((struct Xf10 *)(**(int **)(self + 0x488)))->srt = ((struct Xf4 *)*(int *)(self + 0x444))->srt;
    *(int *)(**(int **)(self + 0x488) + 0x24) -= 0x800;
    ((struct Xf10 *)(*(int *)(self + 0x3ec)))->srt = ((struct Xf4 *)*(int *)(self + 0x444))->srt;
    if (*(signed char *)(self + 0x1c6) == 0xc || *(u8 *)(self + 0x49e) >= 3) {
        func_ov237_020ccbac(self);
    }
    if (*(int *)(self + 0x4b4) != 0) {
        u8 i;

        for (i = 0; i < 3; i++) {
            if (*(int *)(*(int *)(self + 0x490) + i * 8 + 0x7c) != 0) {
                func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x490) + i * 8 + 0x7c));
                *(int *)(*(int *)(self + 0x490) + i * 8 + 0x7c) = 0;
            }
        }
    }
    {
        int part = *(int *)(self + 0x3f0);

        VEC_Subtract((Vec3 *)(*(int *)(self + 0x44c) + 0x14), (Vec3 *)(*(int *)(self + 0x448) + 0x14), &d);
        *(int *)(part + 0x70) = func_01ff8d18(&d, (Vec3 *)(part + 0x64));
        ((struct Pose58 *)**(int **)(self + 0x48c))->pose = ((struct Pose58 *)part)->pose;
    }
    ((struct Xf10 *)(*(int *)(self + 0x3f0)))->srt = *(SrtTransform *)(self + 0xa0);
    ((struct Xf10 *)(**(int **)(self + 0x48c)))->srt = *(SrtTransform *)(self + 0xa0);
    if (*(int *)(self + 0x4ac) != 0 && *(signed char *)(self + 0x1c6) == 10) {
        int frame = func_0203bec0(*(int *)(self + 0x384), 0);

        func_0203be9c(*(int *)(*(int *)(self + 0x4a4) + 0x384), 0, frame);
        func_0203be9c(*(int *)(*(int *)(self + 0x4a4) + 0x3ac), 0, frame);
    }
    if (*(signed char *)(self + 0x1c6) != 9 && *(int *)(self + 0x498) != 0) {
        func_ov107_020cb100(*(int *)(self + 0x498));
        *(int *)(self + 0x498) = 0;
    }
    for (k = 0; k < 2; k++) {
        for (m = 0; m < 5; m++) {
            part = ((struct Ov237Body *)self)->arms[k][m];
            if (m == 0) {
                VEC_Subtract((Vec3 *)(*(int *)(self + 0x44c) + 0x14),
                             (Vec3 *)(((struct Ov237Body *)self)->joints[k][m] + 0x14), &e);
            } else {
                VEC_Subtract((Vec3 *)(((struct Ov237Body *)self)->joints[k][m - 1] + 0x14),
                             (Vec3 *)(((struct Ov237Body *)self)->joints[k][m] + 0x14), &e);
            }
            func_01ff8d18(&e, &e);
            *(Vec3 *)(part + 0x64) = e;
            *(int *)(part + 0x70) = 0x1000;
            ((struct Xf10 *)(((struct Ov237Body *)self)->arms[k][m]))->srt =
                ((struct Xf4 *)((struct Ov237Body *)self)->joints[k][m])->srt;
        }
    }
    *(SrtTransform *)(self + 0x45c) = *(SrtTransform *)(self + 0xa0);
    *(int *)(self + 0x470) += 0x2800;
    func_ov107_020c7ca4(self);
}
