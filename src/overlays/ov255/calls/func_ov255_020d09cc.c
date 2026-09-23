/* Ring tick of an ov255 state: the +0x50 timer accumulates the owner's rate and at 2.13 reaction
 * +0x3f8 mode 0x13 fires once at the +0x3b8 part's point (+0x65). Once the +0xc idle byte clears,
 * the nine +0x3f0 ring items are placed around that point at 2*pi/9 steps (func_ov255_020d1710,
 * turned by the +0x1c orientation), animation 0x21 plays, the +0x3a4 part plays motion 0x1c,
 * reaction mode 0x14 fires at the point and the tick hands over to func_ov255_020d0ae8. */
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov255_020d1710(int item, void *at, void *q, int angle);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov255_020d0ae8(int *node);

void func_ov255_020d09cc(int *node)
{
    int *state = (int *)node[1];
    int i;

    state[0x14] += *(int *)(node[0] + 0x2c);
    if (*((unsigned char *)state + 0x65) == 0 && state[0x14] >= 0x2222) {
        func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x3f8), 0x13, (void *)(*(int *)(*state + 0x3b8) + 0x14));
        *((unsigned char *)state + 0x65) = 1;
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    for (i = 0; i < 9; i++) {
        func_ov255_020d1710(((int *)*(int *)(*state + 0x3f0))[i], (void *)(*(int *)(*state + 0x3b8) + 0x14), state + 7, i * 0x6488 / 9);
    }
    func_ov107_020c9264(*state, 0x21, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a4), 0x1c, 0);
    func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x3f8), 0x14, (void *)(*(int *)(*state + 0x3b8) + 0x14));
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020d0ae8);
}
