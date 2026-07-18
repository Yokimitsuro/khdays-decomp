/*
 * func_ov228_020d2230 -- x3. Event hook: on message kind 5 targeting slot 0, arm an emitter, then
 * forward. When msg[2]==5 and msg[3]==0, spawn via 020c09a0(self[0xf], *(self+msg[3]*8+0x390), 0x17,
 * self+0xa0, msg[4], 0) and store the returned handle at self+msg[3]*8+0x394. Always forward the
 * message to the base handler 020c7500(self, msg, arg3).
 *
 * NON-MATCHING: branch-vs-predicate tie on the two-equality guard (-4B). The ROM tests the guards
 * with two independent `cmp; bne tail` (ldrb msg[2]; cmp #5; bne; ldrb msg[3]; cmp #0; bne); mwcc
 * merges them by PREDICATING the second condition (`cmp #5; ldrbeq msg[3]; cmpeq #0; bne`), saving one
 * branch. Everything else -- the msg[3]*8 slot indexing, the 6-arg 020c09a0 spawn, the handle store,
 * and the 020c7500 forward -- is byte-exact. Tried: nested ifs, inverted-condition gotos, volatile
 * msg[2] read; none split the predicated second guard back into its own branch. Checklist clean (ARM;
 * 020c09a0 6-arg, 020c7500 3-arg -- all correct).
 */
extern int  func_ov107_020c09a0(int a, int b, int mode, int anchor, int e, int f);
extern void func_ov107_020c7500(int a, int b, int c);

void func_ov228_020d2230(int self, unsigned char *msg, int arg3) {
    if (msg[2] == 5 && msg[3] == 0) {
        *(int *)(self + msg[3] * 8 + 0x394) = func_ov107_020c09a0(
            *(int *)(self + 0x3c), *(int *)(self + msg[3] * 8 + 0x390), 0x17,
            self + 0xa0, msg[4], 0);
    }
    func_ov107_020c7500(self, (int)msg, arg3);
}
