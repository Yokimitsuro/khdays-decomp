/* Twin of Ov008_HandleElementTap for the "release" transition: state 0 with phase bits 0xd0 clear
 * and a non-zero variant switches the element to variant 0 and chirps; state 1 sets the pending
 * flag +0x64 (if clear) and chirps. */
extern void func_ov008_02067970(int *obj, int variant, int state);
extern void func_02033b78(int a, int b);
extern unsigned short data_0204c18c;

void func_ov008_020686a0(int *param_1) {
    int variant = *param_1;
    if (param_1[0x8f] != 0) {
        return;
    }
    switch (param_1[1]) {
    case 0:
        if (data_0204c18c & 0xd0) {
            return;
        }
        if (variant == 0) {
            return;
        }
        *param_1 = 0;
        func_ov008_02067970(param_1, variant, 0);
        func_02033b78(0, 0);
        break;
    case 1:
        if (param_1[0x19] != 0) {
            return;
        }
        param_1[0x19] = 1;
        func_02033b78(0, 0);
        break;
    }
}
