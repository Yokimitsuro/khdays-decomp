/* Single-case switch: `msg[2] == 5 && msg[3] == 0` lets mwcc if-convert the second test
 * into the first (ldrbeq/cmpeq); the ROM branches on both.
 * func_ov107_020cb040 takes FIVE arguments (the fifth on the stack); Ghidra shows six. */
extern int  func_ov107_020cb040();
extern void func_ov118_020cfe08(int self);
extern void func_ov107_020c7500(int self, int msg, int c);

void func_ov118_020cfe24(int self, int msg, int c) {
    switch (*(unsigned char *)(msg + 2)) {
    case 5:
        if (*(unsigned char *)(msg + 3) == 0) {
            if (*(int *)(self + 0x390) == 0) {
                *(int *)(self + 0x390) = func_ov107_020cb040(self, 0x120, 5, 1, self + 0xa0);
            } else {
                func_ov118_020cfe08(self);
            }
        }
        break;
    }
    func_ov107_020c7500(self, msg, c);
}
