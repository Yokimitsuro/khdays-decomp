/* Node initialiser of the ov153 enemy (x3: ov153/154/155): resets the actor's +0x1c6 state and
 * +0x1c7 sub-state request, clears bit 0 of the +0x388 list node's +8 flags, points the state
 * at the actor's +0xb0 pose, +0x74 sphere and the +0x384 item's +0xad byte, sets bits 1/2 of the
 * +0x60 high byte and installs the three slot handlers (tick 020cd570, 020cd754, facing
 * 020cd6d0). */
struct bf { unsigned b : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov154_020d11b0(void);
extern void func_ov154_020d1394(void);
extern void func_ov154_020d1310(void);
void func_ov154_020d10e0(int *node) {
    int *state = (int *)node[1];
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = 0xff;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    state[1] = *state + 0xb0;
    state[2] = *state + 0x74;
    state[3] = *(int *)(*state + 0x384) + 0xad;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    }
    func_0203c634(node, 0, func_ov154_020d11b0);
    func_0203c634(node, 1, func_ov154_020d1394);
    func_0203c634(node, 2, func_ov154_020d1310);
}
