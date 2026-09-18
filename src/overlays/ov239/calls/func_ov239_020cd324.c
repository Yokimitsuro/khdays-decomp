/* Attack entry of the ov239 enemy: raises bit 0 of the actor's +0x1ae, drops bit 6 of the
 * +0x60 high byte, resets the +0x2c timer and the +0x32/+0x30 bytes, and configures sub-state 5
 * (part action 1, flag 0) before handing off to cd3a0. */
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov239_020cc9f0(int *node, int anim, int action, int flag, void *next);
extern void func_ov239_020cd3a0(int *node);

void func_ov239_020cd324(int *node)
{
    int *state = (int *)node[1];

    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
    state[0xb] = 0;
    *(unsigned char *)((char *)state + 0x32) = 0;
    *(unsigned char *)(state + 0xc) = 0;
    func_ov239_020cc9f0(node, 5, 1, 0, func_ov239_020cd3a0);
}
