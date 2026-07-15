/* func_ov009_0204d7f4 -- dispatch the current menu command, ov009. Looks up the handler
 * for the active command (func_ov009_0204cb84) in the jump table data_ov009_02055f88 and
 * calls it if present. */
extern int func_ov009_0204cb84(void);
extern void (*data_ov009_02055f88[])(void);
void func_ov009_0204d7f4(void) {
    void (*handler)(void) = data_ov009_02055f88[func_ov009_0204cb84()];
    if (handler != 0) {
        handler();
    }
}
