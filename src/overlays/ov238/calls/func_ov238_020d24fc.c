/* Roar entry of the ov238 actor: +0x2e and the +0x31 cue are set, +0x20 clears, sound 0x12e/0x10
 * plays at the +8 point and the timed step (020d0f54, 0x10 frames, 6) leads on to 020d2560. */
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_ov238_020d0f54(int *node, int param_2, int param_3, int param_4, void *cb);
extern void func_ov238_020d2560(void);

void func_ov238_020d24fc(int *node)
{
    int *state = (int *)node[1];

    *((unsigned char *)state + 0x2e) = 1;
    *((unsigned char *)state + 0x31) = 1;
    state[8] = 0;
    func_ov107_020c5af8(*state, 0x12e, 0x10, (void *)state[2]);
    func_ov238_020d0f54(node, 0x10, 6, 0, func_ov238_020d2560);
}
