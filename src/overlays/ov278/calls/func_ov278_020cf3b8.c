/* Node initialiser (mount form): resets the actor's +0x1c6 state and +0x1c7 request, clears
 * bit 0 of the +0x3a4 item's +8 low byte, points the state's +0x34 at the actor's +0xb0 pose and
 * +0x38 at its +0x74 position, raises bits 1-2 and clears bit 7 of the +0x60 high byte, sets
 * bit 2 of the state's +0x52 and installs the three slot handlers (1: 020cfa88, 0: 020cf4b4,
 * 2: 020cf984). */
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov278_020cfa30(void);
extern void func_ov278_020cf4b4(void);
extern void func_ov278_020cf984(void);

void func_ov278_020cf3b8(int *node) {
    int *state = (int *)node[1];
    int zero = 0;

    *(signed char *)(*state + 0x1c6) = zero;
    *(signed char *)(*state + 0x1c7) = zero - 1;
    ((struct w8 *)(*(int *)(*state + 0x3a4) + 8))->lo &= ~1;
    state[0xd] = *state + 0xb0;
    state[0xe] = *state + 0x74;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 6) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    }
    *((unsigned char *)state + 0x52) |= 4;
    func_0203c634(node, 1, func_ov278_020cfa30);
    func_0203c634(node, 0, func_ov278_020cf4b4);
    func_0203c634(node, 2, func_ov278_020cf984);
}
