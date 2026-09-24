/* Charge entry of the ov236 mount: notes whether each rider (+0x3b4 / +0x3b8) is free (bit 1 of its
 * +0x1ac flags clear), plays pose 0 looping, sets the +0x14 speed to 0.6 of the frame step, picks
 * the +0x30 turn side at random (+1 / -1), the +0x2c run time (rand(7.0) + 3.0), clears the +0x28
 * clock and gives the actor 3.0 of +0x54 invulnerability. With a free rider the +0x3a8 part raises
 * bit 1; the +0x5c height is taken from the +0x34 point and the node moves to 020d05dc. */
typedef unsigned short u16;
struct PartFlags { unsigned int lo : 8; };

extern void func_ov107_020c9264(int owner, int pose, int loop);
extern int func_02023eb4(int bound);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov236_020d05dc(void);

void func_ov236_020d04d0(int *node)
{
    int v;
    int *state = (int *)node[1];
    int front = *(int *)(*state + 0x3b4);
    int rear = *(int *)(*state + 0x3b8);
    int frontFree = (*(u16 *)(front + 0x100 + 0xac) & 2) ? 0 : 1;
    int rearFree = (*(u16 *)(rear + 0x100 + 0xac) & 2) ? 0 : 1;

    func_ov107_020c9264(*state, 0, 1);
    state[5] = *(int *)(node[0] + 0x2c) * 30 / 50;
    state[0xc] = func_02023eb4(2) + (v - v) != 0 ? 1 : -1;
    state[0xb] = func_02023eb4(0x7001) + 0x3000;
    state[0xa] = 0;
    *(int *)(*state + 0x54) = 0x3000;
    if (frontFree || rearFree) {
        ((struct PartFlags *)(*(int *)(*state + 0x3a8) + 8))->lo |= 2;
    }
    state[0x17] = *(int *)(state[0xd] + 4);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov236_020d05dc);
}
