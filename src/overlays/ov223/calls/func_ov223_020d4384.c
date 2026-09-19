/* Charge setup of the ov223 enemy's state: keeps the variant at +0x48, the caller's target
 * point (the second by-value vector; the first is unused) at +0x20, zeroes the +0x14 velocity, +0x44 and the +0x4c byte, sets the
 * +0x2c pose to face the target from data_02042258 (ed60) and requests sub-state 1. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int q[4]; } Quat;

extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;

void func_ov223_020d4384(int *state, int nVariant, Vec3 vFrom, Vec3 vTarget)
{
    state[0x12] = nVariant;
    *(Vec3 *)(state + 8) = vTarget;
    *(Vec3 *)(state + 5) = data_02041dc8;
    state[0x11] = 0;
    *(unsigned char *)((char *)state + 0x4c) = 0;
    func_0202ed60((Quat *)(state + 0xb), &data_02042258, &vTarget);
    *(unsigned char *)(*state + 0x1c7) = 1;
}
