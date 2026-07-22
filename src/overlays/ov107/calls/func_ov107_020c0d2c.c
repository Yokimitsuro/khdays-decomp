/* Dispatches the message to the handler at +0x1c.  Messages whose byte at +2 is zero are
 * gated on func_02030788 first; a missing handler is not an error. */
extern int func_02030788(int a);

void func_ov107_020c0d2c(char *self, unsigned char *msg, int arg) {
    void (*fn)(char *, unsigned char *, int);
    if (msg[2] == 0) {
        if (func_02030788((int)self) == 0) {
            return;
        }
    }
    fn = *(void (**)(char *, unsigned char *, int))(self + 0x1c);
    if (fn == 0) {
        return;
    }
    fn(self, msg, arg);
}
