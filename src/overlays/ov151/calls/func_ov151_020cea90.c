/* Summon wait of the ov151 enemy (and its byte-identical twin): waits for the +0x48 busy byte to
 * clear; with three summons counted (+0x38), or none of the three +0x3c8 items free (+0x60 low
 * bit clear), sub-state 2 is requested and the state ends; otherwise the tick returns to the
 * summon state (ce930). */
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov151_020ce930(void);

void func_ov151_020cea90(int *node)
{
    int *state = (int *)node[1];
    int i;
    int actor;

    if (*(unsigned char *)state[0x12] != 0) {
        return;
    }
    if (state[0xe] >= 3) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    for (i = 0; i < 3; i++) {
        if ((((struct hw60 *)((*(int **)(*state + 0x3c8))[i] + 0x60))->lo & 1) == 0) {
            func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov151_020ce930);
            return;
        }
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
