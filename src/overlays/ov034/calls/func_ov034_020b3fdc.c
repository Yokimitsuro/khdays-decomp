/* Idle step of the ov034 enemy (x4: ov034/052/072/090): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16; with a cached heading (+0x2abc) the node turns towards
 * it (plus the +0x478 offset, clamped by the turn helper) unless the facing is locked and the
 * enemy moves along it at the rig's speed (+0x2cfc), otherwise it stays; in the air without bit
 * 36 the fall speed is -0x8f (-0xd6 in hard mode); the rapid burst is tried; a quiet emitter at
 * +0x22f8 hands over to state 0x25, otherwise the actor's hook runs and becoming active rewinds
 * the animation, clears the timer and raises bit 29; finally a +0x1c state of 5 or 6 hands over
 * to state 0x22. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

extern int func_02030788(void);
extern int func_ov022_020ad4e8(char *self, unsigned int angle);            /* Ov022_ClampAngleTowardTarget */
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);            /* ScaleVec3Fx12 */
extern int func_02023c40(void);                                            /* game mode: 1 = hard */
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov034_020b4bf8(char *self);
extern int func_ov022_02095524(char *emitter);
extern void *func_ov022_020a35f4(char *self, int state);
extern void func_01fff774(void *animation, int track, int frame);          /* Anim_SetFrameWrapped */
extern char *data_ov034_020b5660;
extern short data_0203d210[];

void *func_ov034_020b3fdc(char *self)
{
    Vec3 step;
    Vec3 flat;
    void *next = 0;
    char *rig = data_ov034_020b5660 + 0xe4 + 0x2c00;
    int a;
    int v;
    unsigned int *node;
    int r;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    if (*(int *)(self + 0x2abc) != -1) {
        a = func_ov022_020ad4e8(self, (u16)(*(int *)(self + 0x2abc) + *(short *)(self + 0x478)));
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            *(u16 *)((char *)node + 0x80) = a + 0x8000;
            *(u16 *)((char *)node + 4) |= 0x20;
        }
        step.x = -data_0203d210[(a >> 4) * 2];
        step.z = -data_0203d210[(a >> 4) * 2 + 1];
        step.y = 0;
        func_01ffa724(*(int *)(rig + 0x18), &step, &step);
    } else {
        step.z = 0;
        step.y = 0;
        step.x = 0;
    }
    if ((*(int *)(self + 0x24) & 4) == 0) {
        v = 0;
        if ((*(unsigned long long *)self & 0x1000000000ULL) == 0) {
            v = func_02023c40() == 1 ? -0xd6 : -0x8f;
        }
        *(int *)(self + 0x58) = v;
    }
    flat = step;
    flat.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &flat, (Vec3 *)(self + 0x98 + 0x400));
    func_ov034_020b4bf8(self);
    if (func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
        next = func_ov022_020a35f4(self, 0x25);
    }
    if (next == 0) {
        r = (*(int (**)(char *))(self + 0x668))(self);
        ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
        if (((Flags *)(self + 0x694))->b1) {
            func_01fff774(*(char **)(self + 0x20) + 4, 0, 0);
            *(int *)(self + 0x7b0) = 0;
            *(unsigned long long *)self |= 0x20000000;
        }
    }
    if (next == 0 && (u16)(*(u16 *)(self + 0x1c) + 0xfffb) <= 1) {
        next = func_ov022_020a35f4(self, 0x22);
    }
    return next;
}
