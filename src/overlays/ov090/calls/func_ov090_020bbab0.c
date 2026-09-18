/* Approach step of the ov034 enemy (x4: ov034/052/072/090): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16; with a target the enemy turns towards it (unless the
 * facing is locked) and moves at the rig's speed (+0x2cf8), capped at the remaining distance,
 * while a target closer than 0x333 or no target at all leaves it in place; the vertical speed is
 * set to 0x1333 and the actor's hook runs; past 0x6000 on the +0x4cc counter it hands over to
 * state 0x24. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_02030788(void);
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern int FX_Atan2(int x, int z);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);         /* ScaleVec3Fx12 */
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void *func_ov022_020a35f4(char *self, int state);
extern char *data_ov090_020bcc00;
extern short data_0203d210[];

void *func_ov090_020bbab0(char *self)
{
    Vec3 d;
    Vec3 step;
    Vec3 flat;
    void *next = 0;
    u16 angle;
    int speed = *(int *)(data_ov090_020bcc00 + 0x2cf8);
    int dist;
    unsigned int *node;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    step.z = 0;
    step.y = 0;
    step.x = 0;
    if (func_ov022_020ad114(self) == 0) {
        angle = *(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000;
    } else {
        VEC_Subtract(func_ov022_020ad0c0(self), (Vec3 *)(self + 0x8c + 0x400), &d);
        dist = VEC_Mag(&d);
        if (dist >= 0x333) {
            angle = (u16)FX_Atan2(-d.x, -d.z);
            node = *(unsigned int **)(self + 0x20);
            if ((*node & 0x20) == 0) {
                *(u16 *)((char *)node + 0x80) = angle + 0x8000;
                *(u16 *)((char *)node + 4) |= 0x20;
            }
            if (dist < speed) {
                speed = VEC_Mag(&d);
            }
        } else {
            speed = 0;
            angle = *(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000;
        }
    }
    if (speed > 0) {
        step.x = -data_0203d210[(angle >> 4) * 2];
        step.z = -data_0203d210[(angle >> 4) * 2 + 1];
        step.y = 0;
        func_01ffa724(speed, &step, &step);
    }
    *(int *)(self + 0x58) = 0x1333;
    flat = step;
    flat.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &flat, (Vec3 *)(self + 0x98 + 0x400));
    (*(int (**)(char *))(self + 0x668))(self);
    if (*(int *)(self + 0x4cc) >= 0x6000) {
        next = func_ov022_020a35f4(self, 0x24);
    }
    return next;
}
