/*
 * Approach step: the per-frame body of the ov037 enemy's approach state.
 *
 * Marks bit 16 of both 64-bit flag words (+0x464/+0x46c) for the local player; when the target
 * sampler is live (020ad114) aims at it -- the normalised target-to-anchor direction's atan2,
 * kept as a u16 -- and on every 0x6000 tick writes that heading (+0x8000) into the model node
 * unless its bit 5 is set. Then bit 35 for the local player, the ground sample (falling
 * velocity to +0x58), the horizontal step added to +0x498, the rig's +0x110 latch raised by
 * bit 0 of +0x18 and the state callback into bit 1 of +0x694. From tick 0x27000 on, a raised
 * latch waits for the +0x22f8 channel: while it is busy the state ends (bit 1) -- a finished
 * channel also marks `done` -- and once idle 020acf14 re-arms it at 0x3000. On ticks 0xc000,
 * 0x18000, 0x24000 and 0x27000 a clear latch ends the state and marks it done, and the latch is
 * reset either way. The timed volley (020b46fc) fires, a set bit 1 finishes the pose (bit 49,
 * node reset unless bit 5, bit 1 of +0x464 for the local player), and bit 1 of +0x464 hands
 * over: before tick 0x27000, with an idle channel or when done, the velocities are cleared, bit
 * 2 set and state 0 (with the slot callback) or 2 follows; otherwise bit 31 of +0x464 is set for
 * the local player and state 0x22 follows.
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
extern int func_ov022_02095554(char *chan);
extern int func_ov022_02095524(char *chan);
extern void func_ov022_020acf14(char *self, int a);
extern void func_ov056_020b6efc(char *self);
extern void func_0202af1c(void *node);
extern void *func_ov022_020a35f4(char *self, int state);
extern char *data_ov056_020b7620;

void *func_ov056_020b6508(char *self)
{
    int r;
    Vec3 sample;
    Vec3 dir;
    Vec3 step;
    void *next = 0;
    char *rig = data_ov056_020b7620 + 0x2c + 0x2c00;
    int done = 0;
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
    if (*(int *)(self + 0x7b0) % 0x6000 == 0 && angle != -1) {
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
    }
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    if ((*(u16 *)(self + 0x18) & 1) != 0) {
        *(int *)(rig + 0x110) = 1;
    }
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (*(int *)(rig + 0x110) != 0 && *(int *)(self + 0x7b0) >= 0x27000) {
        ok = 1;
        if (func_ov022_02095554(self + 0x2f8 + 0x2000) != 0) {
            ok = 0;
        }
        if (func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
            ok = 0;
            done = 1;
        }
        if (ok != 0) {
            func_ov022_020acf14(self, 0x3000);
        } else {
            ((Flags *)(self + 0x694))->b1 = 1;
        }
    }
    switch (*(int *)(self + 0x7b0)) {
    case 0xc000:
    case 0x18000:
    case 0x24000:
    case 0x27000:
        if (*(int *)(rig + 0x110) == 0) {
            done = 1;
            ((Flags *)(self + 0x694))->b1 = 1;
        }
        *(int *)(rig + 0x110) = 0;
        break;
    }
    func_ov056_020b6efc(self);
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
        if (*(int *)(self + 0x7b0) < 0x27000 || func_ov022_02095524(self + 0x2f8 + 0x2000) == 0
            || done != 0) {
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
                next = func_ov022_020a35f4(self, 2);
            }
        } else {
            if (func_02030788() == 0) {
                *(unsigned long long *)(self + 0x464) |= 0x80000000ULL;
            }
            next = func_ov022_020a35f4(self, 0x22);
        }
    }
    return next;
}
