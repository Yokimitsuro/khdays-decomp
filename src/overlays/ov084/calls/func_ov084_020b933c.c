/* func_ov084_020b933c -- enemy state tick, head of a 4-member family (ARM).
 * State 1 accumulates the frame delta at +0x10c and, past 0xa000, notifies func_ov084_020b94e8
 * and moves to state 2. State 2 waits for func_02030788 to go quiet, then runs 020b4504 and
 * arms the follow-up through func_0202a818. Returns 1 only on the path that took the state-2 exit.
 *
 * Parked for 8 bytes as "the ROM loads the switch value into r2 and mwcc into r0; the two cmp
 * inherit the register", with five source shapes ruled out and a guess that r0 was being reserved
 * as the return register. The real reason r0 is untouchable is much simpler: `node` is STILL IN
 * r0 at that point (nothing has written r0 since entry) because func_ov084_020b94e8 takes it as
 * its argument -- the extern here said `(void)` while the definition takes one parameter.
 * Passing it costs literally nothing (mwcc sees the value is already in place and emits no `mov`),
 * which is exactly why the call site looks argument-free, and it makes r0 live so the switch value
 * has to go to r2.
 *
 * Worth remembering as a shape: an argument that is ALREADY in its register emits no instruction,
 * so a dropped argument of that kind is invisible in the size and shows up only as "one register
 * is wrong". tools/audit_extern_sig.py finds them without any analysis.
 */
extern void func_ov084_020b94e8(int *node);
extern int func_02030788(void);
extern void func_ov084_020b93e4(int *node);
extern int func_0202a818(int a, int b);

int func_ov084_020b933c(int *node, int dt) {
    int r = 0;
    switch (node[0]) {
    default:
        break;
    case 1:
        node[0x43] += dt;
        if (node[0x43] >= 0xa000) {
            func_ov084_020b94e8(node);
            node[0] = 2;
        }
        break;
    case 2:
        if (func_02030788() == 0) {
            func_ov084_020b93e4(node);
        }
        if (func_0202a818((int)node + 4, dt) != 0) {
            node[0] = 0;
        }
        break;
    }
    if (node[0] == 0) r = 1;
    return r;
}
