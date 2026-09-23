/* Throw release entry of the ov218 actor: the +0x28 velocity takes the +0x34 drift, which decays to
 * 0.69; once the partner holds no queued move pose 6 loops, effect 1 fires at the origin, the +0x14
 * timer starts at 75.0 and is scaled by 1.5 per throw out (+0x24), +0x40 clears and the node moves on
 * to 020cda78. */
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov218_020cda78(void);
extern const Vec3 data_02041dc8;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov218_020cd974(int *node)
{
    int *state = (int *)node[1];
    int i;

    *(Vec3 *)(state + 0xa) = *(Vec3 *)(state + 0xd);
    func_01ffa724(0xb00, (Vec3 *)(state + 0xd), (Vec3 *)(state + 0xd));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 6, 1);
    func_ov107_020c0b90(*state, 1, data_02041dc8, 0);
    state[5] = 0x4b000;
    for (i = 0; i < state[9]; i++) {
        state[5] = FX_MUL(state[5], 0x1800);
    }
    *((unsigned char *)state + 0x40) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov218_020cda78);
}
