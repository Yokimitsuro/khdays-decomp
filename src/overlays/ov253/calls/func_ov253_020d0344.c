/* func_ov253_020d0344 -- carry tick: the +0x18 speed follows twice the frame step (30 / 15);
 * until the +0x30 latch is set the +0x3bc target's +0x18c rider (its +0x20 child) is seated at
 * the actor's +0x3ac joint anchor and the +0x1c timer runs up; past 0.667 the latch is raised,
 * bit 7 of the target's +0x60 high byte set and the node moves to 020d0410. */
typedef unsigned short u16;

extern void func_0202b450(int node, void *pos);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020d0410(void);

void func_ov253_020d0344(int *node) {
    int *state = (int *)node[1];

    state[6] = *(int *)(node[0] + 0x2c) * 0x1e / 0xf;
    if (*((unsigned char *)state + 0x30) != 0) {
        return;
    }
    func_0202b450(*(int *)(*(int *)(*(int *)(*state + 0x3bc) + 0x18c) + 0x20),
                  (void *)(*(int *)(*state + 0x3ac) + 0x14));
    state[7] += *(int *)(node[0] + 0x2c);
    if (state[7] < 0xaaa) {
        return;
    }
    *((unsigned char *)state + 0x30) = 1;
    {
        int target = *(int *)(*state + 0x3bc);
        u16 hw = *(u16 *)(target + 0x60);
        *(u16 *)(target + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x80) << 0x18) >> 0x10);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d0410);
}
