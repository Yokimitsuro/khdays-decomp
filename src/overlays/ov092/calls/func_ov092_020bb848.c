/*
 * Idle step: the per-frame body of the ov036 enemy's idle/pattern state (modes 0x21/0x23; the
 * charge proper at mode 0x22 is 020b46e8).
 *
 * Marks bit 16 of both 64-bit flag words for the local player. With a target angle at +0x2abc
 * it turns towards it (clamped by 020ad4e8 from the +0x478 offset), writes the heading into the
 * model node unless its bit 5 is set, and builds the step from the sin/cos table scaled by the
 * rig's +0x130 speed; a grounded actor without bit 2 of +0x24 gets its +0x58 fall set to 0, or
 * to -0xd6 / -0x8f (by 02023c40) when bit 36 of the flags is clear. The horizontal step goes
 * into +0x498. A busy +0x22f8 channel raises the rig's +0 flag. With no pattern pending (+0xc)
 * it decides whether to attack: a puppet actor (bit 16 clear) fires on +0x1c modes 5/6, the real
 * one on every 0x3000 of +0x4cc from the first on, in phase 2 (+0x14) and with a 70 % roll; a hit
 * in phase 2 stores pattern 2, spawns effect 0xcc at the sampled anchor, fires the spread
 * (020b400c) and advances the +0x10 counter to 5 (falling back to 4 once the channel flag is
 * down); otherwise pattern 1. Bit 1 of +0x18 raises the +4 latch; the state callback lands in
 * bit 1 of +0x694, forced when the counter is at 5 with the channel flag and pattern 2. A set
 * bit 1 then hands over: a raised latch or an idle channel clears the velocities, sets bit 2 and
 * goes to state 0 (with the slot callback) or 2; otherwise below counter 5 or with the channel
 * done the model is rewound to 0 and the state stays, else state 0x22 follows.
 */
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;
typedef struct { int x, y, z; } Vec3;
typedef unsigned short u16;

extern int func_02030788(void);
extern int func_ov022_020ad4e8(char *self, unsigned int angle);            /* Ov022_ClampAngleTowardTarget */
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);         /* ScaleVec3Fx12 */
extern int func_02023c40(void);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov022_02095554(char *chan);
extern int func_0203084c(void);
extern void func_ov022_020ad44c(Vec3 *emit, char *self);
extern void func_ov022_020ad28c(char *self, Vec3 *at, int effect, int arg);
extern void func_ov092_020bb5ac(char *self);
extern int func_ov022_02095524(char *chan);
extern void *func_ov022_020a35f4(char *self, int state);
extern void func_01fff774(char *anim, int track, int frame);
extern char *data_ov092_020bc4e0;
extern short data_0203d210[];

void *func_ov092_020bb848(char *self)
{
    Vec3 sample;
    Vec3 at;
    Vec3 emit;
    Vec3 step;
    char *rig = data_ov092_020bc4e0 + 0x194 + 0x2c00;
    void *next = 0;
    int fire;
    int a;
    int v;
    int t;
    int r;
    unsigned int *node;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    sample.z = 0;
    sample.y = 0;
    sample.x = 0;
    if (*(int *)(self + 0x2000 + 0xabc) != -1) {
        a = func_ov022_020ad4e8(self, (u16)(*(int *)(self + 0x2000 + 0xabc) + *(short *)(self + 0x400 + 0x78)));
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            *(u16 *)((char *)node + 0x80) = a + 0x8000;
            *(u16 *)((char *)node + 4) |= 0x20;
        }
        sample.x = -data_0203d210[(a >> 4) * 2];
        sample.z = -data_0203d210[(a >> 4) * 2 + 1];
        sample.y = 0;
        func_01ffa724(*(int *)(rig + 0x130), &sample, &sample);
    }
    if ((*(int *)(self + 0x24) & 4) == 0) {
        v = 0;
        if ((*(unsigned long long *)self & 0x1000000000ULL) == 0) {
            v = (func_02023c40() == 1) ? -0xd6 : -0x8f;
        }
        *(int *)(self + 0x58) = v;
    }
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    if (func_ov022_02095554(self + 0x2f8 + 0x2000) != 0) {
        *(int *)rig = 1;
    }
    if (*(int *)(rig + 0xc) == 0) {
        fire = 0;
        if ((*(int *)self & 0x10000) == 0) {
            if ((u16)(*(u16 *)(self + 0x1c) + 0xfffb) <= 1) {
                fire = 1;
            }
        } else {
            t = *(int *)(self + 0x4cc);
            if (t % 0x3000 == 0 && t >= 0x3000 && *(int *)(rig + 0x14) == 2
                && func_0203084c() * 100 < 0x46000) {
                fire = 1;
            }
        }
        if (fire != 0) {
            if (*(int *)(rig + 0x14) == 2) {
                *(int *)(rig + 0xc) = 2;
                func_ov022_020ad44c(&emit, self);
                at = emit;
                func_ov022_020ad28c(self, &at, 0xcc, 3);
                func_ov092_020bb5ac(self);
                if (*(int *)(rig + 0x10) < 5) {
                    *(int *)(rig + 0x10) += 1;
                } else if (*(int *)rig == 0) {
                    *(int *)(rig + 0x10) = 4;
                }
            } else {
                *(int *)(rig + 0xc) = 1;
            }
        }
    }
    if ((*(u16 *)(self + 0x18) & 2) == 2) {
        *(int *)(rig + 4) = 1;
    }
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (*(int *)(rig + 0x10) >= 5 && *(int *)rig != 0 && *(int *)(rig + 0xc) == 2) {
        ((Flags *)(self + 0x294 + 0x400))->b1 = 1;
    }
    if (((Flags *)(self + 0x694))->b1) {
        if (*(int *)(rig + 4) != 0 || func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
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
            if (*(int *)(rig + 0x10) < 5 || func_ov022_02095554(self + 0x2f8 + 0x2000) == 0) {
                ((Flags *)(self + 0x694))->b1 = 0;
                func_01fff774(*(char **)(self + 0x20) + 4, 0, 0);
                *(int *)(self + 0x7b0) = 0;
                *(unsigned long long *)self |= 0x20000000ULL;
            } else {
                next = func_ov022_020a35f4(self, 0x22);
            }
        }
    }
    return next;
}
