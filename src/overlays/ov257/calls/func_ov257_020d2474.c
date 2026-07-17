/*
 * func_ov257_020d2474 -- x3. AI-state tick: kick off a fixed motion (mode 0xd), flag it, dispatch.
 * 020c0b90(state[0], mode 0xd, const vec data_02041dc8 by value, flag 0); then set bits 0x3 in the
 * halfword flags at *(u16*)(state[0]+0x1ae). Hand off via 0203c634 (cb=0).
 */
struct vec3 { int x, y, z; };
extern struct vec3 data_02041dc8;
extern void func_ov107_020c0b90(int obj, int mode, struct vec3 v, int flag);
extern void func_0203c634(int self, int idx, int cb);

void func_ov257_020d2474(int *self) {
    int *state = (int *)self[1];

    func_ov107_020c0b90(*state, 0xd, data_02041dc8, 0);
    *(unsigned short *)(*state + 0x1ae) |= 3;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
