/* Attack-phase step of the ov034 enemy (x4: ov034/052/072/090): on the local player both 64-bit
 * flag words at +0x464 and +0x46c get bit 16, the shared sampler's motion is folded into the
 * position at +0x498 on the ground plane (raising bit 46 and clearing the vertical speed unless
 * bit 2 of +0x24 says the enemy is grounded), the heavy burst is tried, and the actor's own hook
 * decides bit 1 of +0x694: becoming active raises bit 49, shows the node and, for the local
 * player, sets bit 1 of +0x464. Once that bit is set the enemy hands over to state 0x21 while
 * the emitter at +0x22f8 is busy, otherwise to state 0x25. */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef struct { int x, y, z; } Vec3;

extern int func_02030788(void);
extern int func_ov022_0209fe20(char *self, void *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov034_020b4d7c(char *self);
extern void func_0202af1c(void *node);
extern int func_ov022_02095524(char *emitter);
extern void *func_ov022_020a35f4(char *self, int state);

void *func_ov034_020b424c(char *self)
{
    int r;
    Vec3 sample;
    Vec3 step;
    void *next = 0;
    unsigned int *node;

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
    func_ov034_020b4d7c(self);
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
    if ((*(unsigned long long *)(self + 0x464) & 2) != 0) {
        if (func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
            next = func_ov022_020a35f4(self, 0x25);
        } else {
            next = func_ov022_020a35f4(self, 0x21);
        }
    }
    return next;
}
