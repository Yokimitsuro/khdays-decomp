/*
 * func_ov245_020cf230 -- x3. Node update entry: fire an optional callback, tick, forward.
 * If bit1 of self[0x40] is set and the callback self[0xc] is non-null, invoke it as cb(self, 0).
 * Always run 0203c7ac(self[0x384], 0). If self[0x50] == 1, forward to 020cf978(self[0x214], arg2).
 */
extern void func_0203c7ac(int a, int b);
extern void func_ov245_020cf978(int p, int arg2);

void func_ov245_020cf230(int self, int arg2) {
    int *s = (int *)self;

    if (s[0x10] << 30 >> 31 && s[3] != 0) {
        ((void (*)(int, int))s[3])(self, 0);
    }
    func_0203c7ac(s[0xe1], 0);
    if (s[0x14] == 1) {
        func_ov245_020cf978(s[0x85], arg2);
    }
}
