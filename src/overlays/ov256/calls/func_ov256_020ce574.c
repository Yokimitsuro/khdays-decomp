/* Turn tick of the ov256 actor: the +0x10 velocity is the +0x450 owner's +0x2c vector turned by its
 * heading (020cd054); once the partner holds no queued move a side is rolled (0 or 2) and the target
 * re-picked (020ccd54); a heading change of more than 35 degrees forces side 2. Pose 0x1f + side plays,
 * the +0x450 part takes motion 0x10 + side and the node moves on to 020ce650. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern int func_02023eb4(int n);
extern int func_ov256_020ccd54(int *node);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020ce650(void);

void func_ov256_020ce574(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;
    u8 side;
    int heading;

    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    *(Vec3 *)(state + 4) = v;
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    side = func_02023eb4(2) == 0 ? 2 : 0;
    heading = state[0x10];
    func_ov256_020ccd54(node);
    if (heading + 0x1922 < state[0x10] || heading - 0x1922 > state[0x10]) {
        side = 2;
    }
    func_ov107_020c9264(*state, side + 0x1f, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x450), side + 0x10, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020ce650);
}
