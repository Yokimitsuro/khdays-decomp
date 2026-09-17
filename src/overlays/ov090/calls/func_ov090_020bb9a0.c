/* Per-frame step of the ov034 enemy (x4: ov034/052/072/090): on the local player both 64-bit
 * flag words at +0x464 and +0x46c get bit 16, the shared sampler's motion is folded into the
 * position at +0x498 on the ground plane (and, unless bit 2 of +0x24 says the enemy is
 * grounded, bit 46 of the actor flags is raised and the vertical speed cleared), the actor's own
 * hook decides bit 1 of +0x694, and past 0xb000 on the +0x7b0 timer the enemy hands over to
 * state 0x23. */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef struct { int x, y, z; } Vec3;

extern int func_02030788(void);
extern int func_ov022_0209fe20(char *self, void *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void *func_ov022_020a35f4(char *self, int state);

void *func_ov090_020bb9a0(char *self)
{
    int r;
    Vec3 sample;
    Vec3 step;
    void *next = 0;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    func_ov022_0209fe20(self, &sample);
    if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (*(int *)(self + 0x7b0) > 0xb000) {
        next = func_ov022_020a35f4(self, 0x23);
    }
    return next;
}
