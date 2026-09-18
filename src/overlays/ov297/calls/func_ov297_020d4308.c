/* Init of the ov297 enemy's state machine: resets the actor's sub-state (+0x1c6 0, +0x1c7
 * none), clears bit 0 of the +0x38c part's +8 word, points the +8 position at the actor's +0xb0,
 * sets bits 1-2 of the +0x60 high byte, clears the +0x90 byte and the four +0x64 slots (-1),
 * marks +0x91 with 0/1 when the scene's +0x78 world is mode 10/11, and registers the slot 1/0/2 ticks
 * (d46e4 / d441c / d45c0). */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct LowByte32 { unsigned bits : 8; };

extern int func_ov002_02072754(int world);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov297_020d46e4(int *node);
extern void func_ov297_020d441c(int *node);
extern void func_ov297_020d45c0(int *node);

void func_ov297_020d4308(int *node)
{
    int *state = (int *)node[1];
    int i;
    int scene = *(int *)(*state + 4);
    unsigned short *hw;
    unsigned int h;

    *(unsigned char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    ((struct LowByte32 *)(*(int *)(*state + 0x38c) + 8))->bits &= ~1;
    state[2] = *state + 0xb0;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    *(unsigned char *)(state + 0x24) = 0;
    for (i = 0; i < 4; i++) {
        state[0x19 + i] = -1;
    }
    switch (func_ov002_02072754(*(int *)(scene + 0x78))) {
    case 10:
        *(signed char *)((char *)state + 0x91) = 0;
        break;
    case 11:
        *(signed char *)((char *)state + 0x91) = 1;
        break;
    default:
        *(signed char *)((char *)state + 0x91) = -1;
        break;
    }
    func_0203c634(node, 1, func_ov297_020d46e4);
    func_0203c634(node, 0, func_ov297_020d441c);
    func_0203c634(node, 2, func_ov297_020d45c0);
}
