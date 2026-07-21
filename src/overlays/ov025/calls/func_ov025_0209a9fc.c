/* React to a tap on a two-state UI element: in state 0, if the phase byte's 0xe0 bits are clear
 * and the element is not already variant 2, switch it to variant 2 and chirp; in state 1, if the
 * pending flag (+0x64) is set, clear it and chirp. */
extern void func_ov025_02099d50(int *obj, int variant, int state);
extern void func_02033b78(int a, int b);
extern unsigned short data_0204c18c;

void func_ov025_0209a9fc(int *param_1) {
    int variant = *param_1;
    if (param_1[0x8f] != 0) {
        return;
    }
    switch (param_1[1]) {
    case 0:
        if (data_0204c18c & 0xe0) {
            return;
        }
        if (variant == 2) {
            return;
        }
        *param_1 = 2;
        func_ov025_02099d50(param_1, variant, 2);
        func_02033b78(0, 0);
        break;
    case 1:
        if (param_1[0x19] == 0) {
            return;
        }
        param_1[0x19] = 0;
        func_02033b78(0, 0);
        break;
    }
}
