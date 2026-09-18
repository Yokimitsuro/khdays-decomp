/* func_ov245_020cdcb4 -- dive entry: resets the actor (020cce08), starts motion 0 of the +0x4c8
 * anchor, hands the +0x24 value to the +0x430 item (020d1dc8), then from the height gap (020ccda4, flat) computes the
 * fraction of 5.0 still to fall (clamped 0..5.0) and its ratio (FX_Inv against 5.0) scaled by
 * 0.925 into the +0x20 z speed (x/y zero), and hands the node to 020cd9f4. */
extern void func_ov245_020cce08(int actor);
extern void func_ov107_020c9ee8(int item, int motion, int flag);
extern void func_ov245_020d1dc8(int item, int a);
extern int func_ov245_020ccda4(int *node, int flat);
extern int FX_Inv(int num, int den);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020cdd60(void);

void func_ov245_020cdcb4(int *node) {
    int *state = (int *)node[1];
    int rest;

    func_ov245_020cce08(*state);
    func_ov107_020c9ee8(*(int *)(*state + 0x4c8), 0, 1);
    func_ov245_020d1dc8(*(int *)(*state + 0x430), state[9]);
    rest = 0x5000 - func_ov245_020ccda4(node, 1);
    if (rest > 0x5000) {
        rest = 0x5000;
    } else if (rest < 0) {
        rest = 0;
    }
    rest = FX_Inv(rest, 0x5000);
    state[6] = 0;
    state[7] = 0;
    state[8] = (int)(((long long)rest * 0xed0 + 0x800) >> 12);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020cdd60);
}
