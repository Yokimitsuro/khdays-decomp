/* func_ov245_020cfb30 -- node initialiser: resets the actor's +0x1c6 state and +0x1c7 request,
 * clears bit 0 of the +0x388 item's +8 low byte, points the state's +8 at the actor's +0xb0
 * pose, raises bits 1, 2 and 7 and clears bit 0 of the +0x60 high byte, and installs the three
 * slot handlers (1: 020cfdec, 0: 020cfc14, 2: 020cfd54). */
typedef unsigned short u16;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020cfdec(void);
extern void func_ov245_020cfc14(void);
extern void func_ov245_020cfd54(void);

void func_ov245_020cfb30(int *node) {
    int *state = (int *)node[1];

    *(unsigned char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    ((struct w8 *)(*(int *)(*state + 0x388) + 8))->lo &= ~1;
    state[2] = *state + 0xb0;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x86) << 0x18) >> 0x10);
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    func_0203c634(node, 1, func_ov245_020cfdec);
    func_0203c634(node, 0, func_ov245_020cfc14);
    func_0203c634(node, 2, func_ov245_020cfd54);
}
