/* Step tick of the ov256 actor: the +0x10 velocity is the +0x450 owner's +0x2c vector turned by its
 * heading (020cd054); once the partner holds no queued move +0x54, +0x4c and the +0x69 charges clear,
 * the +0x70 turn direction is rolled (+1 or -1), pose 1 plays, the +0x450 part takes motion 0 and the
 * node moves on to 020cdc98. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern int func_02023eb4(int n);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020cdc98(void);

void func_ov256_020cdbe4(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    *(Vec3 *)(state + 4) = v;
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    state[0x15] = 0;
    state[0x13] = 0;
    *((u8 *)state + 0x69) = 0;
    *((signed char *)state + 0x70) = func_02023eb4(2) == 0 ? 1 : -1;
    func_ov107_020c9264(*state, 1, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x450), 0, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020cdc98);
}
