extern void func_ov008_02077908(int obj, int delta);
extern unsigned short data_0204c18c;

void func_ov008_02077974(int param_1) {
    switch (*(int *)(param_1 + 8)) {
    case 1:
        if (data_0204c18c & 0x40) {
            func_ov008_02077908(param_1, -8);
            return;
        }
        *(int *)(param_1 + 8) = 0;
        return;
    case 2:
        if (data_0204c18c & 0x80) {
            func_ov008_02077908(param_1, 8);
            return;
        }
        *(int *)(param_1 + 8) = 0;
        return;
    default:
        *(int *)(param_1 + 8) = 0;
    }
}
