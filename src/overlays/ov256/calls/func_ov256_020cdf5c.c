/* Walk entry tick of the ov256 actor: the +0x10 velocity is the +0x450 owner's +0x2c vector turned by
 * its heading (020cd054); once the partner holds no queued move, coming from move 7 the +0x44 target
 * heading swings by 70 degrees (and +0x40 follows), a pending retreat (+0x6b) re-picks the target, the
 * step count +0x54 = 5, +0x4c and +0x74 clear, the +0x71 turn direction is rolled, pose 2 plays, the
 * +0x450 part takes motion 1 and the node moves on to 020ce050. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern int func_ov256_020ccd54(int *node);
extern int func_02023eb4(int n);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020ce050(void);

void func_ov256_020cdf5c(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    *(Vec3 *)(state + 4) = v;
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (*(signed char *)(*state + 0x1c8) == 7) {
        state[0x10] = state[0x11] += 0x3244;
    }
    if (*((u8 *)state + 0x6b) != 0) {
        func_ov256_020ccd54(node);
    }
    state[0x15] = 5;
    state[0x13] = 0;
    *((signed char *)state + 0x71) = func_02023eb4(2) == 0 ? 1 : -1;
    state[0x1d] = 0;
    func_ov107_020c9264(*state, 2, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x450), 1, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020ce050);
}
