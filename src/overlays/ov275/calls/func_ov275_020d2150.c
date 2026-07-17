/* Handle a type-5 resource message (x4: ov206/207/274/275). Sub-op msg[3] says which
 * slot of the actor's resource block (+0x3e0) the payload at msg+5 belongs to: 0 spawns
 * and links a node, 1/4/5 bind a 0x17 resource to the slot's handle at +8/+0x18/+0x20 and
 * cache the result at +0xc/+0x1c/+0x24; sub-op 5 additionally arms the block. Sub-ops 2
 * and 3 carry no payload of their own. Either way the message continues to the generic
 * handler.
 *
 * Case order from tools/switchorder.py: 0, 1, 4, 5, then {2,3} sharing the default's body
 * -- i.e. 2 and 3 are simply not written. Matched byte-exact on the first compile.
 *
 * Note func_ov275_020d2620 is called with FOUR arguments and the ROM sets NONE of them:
 * self, msg[3] (the switch value itself, still live in r1), p3 and p4 are all already in
 * place. And ov107_020c08cc takes SIX -- the last two go on the stack. */
extern int func_ov275_020d2620(int self, int a, int b, int c);
extern int func_ov107_020c08cc(int a, int b, int c, int d, int e, void *f);
extern void func_ov107_020c0b14(int self, int a);
extern void func_ov107_020c7500(int self, void *msg, int c);

void func_ov275_020d2150(int self, unsigned char *msg, int p3, int p4) {
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            *(int *)(*(int *)(self + 0x3e0) + 4) = func_ov275_020d2620(self, msg[3], p3, p4);
            break;
        case 1:
            *(int *)(*(int *)(self + 0x3e0) + 0xc) =
                func_ov107_020c08cc(*(int *)(self + 0x3c),
                                    *(int *)(*(int *)(self + 0x3e0) + 8),
                                    0x17, 0, 0x1000, msg + 5);
            break;
        case 4:
            *(int *)(*(int *)(self + 0x3e0) + 0x1c) =
                func_ov107_020c08cc(*(int *)(self + 0x3c),
                                    *(int *)(*(int *)(self + 0x3e0) + 0x18),
                                    0x17, 0, 0x1000, msg + 5);
            break;
        case 5:
            *(int *)(*(int *)(self + 0x3e0) + 0x24) =
                func_ov107_020c08cc(*(int *)(self + 0x3c),
                                    *(int *)(*(int *)(self + 0x3e0) + 0x20),
                                    0x17, 0, 0x1000, msg + 5);
            func_ov107_020c0b14(self, 1);
            break;
        }
    }
    func_ov107_020c7500(self, msg, p3);
}
