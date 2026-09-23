/* Attack entry: once bit 0 of the actor's +0x60 low byte is up, the +0x78 aggressive flag is set,
 * command 0xd (1) goes out (020cd920), the +0x73 flag and the actor's +0x4d8 / +0x4dc slots
 * clear, the +0x3c cooldown restarts (8.0), +0x6c clears, the next waypoint is picked into +0x34
 * and copied to +0x30, the +0x18 point is dropped to the ground (height into +0x1c) and the actor
 * lands there; the actor's +0x1c9 move becomes the pending one and the handler is cleared. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct Hw60 { u16 lo : 8; u16 hi : 8; };

extern void func_ov254_020cd920(int *self, int arg);
extern void func_ov254_020cd5f4(int *state, int a, int *out);
extern int func_ov254_020ccfd4(int *self, Vec3 pos, int *outY);
extern void func_ov107_020c5c54(int actor, void *at);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov254_020ce504(int *node)
{
    int *state = (int *)node[1];

    if ((((struct Hw60 *)(*state + 0x60))->lo & 1) == 0) {
        return;
    }
    state[0x1e] = 1;
    func_ov254_020cd920(state, 1);
    *((u8 *)state + 0x73) = 0;
    *(int *)(*state + 0x4d8) = 0;
    *(int *)(*state + 0x4dc) = 0;
    state[0xf] = (state[0x1e] != 0 ? 8 : 0xf) << 12;
    state[0x1b] = 0;
    func_ov254_020cd5f4(state, 1, state + 0xd);
    state[0xc] = state[0xd];
    func_ov254_020ccfd4(state, *(Vec3 *)(state + 6), state + 7);
    func_ov107_020c5c54(*state, state + 6);
    *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x100 + 0xc9);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
