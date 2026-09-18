/*
 * Pursuit step: the per-frame body of the enemy's pursuit state (the ov041 sibling of the
 * approach step at 020b4478).
 *
 * Same skeleton: bit 16 of both 64-bit flag words for the local player, the aim at the target
 * sampler (020ad114/020ad0c0, atan2 of the normalised direction as a u16) written into the model
 * node on every 0x6000 tick unless its bit 5 is set, bit 35 for the local player, the ground
 * sample (falling velocity to +0x58; when grounded without bit 2 of +0x24 the target being live
 * OR bit 36 of the flags sets bit 46 and zeroes +0x58), the horizontal step into +0x498, the
 * rig's +0x660 latch raised by bit 0 of +0x18 and the state callback into bit 1 of +0x694. A
 * raised latch with a finished +0x22f8 channel drops from tick 0x27000 on (020acf14); on ticks
 * 0xc000, 0x18000 and 0x27000 a clear latch ends the state (bit 1) and the latch is reset either
 * way. 020b3a38 then runs the per-tick effects, and the finish/handover tail is the approach
 * step's (chained +0x698 clear in the state-2 arm, bit 16 of +0x46c cleared on handover).
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
extern void func_ov097_020bafd8(char *self);
extern int func_ov022_02095524(char *chan);
extern void func_ov022_020acf14(char *self, int a);
extern void func_0202af1c(void *node);
extern void *func_ov022_020a35f4(char *self, int state);

void *func_ov097_020bbdc0(char *self)
{
    int r;
    Vec3 sample;
    Vec3 dir;
    Vec3 step;
    void *next = 0;
    char *rig = self + 0x84 + 0x2c00;
    int angle = -1;
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
    } else if ((*(int *)(self + 0x24) & 4) == 0) {
        if (func_ov022_020ad114(self) != 0 || (*(unsigned long long *)self & 0x1000000000ULL) != 0) {
            *(unsigned long long *)self |= 0x400000000000ULL;
            *(int *)(self + 0x58) = 0;
        }
    }
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    if ((*(u16 *)(self + 0x18) & 1) != 0) {
        *(int *)(rig + 0x660) = 1;
    }
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (*(int *)(rig + 0x660) != 0 && func_ov022_02095524(self + 0x2f8 + 0x2000) != 0
        && *(int *)(self + 0x7b0) >= 0x27000) {
        *(int *)(rig + 0x660) = 0;
        func_ov022_020acf14(self, 0);
    }
    if (*(int *)(self + 0x7b0) == 0xc000 || *(int *)(self + 0x7b0) == 0x18000
        || *(int *)(self + 0x7b0) == 0x27000) {
        if (*(int *)(rig + 0x660) == 0) {
            ((Flags *)(self + 0x694))->b1 = 1;
        }
        *(int *)(rig + 0x660) = 0;
    }
    func_ov097_020bafd8(self);
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
