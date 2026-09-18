/* Guard tick of the ov220 enemy: the +0x14 timer accumulates the frame-time; at 0x7000 with
 * the +0x3e flag clear, the +4 item's +0xa8 byte is cleared and the flag set. Once the item is
 * idle the actor plays animation 12 and hands off to the next guard state. */
typedef unsigned char u8;

extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov220_020d3960(int *node);

void func_ov220_020d38e0(int *node)
{
    int *state = (int *)node[1];

    state[5] += *(int *)(*node + 0x2c);
    if (*(u8 *)((char *)state + 0x3e) == 0 && state[5] >= 0x7000) {
        *(u8 *)(state[1] + 0xa8) = 0;
        *(u8 *)((char *)state + 0x3e) = 1;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xc, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov220_020d3960);
}
