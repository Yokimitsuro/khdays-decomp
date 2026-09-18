/* Descent step of the ov049 enemy (x4: ov049/068/087/104): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16, the shared sampler's motion is folded into the position
 * at +0x498 (a vertical component becomes the vertical speed, otherwise -- unless grounded --
 * bit 46 is raised and the speed cleared; either way bit 7 of +0x24 is dropped), the actor's own
 * hook runs, a hit flag (bit 1 of +0x18) latches the rig's +0x2e18 marker, and once the +0x7b0
 * timer is within 0xc000 of the animation's end the enemy hands over: to state 0x23 without the
 * marker, otherwise it stops, raises bit 2 and goes to state 2 (or tells the slot callback and
 * goes to state 0 when grounded). */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_02030788(void);
extern int func_ov022_0209fe20(char *self, void *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_0202aef8(void *animation, int track);                 /* Anim_GetLengthQ12 */
extern void *func_ov022_020a35f4(char *self, int state);
extern char *data_ov104_020bc2a0;

void *func_ov104_020bbba0(char *self)
{
    Vec3 sample;
    Vec3 step;
    void *next = 0;
    char *rig = data_ov104_020bc2a0 + 0xfc + 0x2c00;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
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
    (*(int (**)(char *))(self + 0x668))(self);
    if ((*(u16 *)(self + 0x18) & 2) == 2) {
        *(int *)(rig + 0x11c) = 1;
    }
    if (*(int *)(self + 0x7b0) >= func_0202aef8(*(char **)(self + 0x20) + 4, 0) - 0xc000) {
        if (*(int *)(rig + 0x11c) == 0) {
            next = func_ov022_020a35f4(self, 0x23);
        } else {
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
                *(int *)(self + 0x58) = 0;
                next = func_ov022_020a35f4(self, 2);
            }
        }
    }
    return next;
}
