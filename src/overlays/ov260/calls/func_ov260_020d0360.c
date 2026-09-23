/* Dash entry tick of the ov260 actor: with a +8 target it turns to it (+0x64 / +0x68 heading), pose
 * 0xa plays, its +0x428 part takes motion 4, the actor is knocked back at the origin (mode 0xd, 8)
 * and at the +0x10 point (mode 9), effect 0x1c starts there, +0x70 and the +0x7b flag clear, the dash
 * starts (+0x7c) and the node moves on to 020d04bc. Without one, once the partner holds no queued move,
 * pose 0xb plays, the origin knock-back (mode 0xd, 8) runs and the node moves on the same way. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int y);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020d04bc(void);
extern const Vec3 data_02041dc8;

void func_ov260_020d0360(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    if (state[2] != 0) {
        VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)state[4], &d);
        state[0x19] = state[0x1a] = func_020050b4(d.x, d.z);
        func_ov107_020c9264(*state, 0xa, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x428), 4, 0);
        func_ov107_020c0b90(*state, 0xd, data_02041dc8, 8);
        func_ov107_020c0b90(*state, 9, *(Vec3 *)state[4], 0);
        func_ov260_020cd148(*state, 0x1c, state[4]);
        state[0x1c] = 0;
        *((u8 *)state + 0x7b) = 0;
        state[0x1f] = 1;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020d04bc);
        return;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xb, 0);
    func_ov107_020c0b90(*state, 0xd, data_02041dc8, 8);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020d04bc);
}
