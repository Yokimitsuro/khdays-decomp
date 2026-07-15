#pragma thumb on
/* func_ov009_02055f34 -- snapshot the current tick into data_0204be1c, ov009 (byte-identical twin of an ov000 helper). */
extern unsigned long long func_020031d4(void);
extern unsigned long long data_0204be1c;
void func_ov009_02055f34(void) {
    data_0204be1c = func_020031d4();
}
