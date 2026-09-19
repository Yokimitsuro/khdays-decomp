/* Charge step of the mission enemy: on the local player both 64-bit flag words at +0x464 and
 * +0x46c get bit 16; once the +0x7b0 timer passes 0x9000 and a heading is cached (+0x2abc) the
 * node turns towards it (plus the +0x478 offset, clamped by the turn helper) unless the facing
 * is locked and the enemy moves along it at the owner block's +0xc speed, otherwise it stays;
 * in the air bit 46 is raised and the fall speed cleared. The first time the timer passes
 * 0x9000 both rows fire (5120), the +0x47a/+0x47b pair is armed (3, 3) unless flagged 0x10000
 * and the block's +4 latch set; the attack burst ticks; a quiet emitter at +0x22f8 hands over
 * to state 0x23, otherwise the actor's hook runs and becoming active either hands over to 0x23
 * (quiet emitter) or winds the animation and timer to 0x9000. */
typedef unsigned short u16;
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

extern int func_02030788(void);
extern int func_ov022_020ad4e8(char *self, unsigned int angle);            /* Ov022_ClampAngleTowardTarget */
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);            /* ScaleVec3Fx12 */
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov062_020b7920(char *self);
extern void func_ov062_020b6db8(char *self);
extern int func_ov022_02095524(char *emitter);
extern void *func_ov022_020a35f4(char *self, int state);
extern void func_01fff774(void *animation, int track, int frame);          /* Anim_SetFrameWrapped */
extern char *data_ov062_020b80e0;
extern short data_0203d210[];

void *func_ov062_020b6968(char *self)
{
    Vec3 step;
    Vec3 flat;
    void *next = 0;
    char *pBlock = data_ov062_020b80e0 + 0x138 + 0x2c00;
    int a;
    unsigned int *node;
    int r;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    step.z = 0;
    step.y = 0;
    step.x = 0;
    if (*(int *)(self + 0x7b0) >= 0x9000 && *(int *)(self + 0x2abc) != -1) {
        a = func_ov022_020ad4e8(self, (u16)(*(int *)(self + 0x2abc) + *(short *)(self + 0x478)));
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            *(u16 *)((char *)node + 0x80) = a + 0x8000;
            *(u16 *)((char *)node + 4) |= 0x20;
        }
        step.x = -data_0203d210[(a >> 4) * 2];
        step.z = -data_0203d210[(a >> 4) * 2 + 1];
        step.y = 0;
        func_01ffa724(*(int *)(pBlock + 0xc), &step, &step);
    }
    if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    flat = step;
    flat.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &flat, (Vec3 *)(self + 0x98 + 0x400));
    if (*(int *)(pBlock + 4) == 0 && *(int *)(self + 0x7b0) >= 0x9000) {
        func_ov062_020b7920(self);
        if ((*(int *)self & 0x10000) == 0) {
            *(u8 *)(self + 0x47a) = 3;
            *(u8 *)(self + 0x47b) = 3;
        }
        *(int *)(pBlock + 4) = 1;
    }
    func_ov062_020b6db8(self);
    if (func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
        next = func_ov022_020a35f4(self, 0x23);
    }
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (((Flags *)(self + 0x694))->b1) {
        if (func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
            next = func_ov022_020a35f4(self, 0x23);
        } else {
            func_01fff774(*(char **)(self + 0x20) + 4, 0, 0x9000);
            *(int *)(self + 0x7b0) = 0x9000;
        }
    }
    return next;
}
