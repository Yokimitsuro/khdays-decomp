#pragma thumb on
/* func_ov000_02054f08 -- snapshot the current tick into data_0204be1c, ov000. */
extern unsigned long long func_020031d4(void);
extern unsigned long long data_0204be1c;
void func_ov000_02054f08(void) {
    data_0204be1c = func_020031d4();
}
