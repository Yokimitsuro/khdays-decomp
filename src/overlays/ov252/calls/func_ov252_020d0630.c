/* Shed drift tick of the ov252 actor: the +0xc velocity follows the +0x574 part's +0x2c vector turned
 * by the +0x54 heading and scaled by +0x70 + 0.5 (height from the part's +0x30); +0x64 accumulates the
 * frame rate and after 0.83 the drop cue (+0x88) re-arms once (+0x8c). With the cue armed, a 50 % roll
 * drops a reward (020d056c): a drop counts in +0x60 and disarms the cue, no pieces left ends the drift.
 * Once the partner holds no queued move the drift ends after 12 drops, beyond 25.0 from the origin or
 * with a +0xa0 reward pending (pose 0x15, motion 0xe, effect 4 mode 2, node to 020d0854); otherwise
 * pose 0x14, motion 0xd and effect 4 mode 1 restart it. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov252_020cdafc(Vec3 *out, int angle, Vec3 *vec);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern unsigned int func_02023eb4(int bound);
extern int func_ov252_020d056c(int *node, int param);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d0854(void);
extern const Vec3 data_02041dc8;

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov252_020d0630(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    Vec3 v;
    int dist;

    func_ov252_020cdafc(&v, state[0x15], (Vec3 *)(*(int *)(*state + 0x574) + 0x2c));
    *(Vec3 *)(state + 3) = v;
    func_01ffa724(state[0x1c] + 0x800, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    state[4] = *(int *)(*(int *)(*state + 0x574) + 0x30);
    state[0x19] += *(int *)(node[0] + 0x2c);
    if (state[0x19] >= 0xd48 && *((unsigned char *)state + 0x8c) == 0) {
        *((unsigned char *)state + 0x88) = 0;
        *((unsigned char *)state + 0x8c) = 1;
    }
    if (*((unsigned char *)state + 0x88) == 0 && func_02023eb4(0x64) < 0x32) {
        switch (func_ov252_020d056c(node, 2)) {
        case 0:
            break;
        case 1:
            state[0x18]++;
            *((unsigned char *)state + 0x88) = 1;
            break;
        case 2:
            goto finish;
        }
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    VecSet(&d, -((Vec3 *)state[2])->x, 0, -((Vec3 *)state[2])->z);
    dist = func_01ff8d18(&d, &d);
    if (state[0x18] >= 0xc || dist > 0x19000 || state[0x28] != 0) {
finish:
        func_ov107_020c9264(*state, 0x15, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 0xe, 0);
        func_ov107_020c0b90(*state, 4, data_02041dc8, 2);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d0854);
        return;
    }
    func_ov107_020c9264(*state, 0x14, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x574), 0xd, 0);
    func_ov107_020c0b90(*state, 4, data_02041dc8, 1);
    state[0x19] = 0;
    *((unsigned char *)state + 0x8c) = 0;
}
