/* func_ov203_020d3b78: ported from a matched sibling family (same shape, constants and offsets adjusted). */
extern int func_ov203_020d65a8(int, int, int, int);
extern int func_ov107_020cb040(int, int, int, int, int);
extern int func_ov107_020c08cc(int, int, int, int, int, int);
extern void func_ov107_020c0b14(int, int);
extern int func_ov203_020d63bc(int, int, int, int);
extern int func_ov107_020c09a0(int, int, int, int, int, int);
extern void func_ov107_020c7500(int, int, int);
void func_ov203_020d3b78(int param_1, int param_2, int param_3, int param_4) {
    int result;
    if (*(unsigned char *)(param_2 + 2) == 5) {
        switch (*(unsigned char *)(param_2 + 3)) {
        case 0:
            if (*(int *)(*(int *)(param_1 + 0x3dc) + 4) == 0) {
                result = func_ov203_020d65a8(param_1, *(int *)(*(int *)(param_1 + 0x3dc) + 4),
                                             param_3, param_4);
                *(int *)(*(int *)(param_1 + 0x3dc) + 4) = result;
            }
            result = func_ov107_020cb040(param_1, 0x156, 4, 0,
                                         *(int *)(param_1 + 0x3d8) + 4);
            *(int *)(param_1 + 0x410) = result;
            break;
        case 1:
            result = func_ov107_020c08cc(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3dc) + 8),
                                         5, 0, 0x1000, param_2 + 5);
            *(int *)(*(int *)(param_1 + 0x3dc) + 0xc) = result;
            break;
        case 2:
            break;
        case 3:
            result = func_ov107_020c08cc(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3dc) + 0x18),
                                         5, *(unsigned char *)(param_2 + 4), 0x3000, param_2 + 5);
            *(int *)(*(int *)(param_1 + 0x3dc) + 0x1c) = result;
            func_ov107_020c0b14(param_1, 1);
            break;
        case 4:
            result = func_ov203_020d63bc(param_1, *(unsigned char *)(param_2 + 3), param_3, param_4);
            *(int *)(*(int *)(param_1 + 0x3dc) + 0x24) = result;
            result = func_ov107_020c09a0(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3dc) + 0x10),
                                         5, param_1 + 0x3e4, 0, 1);
            *(int *)(*(int *)(param_1 + 0x3dc) + 0x14) = result;
            break;
        }
    }
    func_ov107_020c7500(param_1, param_2, param_3);
}
