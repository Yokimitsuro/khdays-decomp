/* Attack step of the ov048 enemy (x4: ov048/067/086/103): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16; from 0x15000 on the +0x7b0 timer the rig's progress
 * (+0x2f90) accumulates the heading and the enemy flies its own heading (nudged 0xfff either
 * way by the +0x1a steer bits and clamped by the turn helper, the node turning unless locked) at
 * the rig's speed (+0x2f94), before that the shared sampler drives it; a vertical component
 * becomes the vertical speed, otherwise -- unless grounded -- bit 46 is raised and the speed
 * cleared. The actor's hook decides bit 1 of +0x694. The attack ends when the progress reaches
 * the rig's duration (+0x2f98) or the burst asks for it (step 1, or step 2 which also marks the
 * alternate ending): the enemy hands over to state 0x24 (0x23 for the alternate ending);
 * otherwise an activation rewinds the animation to 0x15000, clears the bit and raises bit 29. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

extern int func_02030788(void);
extern int func_ov022_0209fe20(char *self, void *out);
extern int func_ov022_020ad4e8(char *self, unsigned int angle);            /* Ov022_ClampAngleTowardTarget */
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);            /* ScaleVec3Fx12 */
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov067_020b68c8(char *self);
extern void *func_ov022_020a35f4(char *self, int state);
extern void func_01fff774(void *animation, int track, int frame);          /* Anim_SetFrameWrapped */
extern char *data_ov067_020b7380;
extern short data_0203d210[];

void *func_ov067_020b6d8c(char *self)
{
    Vec3 sample;
    Vec3 step;
    char *rig = data_ov067_020b7380 + 0x2c + 0x2c00;
    void *next = 0;
    int bDone = 0;
    int bAlt = 0;
    int a;
    unsigned int *node;
    int r;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    if (*(int *)(self + 0x7b0) >= 0x15000) {
        *(int *)(rig + 0x364) += *(short *)(self + 0x2aba);
    }
    if (*(int *)(self + 0x7b0) < 0x15000) {
        func_ov022_0209fe20(self, &sample);
    } else {
        a = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
        if ((*(u16 *)(self + 0x1a) & 0x20) != 0) {
            a += 0xfff;
        } else if ((*(u16 *)(self + 0x1a) & 0x10) != 0) {
            a -= 0xfff;
        }
        a = func_ov022_020ad4e8(self, a);
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            *(u16 *)((char *)node + 0x80) = a + 0x8000;
            *(u16 *)((char *)node + 4) |= 0x20;
        }
        sample.x = -data_0203d210[(a >> 4) * 2];
        sample.z = -data_0203d210[(a >> 4) * 2 + 1];
        sample.y = 0;
        func_01ffa724(*(int *)(rig + 0x368), &sample, &sample);
    }
    if (sample.y != 0) {
        *(int *)(self + 0x58) = sample.y;
    } else if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (*(int *)(rig + 0x364) >= *(int *)(rig + 0x36c)) {
        bDone = 1;
    }
    if (*(int *)(self + 0x7b0) >= 0x15000) {
        switch (func_ov067_020b68c8(self)) {
        case 2:
            bDone = 1;
            bAlt = bDone;
            break;
        case 1:
            bDone = 1;
            break;
        }
    }
    if (bDone != 0) {
        if (bAlt == 0) {
            next = func_ov022_020a35f4(self, 0x24);
        } else {
            next = func_ov022_020a35f4(self, 0x23);
        }
    } else if (((Flags *)(self + 0x694))->b1) {
        ((Flags *)(self + 0x694))->b1 = 0;
        func_01fff774(*(char **)(self + 0x20) + 4, 0, 0x15000);
        *(int *)(self + 0x7b0) = 0x15000;
        *(unsigned long long *)self |= 0x20000000;
    }
    return next;
}
