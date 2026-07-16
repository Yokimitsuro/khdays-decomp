extern int func_ov132_020d0b7c(int, int, int, int);
extern int func_ov107_020cb040(int, int, int, int, int);
extern int func_ov107_020c08cc(int, int, int, int, int, int);
extern void func_ov107_020c0b14(int, int);
extern int func_ov132_020d0990(int, int, int, int);
extern int func_ov107_020c09a0(int, int, int, int, int, int);
extern void func_ov107_020c7500(int, int, int);
void func_ov132_020ce114(int param_1, int param_2, int param_3, int param_4) {
    int result;
    if (*(unsigned char *)(param_2 + 2) == 5) {
        switch (*(unsigned char *)(param_2 + 3)) {
        case 0:
            if (*(int *)(*(int *)(param_1 + 0x3c4) + 4) == 0) {
                result = func_ov132_020d0b7c(param_1, *(int *)(*(int *)(param_1 + 0x3c4) + 4),
                                             param_3, param_4);
                *(int *)(*(int *)(param_1 + 0x3c4) + 4) = result;
            }
            result = func_ov107_020cb040(param_1, 0x119, 4, 0,
                                         *(int *)(param_1 + 0x3c0) + 4);
            *(int *)(param_1 + 0x3d0) = result;
            break;
        case 1:
            result = func_ov107_020c08cc(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3c4) + 8),
                                         5, 0, 0x1000, param_2 + 5);
            *(int *)(*(int *)(param_1 + 0x3c4) + 0xc) = result;
            break;
        case 2:
            break;
        case 3:
            result = func_ov107_020c08cc(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3c4) + 0x18),
                                         5, *(unsigned char *)(param_2 + 4), 0x1800, param_2 + 5);
            *(int *)(*(int *)(param_1 + 0x3c4) + 0x1c) = result;
            func_ov107_020c0b14(param_1, 1);
            break;
        case 4:
            result = func_ov132_020d0990(param_1, *(unsigned char *)(param_2 + 3), param_3, param_4);
            *(int *)(*(int *)(param_1 + 0x3c4) + 0x24) = result;
            result = func_ov107_020c09a0(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3c4) + 0x10),
                                         5, param_1 + 0x394, 0, 1);
            *(int *)(*(int *)(param_1 + 0x3c4) + 0x14) = result;
            break;
        }
    }
    func_ov107_020c7500(param_1, param_2, param_3);
}
