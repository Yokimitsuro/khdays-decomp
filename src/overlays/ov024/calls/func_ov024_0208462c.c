/* func_ov024_0208462c -- conditionally run the two ov024 teardown steps, ov024. */
extern void func_ov024_02083e28(void);
extern void func_ov024_02083f44(void);
void func_ov024_0208462c(int doA, int doB) {
    if (doA != 0) {
        func_ov024_02083e28();
    }
    if (doB != 0) {
        func_ov024_02083f44();
    }
}
