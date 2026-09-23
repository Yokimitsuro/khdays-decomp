/* Spin tick of an ov256 claw: the +0x60 timer accumulates the frame rate, the +0x10 velocity is the
 * +0x1c spin vector scaled by 1 + the owner's +0x3ac part's +0x45c boost (x 1/8), the claw moves
 * (020d1400 1, 2). Once the +0x390 part's animation (+0x3c -> +0xad) ends the timers clear, the +0x6d
 * flag is set, the part takes motion 1 and the node moves on to 020d227c. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov256_020d1400(int *node, int a, int b);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020d227c(void);

void func_ov256_020d21d0(int *node)
{
    int *state = (int *)node[1];

    state[0x18] += *(int *)(node[0] + 0x2c);
    *(Vec3 *)(state + 4) = *(Vec3 *)(state + 7);
    func_01ffa724((*(int *)(*(int *)(*state + 0x3ac) + 0x45c) << 9) + 0x1000, (Vec3 *)(state + 4), (Vec3 *)(state + 4));
    func_ov256_020d1400(node, 1, 2);
    if (*(u8 *)(*(int *)(*(int *)(*state + 0x390) + 0x3c) + 0xad) != 0) {
        return;
    }
    state[0x18] = 0;
    state[0x19] = 0;
    *((u8 *)state + 0x6d) = 1;
    func_ov107_020c9ee8(*(int *)(*state + 0x390), 1, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020d227c);
}
