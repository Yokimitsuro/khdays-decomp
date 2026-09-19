/* Hover tick: `ready` = the +0x70 timer has started and the actor's +0x10c slot is empty. While
 * the actor's +0x13c height is valid its +0x10 lift eases a tenth of the way to 6.0; while the
 * +0x6a latch is clear the +0x70 timer runs and past 0x1555 the latch is set and effect 7 spawns
 * at the zero vector. Unless the height is within 0x100 of 6.0, the actor's +0x17a bit 3 is set,
 * or both ready and the latch hold, nothing more happens; otherwise the second
 * halfword pair of data_ov213_020d2e6c goes through the +0x24 hook, pose 7 plays, the +0x1c timer restarts at
 * 0xc00, the +0x64 counter clears and the node moves to 020cfe48. */
struct vec3 { int x, y, z; };
struct Bits17a { unsigned char b0 : 1, b1 : 1, b2 : 1, b3 : 1; };
extern void func_ov107_020c0b90();  /* K&R + const vector: hoists the pool load over the latch store */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
extern const struct vec3 data_02041dc8;
extern unsigned short data_ov213_020d2e6c[];
extern void func_ov213_020cfe48(void);

void func_ov213_020cfcd0(int *self) {
    int actor;
    int *state = (int *)self[1];
    int ready;
    unsigned short pair[2];
    unsigned short *pp;

    actor = *state;
    if (state[0x1c] != 0 && *(int *)(actor + 0x10c) == 0) ready = 1;
    else ready = 0;
    if (*(int *)(actor + 0x13c) != 0x7fffffff) {
        state[4] += (0x6000 - *(int *)(actor + 0x13c)) / 10;
    }
    if (*((unsigned char *)state + 0x6a) == 0) {
        state[0x1c] += *(int *)(self[0] + 0x2c);
        if (state[0x1c] >= 0x1555) {
            *((unsigned char *)state + 0x6a) = 1;
            func_ov107_020c0b90(*state, 7, data_02041dc8, 0);
        }
    }
    {
        int d = *(int *)(actor + 0x13c) - 0x6000;
        if (d < 0) d = -d;
        if (d >= 0x100) {
            if (((struct Bits17a *)(*state + 0x17a))->b3 == 0) {
                if (ready == 0 || *((unsigned char *)state + 0x6a) == 0) return;
            }
        }
    }
    pp = pair;
    pp[1] = data_ov213_020d2e6c[3];
    pp[0] = data_ov213_020d2e6c[2];
    if (*(void **)(*state + 0x24) != 0) {
        (*(void (**)(int, unsigned short *, int))(*state + 0x24))(*state, pp, 4);
    }
    func_ov107_020c9264(*state, 7, 0);
    state[7] = 0xc00;
    state[0x19] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov213_020cfe48);
}
