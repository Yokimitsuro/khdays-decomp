/* Target pick of the ov218 actor: the nearest target (020cab14) goes to +0x390; without one the next
 * move is 2 and the node ends. Otherwise +0x48 is -1, +0x60 clears, a random side (+0x5c) is drawn,
 * the +0x18 wait is rolled between +0x224 and +0x228 and the node moves on to 020ccfa8. */
extern int func_ov107_020cab14(int actor, int *distOut);
extern int func_02023eb4(int bound);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov218_020ccfa8(void);

void func_ov218_020ccf04(int *node)
{
    int *state = (int *)node[1];
    int lo;
    int span;

    *(int *)(*state + 0x390) = func_ov107_020cab14(*state, 0);
    if (*(int *)(*state + 0x390) == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x12] = -1;
    state[0x18] = 0;
    *((unsigned char *)state + 0x5c) = func_02023eb4(2);
    lo = *(int *)(*state + 0x224);
    span = *(int *)(*state + 0x228) - lo;
    if (span < 0) {
        span = -span;
    }
    state[6] = lo + func_02023eb4(span + 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov218_020ccfa8);
}
