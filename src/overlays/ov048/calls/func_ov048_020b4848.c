/* Landing step of the ov048 enemy (x4: ov048/067/086/103): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16, the shared sampler's motion is folded into the position
 * at +0x498 (a vertical component becomes the vertical speed, otherwise -- unless bit 2 of +0x24
 * says the enemy is grounded -- bit 46 is raised and the speed cleared), and the actor's own hook
 * decides bit 1 of +0x694: becoming active raises bit 49, shows the node and, for the local
 * player, sets bit 1 of +0x464. While active the velocities at +0x498 and +0x698 are cleared, bit
 * 2 of the actor flags is raised and the enemy hands over to state 2, or, when grounded, tells
 * the slot callback 0 and hands over to state 0. */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef struct { int x, y, z; } Vec3;

extern int func_02030788(void);
extern int func_ov022_0209fe20(char *self, void *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0202af1c(void *node);
extern void *func_ov022_020a35f4(char *self, int state);

void *func_ov048_020b4848(char *self)
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
