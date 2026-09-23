/* Roar tick of the ov256 actor: the +0x4c timer accumulates the frame rate; at 0x6e8 the last charge
 * (+0x69 == 1) is spent and the actor is knocked back at the origin twice (modes 0xc and 0xd). Once the
 * partner holds no queued move +0x54 clears, pose 0xd plays and the node moves on to 020cf974. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020cf974(void);
extern const Vec3 data_02041dc8;

void func_ov256_020cf88c(int *node)
{
    int *state = (int *)node[1];

    state[0x13] += *(int *)(node[0] + 0x2c);
    if (state[0x13] >= 0x6e8 && *((u8 *)state + 0x69) == 1) {
        Vec3 origin;

        *((u8 *)state + 0x69) -= 1;
        origin = data_02041dc8;
        func_ov107_020c0b90(*state, 0xc, origin, 0);
        func_ov107_020c0b90(*state, 0xd, origin, 0);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    state[0x15] = 0;
    func_ov107_020c9264(*state, 0xd, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020cf974);
}
