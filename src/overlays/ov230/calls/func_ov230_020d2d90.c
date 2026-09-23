/* Contact check of the ov230 actor: with a target (+8) and the hit window open (+0x68), the direction
 * from the owner's +0x494 point to the target is kept (normalised) and, flattened (world +z when
 * degenerate) and scaled to 0.5, offered as a kind-4 hit. On acceptance effect 1 spawns at the +0x494
 * point pushed out by the +0x4a0 radius along the direction plus that offset, and reaction 0x147 mode
 * 6 fires at the +0xc position. Returns whether the hit landed. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int a, int b, u8 kind, Vec3 *push, int z);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int owner, int cue, int kind, void *target);
extern const Vec3 data_02042258;

int func_ov230_020d2d90(int *state)
{
    Vec3 dir;
    Vec3 at;

    if (state[2] != 0 && state[0x1a] != 0) {
        VEC_Subtract((Vec3 *)(state[2] + 0x74), (Vec3 *)(*state + 0x494), &dir);
        func_01ff8d18(&dir, &at);
        dir.y = 0;
        if (func_01ff8d18(&dir, &dir) == 0) {
            dir = data_02042258;
        }
        func_01ffa724(0x800, &dir, &dir);
        if (func_ov107_020ca918(state[2], *state, *state, 4, &dir, 0) != 0) {
            func_01ffa724(*(int *)(*state + 0x4a0), &at, &at);
            VEC_Add(&at, &dir, &at);
            VEC_Add(&at, (Vec3 *)(*state + 0x494), &at);
            func_ov107_020c0b90(*state, 1, at, 0);
            func_ov107_020c5af8(*state, 0x147, 6, (void *)state[3]);
            return 1;
        }
    }
    return 0;
}
