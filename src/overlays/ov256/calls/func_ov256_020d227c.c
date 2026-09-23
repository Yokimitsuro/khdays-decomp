/* Swing tick of an ov256 claw: the +0x60 timer accumulates the frame rate, the +0x10 velocity is the
 * +0x390 part's +0x2c vector turned by the claw's heading (020d1900) and the claw moves (020d1400 1, 2).
 * Each time the part's animation ends the swing count (+0x64) grows: on the second swing the timer
 * clears, the +0x1c spin reverses, the part takes motion 2 and the node moves on to 020d2368;
 * otherwise the part restarts motion 1. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov256_020d1900(int *out, int param_2, int *vec);
extern void func_ov256_020d1400(int *node, int a, int b);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020d2368(void);

void func_ov256_020d227c(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    state[0x18] += *(int *)(node[0] + 0x2c);
    func_ov256_020d1900((int *)&v, (int)node, (int *)(*(int *)(*state + 0x390) + 0x2c));
    *(Vec3 *)(state + 4) = v;
    func_ov256_020d1400(node, 1, 2);
    if (*(u8 *)(*(int *)(*(int *)(*state + 0x390) + 0x3c) + 0xad) != 0) {
        return;
    }
    if (++state[0x19] == 2) {
        state[0x18] = 0;
        func_01ffa724(-0x1000, (Vec3 *)(state + 7), (Vec3 *)(state + 7));
        func_ov107_020c9ee8(*(int *)(*state + 0x390), 2, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020d2368);
        return;
    }
    func_ov107_020c9ee8(*(int *)(*state + 0x390), 1, 0);
}
