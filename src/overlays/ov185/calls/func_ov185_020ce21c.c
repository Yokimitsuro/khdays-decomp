/*
 * func_ov185_020ce21c -- x3. Event hook: on message kind 5, create or destroy a sub-object, then
 * forward. When msg[2]==5, switch on msg[3]: case 0 creates via 020cb040(self, 0x120, 5, 1, self+0xa0)
 * and stores the handle at self+0x400; case 1 destroys the handle at self+0x400 (if non-null) via
 * 020cb100 and clears it. Always forward the message to the base handler 020c7500(self, msg, arg3).
 */
extern int  func_ov107_020cb040(int a, int b, int c, int d, int e);
extern void func_ov107_020cb100(int a);
extern void func_ov107_020c7500(int a, int b, int c);

void func_ov185_020ce21c(int self, unsigned char *msg, int arg3) {
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            *(int *)(self + 0x400) = func_ov107_020cb040(self, 0x120, 5, 1, self + 0xa0);
            break;
        case 1:
            if (*(int *)(self + 0x400) != 0) {
                func_ov107_020cb100(*(int *)(self + 0x400));
                *(int *)(self + 0x400) = 0;
            }
            break;
        }
    }
    func_ov107_020c7500(self, (int)msg, arg3);
}
