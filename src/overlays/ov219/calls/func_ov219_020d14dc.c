/* Guard tick of the ov219 enemy (and its byte-identical twin): only while the +0x18 phase is
 * below 2. The +0x14 timer loses the frame-time (floored at zero); when it has run out and the
 * +0x3e flag is clear, the +4 item's +0xa8 byte is cleared and the flag set. Once the item is
 * idle the actor plays animation 8, publishes a zero vector to it with mode 4 (flag 2) and hands
 * off to the next guard state. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };

extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c0b90(int actor, int a, struct Vecx32 v, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern const struct Vecx32 data_02041dc8;
extern void func_ov219_020d15ac(int *node);

void func_ov219_020d14dc(int *node)
{
    int *state = (int *)node[1];

    if (state[6] >= 2) {
        return;
    }
    state[5] -= *(int *)(*node + 0x2c);
    if (state[5] < 0) {
        state[5] = 0;
    }
    if (*(u8 *)((char *)state + 0x3e) == 0 && state[5] == 0) {
        *(u8 *)(state[1] + 0xa8) = 0;
        *(u8 *)((char *)state + 0x3e) = 1;
    }
    if (*(u8 *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 8, 0);
        func_ov107_020c0b90(*state, 4, data_02041dc8, 2);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov219_020d15ac);
    }
}
