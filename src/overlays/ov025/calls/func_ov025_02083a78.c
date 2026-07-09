extern int func_ov025_02082c68();
extern int data_ov025_020b37e0;

void func_ov025_02083a78(void) {
    int (*f)(void) = ((int (**)(void))&data_ov025_020b37e0)[func_ov025_02082c68()];
    if (f != 0) {
        f();
    }
}
