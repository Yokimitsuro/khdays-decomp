/* Landing step of the ov046 enemy (x4: ov046/065/084/101): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16, the shared sampler's motion is folded into the position
 * at +0x498 (a vertical component becomes the vertical speed, otherwise -- unless bit 2 of +0x24
 * says the enemy is grounded -- bit 46 is raised and the speed cleared), and the actor's own hook
 * decides bit 1 of +0x694: becoming active raises bit 49, shows the node and, for the local
 * player, sets bit 1 of +0x464. Before that, once the +0x7b0 timer reaches 0xc000 (0x18000 with
 * the rig's alternate flag) the ground shot fires once, latched at +0x2d98. While active the
 * velocities at +0x498 and +0x698 are cleared and the enemy hands over to state 2, or, when
 * grounded, tells the slot callback 0 and hands over to state 0. */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef struct { int x, y, z; } Vec3;

extern int func_02030788(void);
extern int func_ov022_0209fe20(char *self, void *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0202af1c(void *node);
extern void *func_ov022_020a35f4(char *self, int state);
extern void func_ov046_020b3e88(char *self);
extern char *data_ov046_020b4b40;

void *func_ov046_020b4824(char *self)
{
    int r;
    Vec3 sample;
    Vec3 step;
    char *rig = data_ov046_020b4b40 + 0x2c80;
    void *next = 0;
    unsigned int *node;
    int limit;

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
    limit = *(int *)rig != 0 ? 0x18000 : 0xc000;
    if (*(int *)(self + 0x7b0) >= limit && *(int *)(rig + 0x118) == 0) {
        func_ov046_020b3e88(self);
        *(int *)(rig + 0x118) = 1;
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
        if ((*(int *)(self + 0x24) & 4) != 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0);
            next = func_ov022_020a35f4(self, 0);
        } else {
            next = func_ov022_020a35f4(self, 2);
        }
    }
    return next;
}
