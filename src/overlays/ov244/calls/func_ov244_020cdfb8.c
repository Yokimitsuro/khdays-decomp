/* Bounce-off entry: clears the actor's +0x390 word and sets bit 0 of +0x1ae; the +0x34 velocity
 * is -32.0 along the +4 pose's data_02042270 axis, the +0x40 one is 32.0 along data_02042240,
 * the +0x1c anchor's position is kept at +0x4c, the +0x30 range is 1/8 of the distance from the
 * anchor to the +0x384 item's +0x3bc target's +0x14 point, +0x2c clears and the node moves to
 * 020ce09c. */
typedef struct { int x, y, z; } Vec3;
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042270;
extern const Vec3 data_02042240;
extern void func_ov244_020ce09c(void);

void func_ov244_020cdfb8(int *node) {
    int *state = (int *)node[1];
    Vec3 d;

    *(int *)(*state + 0x390) = 0;
    *(unsigned short *)(*state + 0x100 + 0xae) |= 1;
    func_0202f384((Vec3 *)(state + 0xd), state + 1, &data_02042270);
    func_01ffa724(-0x20000, (Vec3 *)(state + 0xd), (Vec3 *)(state + 0xd));
    *(Vec3 *)(state + 0x10) = data_02042240;
    func_01ffa724(0x20000, (Vec3 *)(state + 0x10), (Vec3 *)(state + 0x10));
    *(Vec3 *)(state + 0x13) = *(Vec3 *)state[7];
    VEC_Subtract((Vec3 *)(*(int *)(*(int *)(*state + 0x384) + 0x3bc) + 0x14), (Vec3 *)state[7], &d);
    state[0xc] = VEC_Mag(&d) / 8;
    state[0xb] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov244_020ce09c);
}
