/* Idle step of the ov033 enemy (x4: ov033/051/071/089): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16; the node turns (through the turn helper) to its own
 * heading nudged 0xfff either way by the +0x1a steer bits, unless the facing is locked; the
 * sampler's motion is folded into the position at +0x498 (in the air with bit 36 or an unset
 * vertical speed, bit 46 is raised and the speed cleared); the actor's hook decides bit 1 of
 * +0x694 and, with the emitter at +0x22f8 busy, an activation rewinds the animation, clears the
 * timer and the bit and raises bit 29; the forward burst is tried; an active enemy hands over to
 * state 0x23, and a +0x1c state of 5 or 6 to state 0x22. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

extern int func_02030788(void);
extern int func_ov022_020ad4e8(char *self, unsigned int angle);            /* Ov022_ClampAngleTowardTarget */
extern int func_ov022_0209fe20(char *self, void *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov022_02095524(char *emitter);
extern void func_01fff774(void *animation, int track, int frame);          /* Anim_SetFrameWrapped */
extern void func_ov033_020b4220(char *self);
extern void *func_ov022_020a35f4(char *self, int state);

void *func_ov033_020b3bc4(char *self)
{
    Vec3 sample;
    Vec3 step;
    void *next = 0;
    int a;
    unsigned int *node;
    int r;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    a = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    if ((*(u16 *)(self + 0x1a) & 0x20) != 0) {
        a += 0xfff;
    } else if ((*(u16 *)(self + 0x1a) & 0x10) != 0) {
        a -= 0xfff;
    }
    a = func_ov022_020ad4e8(self, (u16)a);
    node = *(unsigned int **)(self + 0x20);
    if ((*node & 0x20) == 0) {
        *(u16 *)((char *)node + 0x80) = a + 0x8000;
        *(u16 *)((char *)node + 4) |= 0x20;
    }
    func_ov022_0209fe20(self, &sample);
    if ((*(int *)(self + 0x24) & 4) == 0
        && ((*(unsigned long long *)self & 0x1000000000ULL) != 0 || *(int *)(self + 0x58) == 0x80000000)) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    if (next == 0) {
        r = (*(int (**)(char *))(self + 0x668))(self);
        ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
        if (((Flags *)(self + 0x694))->b1 && func_ov022_02095524(self + 0x2f8 + 0x2000) != 0) {
            func_01fff774(*(char **)(self + 0x20) + 4, 0, 0);
            *(int *)(self + 0x7b0) = 0;
            ((Flags *)(self + 0x694))->b1 = 0;
            *(unsigned long long *)self |= 0x20000000;
        }
    }
    func_ov033_020b4220(self);
    if (((Flags *)(self + 0x694))->b1) {
        next = func_ov022_020a35f4(self, 0x23);
    }
    if (next == 0 && (u16)(*(u16 *)(self + 0x1c) + 0xfffb) <= 1) {
        next = func_ov022_020a35f4(self, 0x22);
    }
    return next;
}
