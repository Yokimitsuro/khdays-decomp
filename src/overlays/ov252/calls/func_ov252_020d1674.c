/* Blast tick of the ov252 actor: aim tracking runs (020cdfe8, 020ce370) while the +0x64 and +0x6c
 * timers accumulate the frame rate. At 0xee0 on the second timer reaction 0x148/0x13 fires once
 * (+0x89) at the +8 track. Between 0x990 and 0x25b8 the blast is live: the actor is knocked back
 * in place once (mode 0x12, +0x88) and a sphere 2.0 ahead of its +0xb0 position (turned by the
 * +0x54 angle) grows from 4.5 to 14.5 and strikes (020ce0a8, kind 3). Once the +4 item's +0xad
 * byte clears poses 0x33 / 0x37 loop and the next move is 0xb (+0xac set, +0xa0 cleared) or 0xd. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;

extern int func_ov252_020cdfe8(int *node, int a, int b);
extern int func_ov252_020ce370(int *node);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov252_020cdafc(Vec3 *v, int angle, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov252_020ce0a8(int *state, int kind, Sphere *sphere, int a, int b);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;

void func_ov252_020d1674(int *node)
{
    int *state = (int *)node[1];
    Sphere blast;

    func_ov252_020cdfe8(node, 0, 1);
    state[0x19] += *(int *)(node[0] + 0x2c);
    state[0x1b] += *(int *)(node[0] + 0x2c);
    func_ov252_020ce370(node);
    if (*((u8 *)state + 0x89) == 1 && state[0x1b] >= 0xee0) {
        (*((u8 *)state + 0x89))--;
        func_ov107_020c5af8(*state, 0x148, 0x13, (void *)state[2]);
    }
    if (state[0x19] >= 0x990 && state[0x19] < 0x25b8) {
        if (*((u8 *)state + 0x88) == 1) {
            (*((u8 *)state + 0x88))--;
            func_ov107_020c0b90(*state, 0x12, data_02041dc8, 0);
        }
        {
        Vec3 fwd = { 0, 0, 0x2000 };

        func_ov252_020cdafc(&fwd, state[0x15], &fwd);
        VEC_Add((Vec3 *)(*state + 0xb0), &fwd, &blast.pos);
        blast.radius = 0x4800;
        blast.radius = (state[0x19] - 0x990) * 0xa000 / 0x1c28 + 0x4800;
        func_ov252_020ce0a8(state, 3, &blast, 0, 0);
        }
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x33, 1);
    func_ov107_020c9264(*state, 0x37, 1);
    if (state[0x2b] == 0) {
        *(signed char *)(*state + 0x1c7) = 0xd;
    } else {
        state[0x28] = 0;
        *(signed char *)(*state + 0x1c7) = 0xb;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
