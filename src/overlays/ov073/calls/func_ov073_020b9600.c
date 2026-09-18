/* Dive step of the ov034 enemy (x4: ov034/052/072/090): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16, the shared sampler's motion is folded into the position
 * at +0x498 on the ground plane, the third-count burst is tried and the actor's hook decides bit
 * 1 of +0x694. The dive ends (rig +0x2ce8) when the target is within 0x800 vertically, or
 * without a target once the cached height (+0x2d00) is 0x3000 above the enemy, or when the
 * +0x4cc counter passes 0x3c000 or the enemy touches the ground; the first ending arms the
 * +0x47a/+0x47b pair, drops bit 49, hides the node, clears the vertical speed and raises bit
 * 29 (latched at +0x2cec). While still diving from 0x12000 on the +0x7b0 timer the node is shown
 * again. Becoming active shows the node and, for the local player, sets bit 1 of +0x464; once
 * that bit is set the enemy hands over to state 0x21 while the emitter at +0x22f8 is busy,
 * otherwise to state 0x25. */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef struct { int x, y, z; } Vec3;

extern int func_02030788(void);
extern int func_ov022_0209fe20(char *self, void *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov073_020b9e18(char *self);
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void func_0202af1c(void *node);                                          /* SceneNode_Enable */
extern void func_0202af2c(void *node);                                          /* SceneNode_Disable */
extern int func_ov022_02095524(char *emitter);
extern void *func_ov022_020a35f4(char *self, int state);
extern char *data_ov073_020ba540;

void *func_ov073_020b9600(char *self)
{
    int r;
    Vec3 sample;
    Vec3 step;
    void *next = 0;
    char *rig = data_ov073_020ba540 + 0xe4 + 0x2c00;
    unsigned int *node;
    int dy;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    func_ov022_0209fe20(self, &sample);
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    func_ov073_020b9e18(self);
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (func_ov022_020ad114(self) != 0) {
        dy = func_ov022_020ad0c0(self)->y - *(int *)(self + 0x490);
        if (dy < 0) {
            dy = -dy;
        }
        if (dy < 0x800) {
            *(int *)(rig + 4) = 1;
        }
    } else if (*(int *)(rig + 0x1c) >= *(int *)(self + 0x490) + 0x3000) {
        *(int *)(rig + 4) = 1;
    }
    if (*(int *)(self + 0x4cc) > 0x3c000 || (*(int *)(self + 0x24) & 4) != 0) {
        *(int *)(rig + 4) = 1;
    }
    if (*(int *)(rig + 4) != 0 && *(int *)(rig + 8) == 0) {
        if ((*(unsigned int *)self & 0x10000) == 0) {
            *(unsigned char *)(self + 0x47a) = 3;
            *(unsigned char *)(self + 0x47b) = 1;
        }
        *(int *)(rig + 8) = 1;
        *(unsigned long long *)self &= ~0x2000000000000ULL;
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            func_0202af2c(node + 1);
        }
        *(int *)(self + 0x58) = 0;
        *(unsigned long long *)self |= 0x20000000;
    }
    if ((*(int *)(self + 0x24) & 4) == 0 && *(int *)(self + 0x4cc) <= 0x3c000
        && *(int *)(self + 0x7b0) >= 0x12000 && *(int *)(rig + 4) == 0) {
        *(unsigned long long *)self |= 0x2000000000000ULL;
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            func_0202af1c(node + 1);
        }
    }
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
