/* Charge-up tick of the ov250 enemy (x4: ov250/182/183/184): the +0x1c timer grows by dt and the
 * actor's +0x394 scale shrinks as 1.0 - t / 0x555 (never under 0x1). Once the timer passes
 * 0x555 (a third of a second) the scale settles at 0x1, bit 0 of +0x1ae is set, bit 0 of the +0x388 list node's +8
 * flags cleared, bit 1 of the +0x60 high byte set and pose 6 loops; two random directions
 * (a 0..0x6489 turn minus 0x3244, i.e. +-pi) become the +0x28 and +0x34 velocities (sine/cosine
 * table, y 0) scaled by 10.0 plus a random 0..5.0; the +4 position is copied into +0x40, +0x4c
 * gets a third random angle, the timer restarts and handler 020cd844 takes over. */
typedef struct { int x, y, z; } Vec3;
struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern int FX_Inv(int a, int b);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_02023eb4(int bound);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int node, int slot, void *cb);
extern void func_ov250_020d1298(void);
extern const short data_0203d210[];

void func_ov250_020d1068(int node)
{
    int *state = *(int **)(node + 4);
    int angle;
    int idx;
    int angle2;
    int idx2;

    state[7] += *(int *)(*(int *)node + 0x2c);
    *(int *)(*state + 0x394) = 0x1000 - FX_Inv(state[7], 0x555);
    if (*(int *)(*state + 0x394) < 0x1) {
        *(int *)(*state + 0x394) = 0x1;
    }
    if (state[7] < 0x555) {
        return;
    }
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 2) << 0x18) >> 0x10));
    }
    func_ov107_020c9264(*state, 6, 1);
    *(int *)(*state + 0x394) = 0x1;
    angle = func_02023eb4(0x6489) - 0x3244;
    idx = (unsigned short)((0x28BE60DB9391LL * angle + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    state[10] = data_0203d210[(idx >> 4) << 1];                                    /* FX_SinIdx */
    state[11] = 0;
    state[12] = data_0203d210[((idx >> 4) << 1) + 1];                              /* FX_CosIdx */
    func_01ffa724(func_02023eb4(0x5001) + 0xa000, (Vec3 *)(state + 10), (Vec3 *)(state + 10));
    angle2 = func_02023eb4(0x6489) - 0x3244;
    idx2 = (unsigned short)((0x28BE60DB9391LL * angle2 + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    state[13] = data_0203d210[(idx2 >> 4) << 1];                                    /* FX_SinIdx */
    state[14] = 0;
    state[15] = data_0203d210[((idx2 >> 4) << 1) + 1];                              /* FX_CosIdx */
    func_01ffa724(func_02023eb4(0x5001) + 0xa000, (Vec3 *)(state + 13), (Vec3 *)(state + 13));
    *(Vec3 *)(state + 16) = *(Vec3 *)state[1];
    state[19] = func_02023eb4(0x6489) - 0x3244;
    state[7] = 0;
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov250_020d1298);
}
