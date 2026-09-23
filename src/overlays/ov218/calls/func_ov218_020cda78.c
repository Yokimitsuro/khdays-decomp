/* Throw tick of the ov218 actor: the +0x28 velocity takes the +0x34 drift, which decays to 0.69; while
 * fewer than two throws are out (+0x24) the +0x14 timer runs down (to 0) and at 0 the partner's +0xa8
 * hold clears (once, +0x40); after the partner holds no queued move pose 7 plays, effect 3 fires at the
 * origin and the node moves on to 020cdb68. */
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov218_020cdb68(void);
extern const Vec3 data_02041dc8;

void func_ov218_020cda78(int *node)
{
    int *state = (int *)node[1];

    *(Vec3 *)(state + 0xa) = *(Vec3 *)(state + 0xd);
    func_01ffa724(0xb00, (Vec3 *)(state + 0xd), (Vec3 *)(state + 0xd));
    if (state[9] >= 2) {
        return;
    }
    state[5] -= *(int *)(node[0] + 0x2c);
    if (state[5] < 0) {
        state[5] = 0;
    }
    if (*((unsigned char *)state + 0x40) == 0 && state[5] == 0) {
        *(unsigned char *)(state[1] + 0xa8) = 0;
        *((unsigned char *)state + 0x40) = 1;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 7, 0);
    func_ov107_020c0b90(*state, 3, data_02041dc8, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov218_020cdb68);
}
