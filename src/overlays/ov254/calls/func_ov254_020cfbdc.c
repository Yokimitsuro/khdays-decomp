/* Run entry: the +0x80 / +0x10 / +0x44 counters clear, the +0x50 start takes the +8 track's +4
 * position and +0x54 the distance to the end (020cd840); the actor plays pose 4 (move 5) or 1 and
 * its +0x430 part motion 3 or 0; in move 5 the +0x460 / +0x464 helpers are started too. The +0x70
 * flag clears and the node moves to 020cfcac. */
typedef unsigned char u8;

extern int func_ov254_020cd840(int *state, int a);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov254_020d4d50(int helper, int mode);
extern void func_ov254_020d5310(int helper);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020cfcac(void);

void func_ov254_020cfbdc(int *node)
{
    int *state = (int *)node[1];

    state[0x20] = 0;
    state[4] = 0;
    state[0x11] = 0;
    state[0x14] = *(int *)(state[2] + 4);
    state[0x15] = func_ov254_020cd840(state, -1) - state[0x14];
    func_ov107_020c9264(*state, *(signed char *)(*state + 0x100 + 0xc6) == 5 ? 4 : 1, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x430), *(signed char *)(*state + 0x100 + 0xc6) == 5 ? 3 : 0, 0);
    if (*(signed char *)(*state + 0x100 + 0xc6) == 5) {
        func_ov254_020d4d50(*(int *)(*state + 0x460), 3);
        func_ov254_020d5310(*(int *)(*state + 0x464));
    }
    *((u8 *)state + 0x70) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020cfcac);
}
