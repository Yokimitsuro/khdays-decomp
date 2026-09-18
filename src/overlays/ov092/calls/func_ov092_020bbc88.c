/* Charge step of the ov036 enemy (x4: ov036/054/074/091): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16; with a cached heading (+0x2abc) the node turns towards
 * it (plus the +0x478 offset, clamped by the turn helper) unless the facing is locked and the
 * enemy moves along it at the rig's speed (+0x2ec4); in the air bit 46 is raised and the
 * vertical speed cleared; the actor's hook decides bit 1 of +0x694; from 0xc000 on the +0x7b0
 * timer the bone effect spawns once (latched at +0x2d9c), a hit (bit 1 of +0x18) latches the
 * rig's +0x2d98 marker, and an active enemy either hands over to state 0x23 (busy emitter and no
 * marker) or stops, raises bit 2 and lands: state 0 with the slot callback when grounded, else
 * state 2. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

extern int func_02030788(void);
extern int func_ov022_020ad4e8(char *self, unsigned int angle);            /* Ov022_ClampAngleTowardTarget */
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);            /* ScaleVec3Fx12 */
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov092_020bb788(char *self);
extern int func_ov022_02095524(char *emitter);
extern void *func_ov022_020a35f4(char *self, int state);
extern char *data_ov092_020bc4e0;
extern short data_0203d210[];

void *func_ov092_020bbc88(char *self)
{
    Vec3 step;
    Vec3 flat;
    char *rig = data_ov092_020bc4e0 + 0x194 + 0x2c00;
    void *next = 0;
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
        func_01ffa724(*(int *)(rig + 0x130), &step, &step);
    }
    if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    flat = step;
    flat.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &flat, (Vec3 *)(self + 0x98 + 0x400));
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (*(int *)(rig + 8) == 0 && *(int *)(self + 0x7b0) >= 0xc000) {
        func_ov092_020bb788(self);
        *(int *)(rig + 8) = 1;
    }
    if ((*(u16 *)(self + 0x18) & 2) == 2) {
        *(int *)(rig + 4) = 1;
    }
    if (((Flags *)(self + 0x694))->b1) {
        if (func_ov022_02095524(self + 0x2f8 + 0x2000) == 0 || *(int *)(rig + 4) == 1) {
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
            next = func_ov022_020a35f4(self, 0x23);
        }
    }
    return next;
}
