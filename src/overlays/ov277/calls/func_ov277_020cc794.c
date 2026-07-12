/* Tail-call the shared handler, zeroing the arg when the +0x1ac busy bit is set. */
extern int func_ov107_020c6980(int, int);
int func_ov277_020cc794(int param_1, int param_2) {
    if (*(unsigned short *)(param_1 + 0x1ac) & 2) param_2 = 0;
    return func_ov107_020c6980(param_1, param_2);
}
