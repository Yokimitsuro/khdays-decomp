/* Rise tick of the ov252 actor: the guard sweep runs (020ce370); once +0x64 reaches 0.4 with +0x89 at
 * 1 it drops to 0 and sound 0x148/4 plays at the +8 point. The +0xc velocity is damped to 0.875 and
 * gains the +0x574 part's +0x2c vector turned by the +0x54 heading; once the partner holds no queued
 * move +0x7c is half the frame rate, it faces the target, +0x88 = 3 with a lift height set and the node
 * moves on to 020d1abc. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020ce370(int *node);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov252_020cdfe8(int *node, Vec3 *delta, int face);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d1abc(void);

void func_ov252_020d25e8(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov252_020ce370(node);
    state[0x19] += *(int *)(node[0] + 0x2c);
    if (state[0x19] >= 0x660 && *((unsigned char *)state + 0x89) == 1) {
        *((unsigned char *)state + 0x89) -= 1;
        func_ov107_020c5af8(*state, 0x148, 4, (void *)state[2]);
    }
    func_ov252_020cdafc(&v, state[0x15], (Vec3 *)(*(int *)(*state + 0x574) + 0x2c));
    func_01ffa724(0xe00, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    VEC_Add((Vec3 *)(state + 3), &v, (Vec3 *)(state + 3));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    state[0x1f] = *(int *)(node[0] + 0x2c) / 2;
    func_ov252_020cdfe8(node, 0, 1);
    if (state[0x1e] != 0) {
        *((unsigned char *)state + 0x88) = 3;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d1abc);
}
