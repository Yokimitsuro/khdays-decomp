/* Message handler of the ov230 enemy (+0x1c): kind-5 message 0 plays effect pair 0 (+0x38c
 * resource, handle kept at +0x390, kind 0x17) on the +0xa0 pose with the message's +4 byte; every
 * message then goes to the common handler. (`if (msg[3] == 0)` inside a one-case switch keeps the
 * ROM's two branches instead of an if-converted pair.) */
extern int  func_ov107_020c09a0(int a, int b, int mode, int anchor, int e, int f);
extern void func_ov107_020c7500(int a, int b, int c);

void func_ov230_020d5df4(int self, unsigned char *msg, int arg3) {
    switch (msg[2]) {
    case 5:
        if (msg[3] == 0) {
            *(int *)(self + msg[3] * 8 + 0x390) = func_ov107_020c09a0(
                *(int *)(self + 0x3c), *(int *)(self + msg[3] * 8 + 0x38c), 0x17,
                self + 0xa0, msg[4], 0);
        }
        break;
    }
    func_ov107_020c7500(self, (int)msg, arg3);
}
