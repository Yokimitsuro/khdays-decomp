/*
 * Charge step: the per-frame body of the ov039 enemy's charge state.
 *
 * Marks bit 16 of both 64-bit flag words for the local player. With the rig's pose latch
 * (+0xc) raised, the 0x3000 tick of +0x4cc drops bit 49, disables the model node (unless its
 * bit 5 is set) and clears the latch. The ground sample then drives the fall: a hit clears
 * bit 7 of +0x24 and stores the velocity in +0x58, otherwise without bit 2 of +0x24 the same
 * bit 7 is cleared, bit 46 raised and +0x58 zeroed; the horizontal step goes into +0x498. From
 * tick 0x6000 (0xf000 in the rig's alternate mode) with the shot latch (+4) clear the pursuit
 * (020b4820) runs once and the latch is raised. The state callback lands in bit 1 of +0x694; a
 * set bit 1 finishes the pose (bit 49, node reset unless bit 5, bit 1 of +0x464 for the local
 * player), clears the velocities, sets bit 2 and hands over to state 0 (after the slot
 * callback) or 2.
 */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef struct { int x, y, z; } Vec3;

extern int func_02030788(void);
extern void func_0202af2c(void *node);                                          /* SceneNode_Disable */
extern int func_ov022_0209fe20(char *self, void *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov039_020b4820(char *self);
extern void func_0202af1c(void *node);
extern void *func_ov022_020a35f4(char *self, int state);
extern char *data_ov039_020b5600;

void *func_ov039_020b4f0c(char *self)
{
    int r;
    Vec3 sample;
    Vec3 step;
    char *rig = data_ov039_020b5600 + 0xd4 + 0x2c00;
    void *next = 0;
    int limit;
    unsigned int *node;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    if (*(int *)(rig + 0xc) != 0 && *(int *)(self + 0x4cc) == 0x3000) {
        *(unsigned long long *)self &= ~0x2000000000000ULL;
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            func_0202af2c(node + 1);
        }
        *(int *)(rig + 0xc) = 0;
    }
    func_ov022_0209fe20(self, &sample);
    if (sample.y != 0) {
        *(int *)(self + 0x24) &= ~0x80;
        *(int *)(self + 0x58) = sample.y;
    } else if ((*(int *)(self + 0x24) & 4) == 0) {
        *(int *)(self + 0x24) &= ~0x80;
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    limit = *(int *)rig != 0 ? 0xf000 : 0x6000;
    if (*(int *)(self + 0x7b0) >= limit && *(int *)(rig + 4) == 0) {
        func_ov039_020b4820(self);
        *(int *)(rig + 4) = 1;
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
