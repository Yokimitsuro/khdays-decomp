extern short func_02020a9c(void);
extern int func_ov023_02084018(void);
/* Script predicate: true (0) only if the current opcode is 0xc and func_02084018 is non-zero. */
int func_ov023_02086ee4(void) {
    if (func_02020a9c() != 0xc) {
        return 1;
    }
    if (func_ov023_02084018() == 0) {
        return 1;
    }
    return 0;
}
