/* Hover step of the mission enemy: on the local player both 64-bit flag words at +0x464 and
 * +0x46c get bit 16. In mode 0x2f with the +0x7b0 timer still at or under 0xf000 the shared
 * sampler drives the step (its vertical part becomes the fall speed, or in the air bit 46 is
 * raised and the speed cleared). Otherwise, with a cached heading (+0x2abc) and a live but not
 * yet finished emitter at +0x22f8, the node turns towards the heading (plus the +0x478 offset,
 * clamped by the turn helper) unless the facing is locked, the enemy moves along it at the owner
 * block's +0xc speed and mode 0x32 is entered; failing that, mode 0x32 is left for 0x2f with the
 * animation and timer wound to 0x18000 and the enemy stays put, and in the air with bit 36 the
 * fall speed is -0x8f (-0xd6 in hard mode). The step is applied on the ground plane, the attack
 * burst ticks when not sampling, and the actor's hook decides bit 1 of +0x694: becoming active
 * hands over to state 0x22 (finished emitter) or 0x23 (quiet emitter), or in mode 0x2f rewinds
 * the animation and timer to 0x18000. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

extern int func_02030788(void);
extern int func_ov022_02095524(char *emitter);
extern int func_ov022_02095554(char *emitter);
extern int func_ov022_020ad4e8(char *self, unsigned int angle);            /* Ov022_ClampAngleTowardTarget */
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);            /* ScaleVec3Fx12 */
extern void func_01fff774(void *animation, int track, int frame);          /* Anim_SetFrameWrapped */
extern void func_ov022_0209fe20(char *self, Vec3 *out);
extern int func_02023c40(void);                                            /* game mode: 1 = hard */
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov043_020b45b8(char *self);
extern void *func_ov022_020a35f4(char *self, int state);
extern char *data_ov043_020b58e0;
extern short data_0203d210[];

void *func_ov043_020b3e24(char *self)
{
    Vec3 step;
    Vec3 flat;
    void *next = 0;
    char *pBlock = data_ov043_020b58e0 + 0x138 + 0x2c00;
    int bSample;
    int a;
    unsigned int *node;
    int r;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    if (*(int *)(self + 0x6bc) == 0x2f && *(int *)(self + 0x7b0) <= 0xf000) {
        bSample = 1;
    } else {
        bSample = 0;
        if (*(int *)(self + 0x2abc) != -1 && func_ov022_02095524(self + 0x2f8 + 0x2000) != 0
            && func_ov022_02095554(self + 0x2f8 + 0x2000) == 0) {
            a = func_ov022_020ad4e8(self, (u16)(*(int *)(self + 0x2abc) + *(short *)(self + 0x478)));
            node = *(unsigned int **)(self + 0x20);
            if ((*node & 0x20) == 0) {
                *(u16 *)((char *)node + 0x80) = a + 0x8000;
                *(u16 *)((char *)node + 4) |= 0x20;
            }
            step.x = -data_0203d210[(a >> 4) * 2];
            step.z = -data_0203d210[(a >> 4) * 2 + 1];
            step.y = 0;
            func_01ffa724(*(int *)(pBlock + 0xc), &step, &step);
            (*(void (**)(char *, int))(self + 0x664))(self, 0x32);
        } else {
            if (*(int *)(self + 0x6bc) == 0x32) {
                (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
                func_01fff774(*(char **)(self + 0x20) + 4, 0, 0x18000);
                *(int *)(self + 0x7b0) = 0x18000;
            }
            step.z = 0;
            step.y = 0;
            step.x = 0;
        }
    }
    if (bSample != 0) {
        func_ov022_0209fe20(self, &step);
        if (step.y != 0) {
            *(int *)(self + 0x58) = step.y;
        } else if ((*(int *)(self + 0x24) & 4) == 0) {
            *(unsigned long long *)self |= 0x400000000000ULL;
            *(int *)(self + 0x58) = 0;
        }
    } else {
        if ((*(int *)(self + 0x24) & 4) == 0) {
            if ((*(unsigned long long *)self & 0x1000000000ULL) != 0) {
                *(int *)(self + 0x58) = func_02023c40() == 1 ? -0xd6 : -0x8f;
            }
        }
    }
    flat = step;
    flat.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &flat, (Vec3 *)(self + 0x98 + 0x400));
    if (bSample == 0) {
        func_ov043_020b45b8(self);
    }
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (((Flags *)(self + 0x694))->b1) {
        if (func_ov022_02095554(self + 0x2f8 + 0x2000) == 0) {
            if (func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
                next = func_ov022_020a35f4(self, 0x23);
            } else if (*(int *)(self + 0x6bc) == 0x2f) {
                func_01fff774(*(char **)(self + 0x20) + 4, 0, 0x18000);
                *(int *)(self + 0x7b0) = 0x18000;
            }
        } else {
            next = func_ov022_020a35f4(self, 0x22);
        }
    }
    return next;
}
