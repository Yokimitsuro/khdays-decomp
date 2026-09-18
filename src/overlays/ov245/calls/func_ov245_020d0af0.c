/* func_ov245_020d0af0 -- aim: copies the given direction into the state's +0x18 vector, scales
 * it by 0.875 into the +0xc velocity and, unless the actor's kind byte is 1, raises bit 0 of the
 * +0x60 high byte and requests sub-state 1. */
typedef struct { int x, y, z; } Vec3;
typedef unsigned short u16;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);

void func_ov245_020d0af0(int *state, const Vec3 *dir) {
    *(Vec3 *)(state + 6) = *dir;
    func_01ffa724(0xe00, (Vec3 *)(state + 6), (Vec3 *)(state + 3));
    if (*(signed char *)(*state + 0x1c6) != 1) {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
        *(unsigned char *)(*state + 0x1c7) = 1;
    }
}
