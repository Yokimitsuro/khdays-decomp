/* Next-waypoint step of the ov243 enemy (and its byte-identical twins): with a +0x398 waypoint table and a
 * +0x39c count on the actor, the +0x24 index advances modulo the count and +0x1c points at the
 * 20-byte entry; then sub-state 3 is requested and the slot released. The remainder is the
 * high half of func_02020400's 64-bit return; the index is stored and re-read (a local for the
 * remainder hoists the 0x14 above the table load). */
extern long long func_02020400(int a, int b);
extern void func_0203c634(int node, int slot, void *cb);

void func_ov243_020d444c(int node)
{
    int *state = *(int **)(node + 4);
    if (*(int *)(*state + 0x398) != 0 && *(int *)(*state + 0x39c) != 0) {
        state[9] = (int)(func_02020400(state[9] + 1, *(int *)(*state + 0x39c)) >> 32);
        state[7] = *(int *)(*state + 0x398) + state[9] * 0x14;
    }
    *(unsigned char *)(*state + 0x1c7) = 3;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
