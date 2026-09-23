/* Blink tick of an ov252 gem: once its +0 part stops animating, the first pass (+0x26 set) clears the
 * flag and fades layers 0, 2, 4 and 1 in (mode 1); afterwards they fade out (mode 2), sound 0x148/0xb
 * plays at the gem's +8 point and the node moves on to 020d3e04. */
extern void func_0203b9fc(int obj, int layer, int mode, int arg);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d3e04(void);

void func_ov252_020d3d10(int *node)
{
    int *state = (int *)node[1];

    if (*(unsigned char *)(*state + 0xad) != 0) {
        return;
    }
    if (*((unsigned char *)state + 0x26) == 1) {
        *((unsigned char *)state + 0x26) = 0;
        func_0203b9fc(*state, 0, 1, 0);
        func_0203b9fc(*state, 2, 1, 0);
        func_0203b9fc(*state, 4, 1, 0);
        func_0203b9fc(*state, 1, 1, 0);
    } else {
        func_0203b9fc(*state, 0, 2, 0);
        func_0203b9fc(*state, 2, 2, 0);
        func_0203b9fc(*state, 4, 2, 0);
        func_0203b9fc(*state, 1, 2, 0);
        func_ov107_020c5af8(state[1], 0x148, 0xb, state + 2);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d3e04);
    }
}
