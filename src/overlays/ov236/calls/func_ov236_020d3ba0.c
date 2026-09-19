/* Node initialiser (second rider form): resets the actor's +0x1c6 state and +0x1c7 request,
 * clears bit 0 of the +0x3c0 / +0x3c4 items' +8 low byte, points the state's +0x1c at the
 * actor's +0xb0 pose and +0x20 at the +0x388 item's +0xad, raises bits 1-2 of the +0x60 high
 * byte and installs the three slot handlers (1: 020d4010, 0: 020d3c90, 2: 020d3f50). */
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov236_020d4010(void);
extern void func_ov236_020d3c90(void);
extern void func_ov236_020d3f50(void);

void func_ov236_020d3ba0(int *node) {
    int *state = (int *)node[1];
    int zero = 0;

    *(signed char *)(*state + 0x1c6) = zero;
    *(signed char *)(*state + 0x1c7) = zero - 1;
    ((struct w8 *)(*(int *)(*state + 0x3c0) + 8))->lo &= ~1;
    ((struct w8 *)(*(int *)(*state + 0x3c4) + 8))->lo &= ~1;
    state[7] = *state + 0xb0;
    state[8] = *(int *)(*state + 0x388) + 0xad;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 6) << 0x18) >> 0x10);
    }
    func_0203c634(node, 1, func_ov236_020d4010);
    func_0203c634(node, 0, func_ov236_020d3c90);
    func_0203c634(node, 2, func_ov236_020d3f50);
}
