/*
 * Idle step: the per-frame body of the enemy's idle/guard state.
 *
 * Marks bit 16 of both 64-bit flag words for the local player, then, with a zero ground sample,
 * runs the grounded bookkeeping (clear bit 7 of +0x24, set bit 46, zero +0x58) unless bit 2 of
 * +0x24 is set, adds the (zero) horizontal step to +0x498 and runs the state callback twice --
 * the second result lands in bit 1 of +0x694. With the rig's latch (+8) and pending pattern
 * (+0x14) both clear and the tick at 0x9000 or later, it decides whether to attack: a puppet
 * actor (bit 16 clear) fires when its +0x1c mode is 5 or 6; the real one, on every 0x1e000 of
 * its +0x4cc timer from the first one on, rolls against 70 % for band counts 1..2 and 20 %
 * otherwise. A hit stores the band count as the pending pattern, pushes the attack events and
 * effect 0xcd at +0x48c, and rewinds the model to 0x27000 (pattern 3: 0x1e000) with bit 29.
 * Bit 1 of +0x18 without a pending pattern raises the latch. The tail then hands over: a raised
 * latch, a finished pattern 3, or an idle +0x22f8 channel with no pattern goes to state 0x23
 * (pattern 3) or clears the velocities, sets bit 2, queues action 8 for the real actor and hands
 * over to state 0 (with the slot callback) or 2; otherwise a finished state goes to 0x22 for a
 * pending pattern (other than 3) or rewinds the model to 0x9000 and stays.
 */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef struct { int x, y, z; } Vec3;
typedef unsigned short u16;
typedef unsigned char u8;

extern int func_02030788(void);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov095_020bbbc8(char *self);
extern int func_0203084c(void);
extern void func_ov095_020bbc50(char *self);
extern void func_ov022_020ad28c(char *self, char *at, int effect, int arg);
extern void func_01fff774(char *anim, int track, int frame);
extern int func_ov022_02095524(char *emitter);
extern void *func_ov022_020a35f4(char *self, int state);
extern char *data_ov095_020bcba0;

void *func_ov095_020bc0c0(char *self)
{
    int r;
    Vec3 sample;
    Vec3 step;
    char *rig = data_ov095_020bcba0 + 0xd4 + 0x2c00;
    void *next = 0;
    int fire;
    int n;
    int t;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    sample.z = 0;
    sample.y = 0;
    sample.x = 0;
    if ((*(int *)(self + 0x24) & 4) == 0) {
        *(int *)(self + 0x24) &= ~0x80;
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    (*(int (**)(char *))(self + 0x668))(self);
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (*(int *)(rig + 8) == 0 && *(int *)(rig + 0x14) == 0 && *(int *)(self + 0x7b0) >= 0x9000) {
        fire = 0;
        if ((*(int *)self & 0x10000) == 0) {
            if ((u16)(*(u16 *)(self + 0x1c) + 0xfffb) <= 1) {
                fire = 1;
            }
        } else {
            n = func_ov095_020bbbc8(self);
            t = *(int *)(self + 0x4cc);
            if (t % 0x1e000 == 0 && t >= 0x1e000) {
                if ((unsigned int)(n - 1) <= 1) {
                    if (func_0203084c() * 100 < 0x46000) {
                        fire = 1;
                    }
                } else {
                    if (func_0203084c() * 100 < 0x14000) {
                        fire = 1;
                    }
                }
            }
        }
        if (fire != 0) {
            *(int *)(rig + 0x14) = func_ov095_020bbbc8(self);
            func_ov095_020bbc50(self);
            func_ov022_020ad28c(self, self + 0x8c + 0x400, 0xcd, 0);
            if (*(int *)(rig + 0x14) != 3) {
                func_01fff774(*(char **)(self + 0x20) + 4, 0, 0x27000);
                *(unsigned long long *)self |= 0x20000000ULL;
            } else {
                func_01fff774(*(char **)(self + 0x20) + 4, 0, 0x1e000);
                *(unsigned long long *)self |= 0x20000000ULL;
            }
        }
    }
    if ((*(u16 *)(self + 0x18) & 2) == 2 && *(int *)(rig + 0x14) == 0) {
        *(int *)(rig + 8) = 1;
    }
    if (*(int *)(rig + 8) != 0 || (*(int *)(rig + 0x14) == 3 && ((Flags *)(self + 0x694))->b1)
        || (func_ov022_02095524(self + 0x2f8 + 0x2000) == 0 && *(int *)(rig + 0x14) == 0)) {
        if (*(int *)(rig + 0x14) == 3) {
            next = func_ov022_020a35f4(self, 0x23);
        } else {
            *(int *)(self + 0x4a0) = 0;
            *(int *)(self + 0x49c) = 0;
            *(int *)(self + 0x498) = 0;
            *(int *)(self + 0x6a0) = 0;
            *(int *)(self + 0x69c) = 0;
            *(int *)(self + 0x698) = 0;
            *(unsigned long long *)self |= 4;
            if ((*(int *)self & 0x10000) == 0) {
                *(u8 *)(self + 0x47a) = 8;
            }
            if ((*(int *)(self + 0x24) & 4) != 0) {
                (*(void (**)(char *, int))(self + 0x664))(self, 0);
                next = func_ov022_020a35f4(self, 0);
            } else {
                next = func_ov022_020a35f4(self, 2);
            }
        }
    } else {
        if (((Flags *)(self + 0x694))->b1) {
            if (*(int *)(rig + 0x14) != 0 && *(int *)(rig + 0x14) != 3) {
                next = func_ov022_020a35f4(self, 0x22);
            } else {
                ((Flags *)(self + 0x694))->b1 = 0;
                func_01fff774(*(char **)(self + 0x20) + 4, 0, 0x9000);
                *(int *)(self + 0x7b0) = 0x9000;
                *(unsigned long long *)self |= 0x20000000ULL;
            }
        }
    }
    return next;
}
