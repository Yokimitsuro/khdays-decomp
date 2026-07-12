/* Return 0 if param_1 is negative, or if any active entry (byte +2 set) other
 * than index func_ov008_0207b138(param_1) has its signed byte at +4 equal to
 * param_1; otherwise 1. */
extern int func_ov008_0207b138(int obj);

int func_ov008_0207bddc(int param_1, int param_2) {
    unsigned char i;
    unsigned char self;
    if (param_1 < 0) return 0;
    self = (unsigned char)func_ov008_0207b138(param_1);
    for (i = 0; i < 4; i++) {
        if (*(unsigned char *)(param_2 + i * 8 + 2) != 0 && i != self) {
            if (param_1 == *(signed char *)(param_2 + i * 8 + 4)) {
                return 0;
            }
        }
    }
    return 1;
}
