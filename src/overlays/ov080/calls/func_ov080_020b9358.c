/*
 * Approach step: the per-frame body of the enemy's approach state.
 *
 * Marks bit 16 of both 64-bit flag words (+0x464/+0x46c) for the local player; when the target
 * sampler is live (020ad114) aims at it -- the normalised target-to-anchor direction's atan2,
 * kept as a u16 -- and on the 0x3000 tick writes that heading (+0x8000) into the model node
 * unless its bit 5 is set. Then the usual movement: bit 35 for the local player, the ground
 * sample (falling velocity to +0x58, or bit 46 and zero when grounded without bit 2 of +0x24),
 * the horizontal step added to +0x498, the volley (020b3888) between ticks 0xc000 and 0x12000,
 * the rig's +0x660 latch raised by bit 0 of +0x18, and the state callback into bit 1 of +0x694.
 * From tick 0x12000 on, a raised latch waits for both sub-channels of +0x22f8 to finish -- while
 * either is busy the state ends (bit 1); once both are done the latch drops and 020a2954 /
 * 020acf14 run. A set bit 1 finishes the pose (bit 49, node reset unless bit 5, bit 1 of +0x464
 * for the local player); bit 1 of +0x464 then clears the velocities, sets bit 2 and hands over
 * to state 0 (with the slot callback) or 2. A handover also clears bit 16 of +0x46c.
 *
 * Two spellings beyond the ov033/037 template: the wait test is `if (ok != 0) {..} else {..}`
 * (the ROM predicates the eq arm first), and the state-2 arm clears the +0x698 velocity AGAIN as
 * one chained assignment `+0x698 = +0x69c = +0x6a0 = 0` -- that is what puts the third store
 * through a copied register (`mov r3,r1`) after the argument moves.
 */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef struct { int x, y, z; } Vec3;
typedef unsigned short u16;

extern int func_02030788(void);
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern void func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int FX_Atan2(int y, int x);
extern int func_ov022_0209fe20(char *self, void *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov080_020b8768(char *self);
extern int func_ov022_02095554(char *chan);
extern int func_ov022_02095524(char *chan);
extern void func_ov022_020a2954(char *self);
extern void func_ov022_020acf14(char *self, int a);
extern void func_0202af1c(void *node);
extern void *func_ov022_020a35f4(char *self, int state);

void *func_ov080_020b9358(char *self)
{
    int r;
    Vec3 sample;
    Vec3 dir;
    Vec3 step;
    void *next = 0;
    char *rig = self + 0x84 + 0x2c00;
    int angle = -1;
    int ok;
    unsigned int *node;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    if (func_ov022_020ad114(self) != 0) {
        VEC_Subtract(func_ov022_020ad0c0(self), (Vec3 *)(self + 0x8c + 0x400), &dir);
        if (VEC_Mag(&dir) != 0) {
            func_01ff8d18(&dir, &dir);
        }
        angle = (u16)FX_Atan2(-dir.x, -dir.z);
    }
    if (*(int *)(self + 0x7b0) == 0x3000 && angle != -1) {
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            *(u16 *)((char *)node + 0x80) = angle + 0x8000;
            *(u16 *)((char *)node + 4) |= 0x20;
        }
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x800000000ULL;
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
    if (*(int *)(self + 0x7b0) >= 0xc000 && *(int *)(self + 0x7b0) <= 0x12000) {
        func_ov080_020b8768(self);
    }
    if ((*(u16 *)(self + 0x18) & 1) != 0) {
        *(int *)(rig + 0x660) = 1;
    }
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (*(int *)(rig + 0x660) != 0 && *(int *)(self + 0x7b0) >= 0x12000) {
        ok = 1;
        if (func_ov022_02095554(self + 0x2f8 + 0x2000) != 0) {
            ok = 0;
        }
        if (func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
            ok = 0;
        }
        if (ok != 0) {
            *(int *)(rig + 0x660) = 0;
            func_ov022_020a2954(self);
            func_ov022_020acf14(self, 0);
        } else {
            ((Flags *)(self + 0x694))->b1 = 1;
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
        *(int *)(self + 0x4a0) = 0;
        *(int *)(self + 0x49c) = 0;
        *(int *)(self + 0x498) = 0;
        *(int *)(self + 0x6a0) = 0;
        *(int *)(self + 0x69c) = 0;
        *(int *)(self + 0x698) = 0;
        *(unsigned long long *)self |= 4;
        if ((*(int *)(self + 0x24) & 4) != 0) {
            next = func_ov022_020a35f4(self, 0);
            (*(void (**)(char *, int))(self + 0x664))(self, 0);
        } else {
            *(int *)(self + 0x698) = *(int *)(self + 0x69c) = *(int *)(self + 0x6a0) = 0;
            next = func_ov022_020a35f4(self, 2);
        }
    }
    if (next != 0) {
        *(unsigned long long *)(self + 0x46c) &= ~0x10000ULL;
    }
    return next;
}
