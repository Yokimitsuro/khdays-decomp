/* Volley step of the ov035 enemy (x4: ov035/053/073/091): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16; before the first shot the node turns to face the target
 * on the ground plane unless the facing is locked; the shared sampler's motion is folded into
 * the position at +0x498 (a vertical component becomes the vertical speed, otherwise -- unless
 * grounded -- bit 46 is raised and the speed cleared); at 0x3000 on the +0x7b0 timer with shots
 * left (rig +0x2cb0 < +0x2cb1) the animation rewinds and bit 29 is raised, and at 0 a shot goes
 * out (the mark or the aimed request by the rig's +0x2ca4 mode) and the count advances. The
 * actor's hook decides bit 1 of +0x694: becoming active raises bit 49, shows the node and, for
 * the local player, sets bit 1 of +0x464; while active the velocities are cleared, bit 2 is
 * raised and the enemy lands (state 0 with the slot callback when grounded, else state 2). */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef struct { int x, y, z; } Vec3;

extern int func_02030788(void);
extern int func_ov022_0209fe20(char *self, void *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0202af1c(void *node);
extern void *func_ov022_020a35f4(char *self, int state);
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Atan2(int x, int z);
extern void func_01fff774(void *animation, int track, int frame);              /* Anim_SetFrameWrapped */
extern void func_ov054_020b6544(char *self);
extern void func_ov054_020b66f0(char *self);
extern char *data_ov054_020b74a0;

void *func_ov054_020b702c(char *self)
{
    int r;
    Vec3 d;
    Vec3 sample;
    Vec3 step;
    char *rig = data_ov054_020b74a0 + 0xa4 + 0x2c00;
    void *next = 0;
    unsigned int *node;
    unsigned short a;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    if (*(signed char *)(rig + 0xc) == 0 && func_ov022_020ad114(self) != 0) {
        VEC_Subtract(func_ov022_020ad0c0(self), (Vec3 *)(self + 0x8c + 0x400), &d);
        d.y = 0;
        if (VEC_Mag(&d) != 0) {
            func_01ff8d18(&d, &d);
        }
        a = (unsigned short)FX_Atan2(-d.x, -d.z);
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            *(unsigned short *)((char *)node + 0x80) = a + 0x8000;
            *(unsigned short *)((char *)node + 4) |= 0x20;
        }
    }
    func_ov022_0209fe20(self, &sample);
    if (sample.y != 0) {
        *(int *)(self + 0x58) = sample.y;
    } else if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    if (*(int *)(self + 0x7b0) == 0x3000 && *(signed char *)(rig + 0xc) < *(signed char *)(rig + 0xd)) {
        func_01fff774(*(char **)(self + 0x20) + 4, 0, 0);
        *(int *)(self + 0x7b0) = 0;
        *(unsigned long long *)self |= 0x20000000;
    }
    if (*(int *)(self + 0x7b0) == 0) {
        if (*(int *)rig == 0) {
            func_ov054_020b6544(self);
        } else {
            func_ov054_020b66f0(self);
        }
        *(signed char *)(rig + 0xc) += 1;
    }
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (((Flags *)(self + 0x694))->b1) {
        *(unsigned long long *)self |= 0x2000000000000ULL;
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            func_0202af1c(node + 1);
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x464) |= 2;
        }
    }
    if (((Flags *)(self + 0x694))->b1) {
        *(int *)(self + 0x4a0) = 0;
        *(int *)(self + 0x49c) = 0;
        *(int *)(self + 0x498) = 0;
        *(int *)(self + 0x6a0) = 0;
        *(int *)(self + 0x69c) = 0;
        *(int *)(self + 0x698) = 0;
        *(unsigned long long *)self |= 4;
        if ((*(int *)(self + 0x24) & 4) != 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0);
            next = func_ov022_020a35f4(self, 0);
        } else {
            next = func_ov022_020a35f4(self, 2);
        }
    }
    return next;
}
