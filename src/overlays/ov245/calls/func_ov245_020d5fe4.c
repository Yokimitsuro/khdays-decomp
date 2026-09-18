/* func_ov245_020d5fe4 -- spin tick: advances the state's +0x10 angle towards +0x14 at the +0x18
 * rate (0203d040), builds the rotation about the world up axis (0202f188 on 02042264) and the
 * one that aligns the actor's +0x124 facing (0202ed60), combines them (0202ef54) into the
 * actor's +0xa0 placement, then pushes the +0x1c velocity to the actor's +0xf0 and clears it.
 * Codegen: the shared +0x1c address is a named pointer so the copy evaluates its destination
 * address first (ip) and the source (lr) second. */
typedef struct { int x, y, z; } Vec3;

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(void *out, void *tbl, int idx);
extern void func_0202ed60(void *out, const Vec3 *a, const Vec3 *b);
extern void func_0202ef54(void *out, void *a, void *b);
extern void func_0203c9d0(int placement, void *rotation);
extern char data_02042264[];
extern const Vec3 data_02041dc8;

void func_ov245_020d5fe4(int *node) {
    int *state = (int *)node[1];
    int face[4];
    int spin[4];

    state[4] = func_0203d040(state[4], state[5], state[6], 0);
    func_0202f188(spin, data_02042264, state[4]);
    func_0202ed60(face, (const Vec3 *)data_02042264, (Vec3 *)(*state + 0x124));
    func_0202ef54(face, face, spin);
    func_0203c9d0(*state + 0xa0, face);
    {
        Vec3 *push = (Vec3 *)(state + 7);
        Vec3 *dst = (Vec3 *)(*state + 0xf0);
        *dst = *push;
        *push = data_02041dc8;
    }
}
