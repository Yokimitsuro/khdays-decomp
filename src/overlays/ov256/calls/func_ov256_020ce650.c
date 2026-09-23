/* Retreat tick of the ov256 actor: the +0x10 velocity is the +0x450 owner's +0x2c vector turned by
 * its heading (020cd054); once the partner holds no queued move, in retreat mode 2 (+0x6b) a fresh
 * pick (020ccdf0) other than move 9 just ends the node; otherwise mode 2 is set, the next move is the
 * +0x74 mode + 2 and the node ends. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern int func_ov256_020ccdf0(int *node);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov256_020ce650(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    *(Vec3 *)(state + 4) = v;
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (*((u8 *)state + 0x6b) == 2 && func_ov256_020ccdf0(node) && *(signed char *)(*state + 0x1c7) != 9) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *((u8 *)state + 0x6b) = 2;
    *(signed char *)(*state + 0x1c7) = state[0x1d] + 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
