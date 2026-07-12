/* For indices 1..0x276, when func_ov008_0205db98(param_1, i) is nonzero, notify
 * func_020235a8 with the message id i+0x37c9. */
extern int func_ov008_0205db98(int obj, int index);
extern void func_020235a8(int message);

void func_ov008_02065540(int param_1) {
    int i;
    for (i = 1; i < 0x277; i++) {
        if (func_ov008_0205db98(param_1, i) != 0) {
            func_020235a8(i + 0x37c9);
        }
    }
}
