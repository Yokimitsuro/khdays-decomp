/* func_ov009_0204cb4c -- probe slot 0 readiness, ov009. Returns -2 if func_ov009_0204df00
 * reports the slot busy, else 0. */
extern int func_ov009_0204df00(int slot);
int func_ov009_0204cb4c(void) {
    int r = 0;
    if (func_ov009_0204df00(0) != 0) {
        r = -2;
    }
    return r;
}
