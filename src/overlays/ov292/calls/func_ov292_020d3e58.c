/* Per-frame steering step for the ov292 actor's sub-state.
 *
 * Faces the target, builds the rotation from the flat heading, and works out a
 * speed: a base of 0x780 reduced in proportion to the hit points still left,
 * scaled by how squarely the actor already faces the target (the dot product,
 * doubled and clamped into [0x200, 0x1000]), scaled again by the stored
 * throttle and floored at 0x3c0. The throttle then ramps up by 0xc0 a frame,
 * clamped into [0, 0x1000].
 *
 * When the owner has a lap count it also checks arrival: once the flat distance
 * to the target drops below the speed, the step zeroes the velocity, advances
 * the point index modulo the lap count, and walks the point list to the new
 * index. */
typedef unsigned long long u64;

struct Vec3 { int x, y, z; };

extern void VEC_Subtract(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *out);
extern int func_01ff8d18(const struct Vec3 *src, struct Vec3 *dst);
extern int func_020050b4(int x, int z);
extern void func_0202f188(void *quat, const struct Vec3 *axis, int angle);
extern void func_0202f384(struct Vec3 *out, void *mtx, const struct Vec3 *v);
extern long long func_02020400(int num, int den);
extern int VEC_DotProduct(const struct Vec3 *a, const struct Vec3 *b);
extern void func_01ffa724(int scale, const struct Vec3 *v, struct Vec3 *out);
extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);

extern const struct Vec3 data_02042264;
extern const struct Vec3 data_02042258;

void func_ov292_020d3e58(char *state)
{
    struct Vec3 vToTarget;
    struct Vec3 vFacing;
    struct Vec3 vFlat;
    char *actor;
    int nSpeed;
    int nAim;
    int i;
    struct Vec3 *point;

    actor = *(char **)state;
    VEC_Subtract((struct Vec3 *)(state + 0x1c), *(struct Vec3 **)(state + 8),
                 &vToTarget);
    func_01ff8d18(&vToTarget, &vToTarget);
    func_0202f188(state + 0x48, &data_02042264,
                  func_020050b4(vToTarget.x, vToTarget.z));
    func_0202f384(&vFacing, *(char **)state + 0xa0, &data_02042258);

    nSpeed = 0x780;
    if (*(short *)(actor + 0x218) != 0) {
        nSpeed = nSpeed - (int)func_02020400(*(short *)(actor + 0x21a) * 0x500,
                                             *(short *)(actor + 0x218));
    }

    nAim = VEC_DotProduct(&vToTarget, &vFacing) * 2;
    if (nAim > 0x1000) {
        nAim = 0x1000;
    } else if (nAim < 0x200) {
        nAim = 0x200;
    }
    nSpeed = (int)(((long long)nSpeed * nAim + 0x800) >> 12);
    nSpeed = (int)(((long long)nSpeed * *(int *)(state + 0x30) + 0x800) >> 12);
    if (nSpeed < 0x3c0) {
        nSpeed = 0x3c0;
    }
    func_01ffa724(nSpeed, &vToTarget, (struct Vec3 *)(state + 0x10));

    nAim = *(int *)(state + 0x30) + 0xc0;
    if (nAim > 0x1000) {
        nAim = 0x1000;
    } else if (nAim < 0) {
        nAim = 0;
    }
    *(int *)(state + 0x30) = nAim;

    if (*(int *)(*(char **)state + 0x3b4) == 0) {
        return;
    }

    VEC_Subtract((struct Vec3 *)(state + 0x1c), *(struct Vec3 **)(state + 8),
                 &vFlat);
    vFlat.y = 0;
    if (func_01ff8d18(&vFlat, &vFlat) >= nSpeed) {
        return;
    }

    VEC_Subtract((struct Vec3 *)(state + 0x1c), *(struct Vec3 **)(state + 8),
                 (struct Vec3 *)(state + 0x10));
    *(int *)(state + 0x34) = (int)((u64)func_02020400(*(int *)(state + 0x34) + 1,
                                                      *(int *)(*(char **)state + 0x3b4)) >> 32);

    point = func_01fffd70(*(char **)state + 0x394);
    i = 0;
    while (point != 0) {
        *(struct Vec3 *)(state + 0x1c) = *point;
        if (i >= *(int *)(state + 0x34)) {
            return;
        }
        point = func_01fffd8c(*(char **)state + 0x394);
        i++;
    }
}
