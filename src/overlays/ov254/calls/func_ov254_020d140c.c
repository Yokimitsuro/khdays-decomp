/* Landing tick: the +0x10 fall speed clears; once the +4 item's +0xad byte clears the actor is
 * knocked back in place (mode 5, flag 2). While aggressive (+0x78) the next move is 6; otherwise
 * pose 0x12 plays, the +0x3e4 shape gains bit 1 and the +0x3e0 one loses it, the +0x44 timer and
 * +0x70 flag clear and the node moves to 020d151c. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov254_020d151c(void);

void func_ov254_020d140c(int *node)
{
    int *state = (int *)node[1];

    state[4] = 0;
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c0b90(*state, 5, data_02041dc8, 2);
    if (state[0x1e] != 0) {
        *(signed char *)(*state + 0x1c7) = 6;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov107_020c9264(*state, state[0x1e] != 0 ? 9 : 0x12, 0);
    ((B8 *)(*(int *)(*state + 0x3e4) + 8))->f |= 2;
    ((B8 *)(*(int *)(*state + 0x3e0) + 8))->f &= ~2;
    state[0x11] = 0;
    *((u8 *)state + 0x70) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d151c);
}
