/*
 * func_ov158_020cebdc -- x3. Event hook: on message kind 5 targeting slot 0, arm an emitter from the
 * message payload, then forward. When msg[2]==5 and msg[3]==0, spawn via 020c08cc(self[0xf],
 * *(self+0x390), 5, msg[4], 0x1000, &msg[5]) and store the handle at *(self+0x390)+4. Always forward
 * the message to the base handler 020c7500(self, msg, arg3).
 *
 * NON-MATCHING: the two-equality-guard branch-vs-predicate tie (-4B) -- identical class to the parked
 * func_ov228_020d2230 (see deferred-ties.md). The ROM tests the guards with two independent
 * `cmp; bne tail` (ldrb msg[2]; cmp #5; bne; ldrb msg[3]; cmp #0; bne); mwcc merges them by PREDICATING
 * the second condition (`cmp #5; ldrbeq msg[3]; cmpeq #0; bne`), saving one branch. The 020c08cc spawn,
 * the handle store, and the 020c7500 forward are all byte-exact. Tried: nested ifs, inverted-condition
 * gotos -- neither splits the merged guard. Checklist clean (ARM; 020c08cc 6-arg, 020c7500 3-arg).
 */
extern int  func_ov107_020c08cc(int a, int b, int mode, int c, int d, int e);
extern void func_ov107_020c7500(int a, int b, int c);

void func_ov158_020cebdc(int self, unsigned char *msg, int arg3) {
    if (msg[2] == 5) {
        if (msg[3] == 0) {
            *(int *)(*(int *)(self + 0x390) + 4) = func_ov107_020c08cc(
                *(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x390)), 5, msg[4], 0x1000,
                (int)(msg + 5));
        }
    }
    func_ov107_020c7500(self, (int)msg, arg3);
}
