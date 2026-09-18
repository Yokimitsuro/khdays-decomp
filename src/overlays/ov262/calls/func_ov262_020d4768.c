/* Float height tick of the ov261 enemy (and its byte-identical twin): with a +0x2c carrier the
 * +0x1c anchor follows it (func_ov262_020d3f88) and the +0x34 lift eases by a fiftieth towards
 * the carrier's height plus 0x800 above the +4 position; otherwise it eases towards 0x1800 above
 * the actor's +0x13c height. */
extern void func_ov262_020d3f88(void *anchor, int *carrier, int *pos);

void func_ov262_020d4768(int *node)
{
    int *state = (int *)node[1];
    int d;

    if (state[0xb] != 0) {
        func_ov262_020d3f88(state + 7, (int *)state[0xb], (int *)state[1]);
        d = *(int *)(state[0xb] + 4) + 0x800 - *(int *)(state[1] + 4);
        state[0xd] += d / 50;
        return;
    }
    d = 0x1800 - *(int *)(*state + 0x13c);
    state[0xd] += d / 50;
}
