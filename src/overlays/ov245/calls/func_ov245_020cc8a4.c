/* func_ov245_020cc8a4 -- message filter: a message with byte 2 clear while the actor sits in
 * state 2 and whose byte 4 has bit 0 clear is a state change: the current kind byte (+0x1c6) is
 * remembered at +0x1c8, the message's byte 5 becomes the new kind and the change handler
 * (020c49b8) runs; anything else goes to the default handler (020c7500). The third argument is
 * forwarded untouched. */
extern int func_ov107_020c49b8(int self, unsigned char *msg, int extra);
extern int func_ov107_020c7500(int self, unsigned char *msg, int extra);

int func_ov245_020cc8a4(int self, unsigned char *msg, int extra) {
    if (msg[2] == 0 && *(int *)(self + 0x50) == 2 && (msg[4] & 1) == 0) {
        *(signed char *)(self + 0x1c8) = *(signed char *)(self + 0x1c6);
        *(unsigned char *)(self + 0x1c6) = msg[5];
        return func_ov107_020c49b8(self, msg, extra);
    }
    return func_ov107_020c7500(self, msg, extra);
}
