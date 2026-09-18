/* Pursuit step of the ov040 enemy (x4: ov040/059/079/096): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16; while flag bit 33 is set the enemy chases at the rig's
 * speed (+0x2d70): without a target it flies straight ahead at half speed, with one it turns to
 * face it (unless the facing is locked) and closes at most the remaining distance, stopping
 * within 0x1800; the vertical part of the step becomes the vertical speed; without bit 33 an
 * airborne enemy raises bit 46 and clears the speed. Past 0x18000 on the +0x4cc counter, or once
 * in range, it hands over to state 0x22. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_02030788(void);
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern int FX_Atan2(int x, int z);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);         /* ScaleVec3Fx12 */
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void *func_ov022_020a35f4(char *self, int state);
extern char *data_ov096_020bc0c0;
extern short data_0203d210[];

void *func_ov096_020bbd0c(char *self)
{
    Vec3 d;
    Vec3 step;
    Vec3 flat;
    int speed = *(int *)(data_ov096_020bc0c0 + 0x2d70);
    int bClose = 0;
    void *next = 0;
    int dist;
    int idx;
    u16 a;
    unsigned int *node;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    step.z = 0;
    step.y = 0;
    step.x = 0;
    d.z = 0;
    d.y = 0;
    d.x = 0;
    if ((*(unsigned long long *)(self + 0x464) & 0x200000000ULL) != 0) {
        *(int *)(self + 0x4b4) = 0x2000;
        if (func_ov022_020ad114(self) == 0) {
            idx = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000) >> 4;
            speed = speed / 2;
            step.x = -data_0203d210[idx * 2];
            step.y = 0;
            step.z = -data_0203d210[idx * 2 + 1];
        } else {
            VEC_Subtract(func_ov022_020ad0c0(self), (Vec3 *)(self + 0x8c + 0x400), &d);
            dist = VEC_Mag(&d);
            if (dist >= 0x1800) {
                a = (u16)FX_Atan2(-d.x, -d.z);
                node = *(unsigned int **)(self + 0x20);
                if ((*node & 0x20) == 0) {
                    *(u16 *)((char *)node + 0x80) = a + 0x8000;
                    *(u16 *)((char *)node + 4) |= 0x20;
                }
                if (dist < speed) {
                    speed = VEC_Mag(&d);
                }
                if (VEC_Mag(&d) == 0) {
                    step = d;
                } else {
                    func_01ff8d18(&d, &step);
                }
            } else {
                speed = 0;
                bClose = 1;
            }
        }
        func_01ffa724(speed, &step, &step);
        if (step.y != 0) {
            *(int *)(self + 0x58) = step.y;
        }
    } else if ((*(int *)(self + 0x24) & 4) == 0) {
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    flat = step;
    flat.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &flat, (Vec3 *)(self + 0x98 + 0x400));
    if (*(int *)(self + 0x4cc) >= 0x18000 || bClose != 0) {
        next = func_ov022_020a35f4(self, 0x22);
    }
    return next;
}
