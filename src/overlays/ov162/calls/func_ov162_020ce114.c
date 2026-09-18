/* func_ov162_020ce114: spawn-message handler of the ov161 enemy (x2), variant of the matched ov163 sibling (sub 3 uses entry 6 with weight 0x2000; sub 4 also attaches entry 4 to the +0x394 placement, spawns the +0x2c child and registers effect 0x152 mode 7 into +0x3d4). */
/* func_ov162_020ce114: ported from a matched sibling family (same shape, constants and offsets adjusted). */
extern int func_ov162_020ce600(int, int, int, int);
extern int func_ov107_020cb040(int, int, int, int, int);
extern int func_ov107_020c08cc(int, int, int, int, int, int);
extern void func_ov107_020c0b14(int, int);
extern int func_ov162_020ce414(int, int, int, int);
extern int func_ov107_020c09a0(int, int, int, int, int, int);
extern int func_ov162_020ce7fc(int);
extern void func_ov107_020c7500(int, int, int);
void func_ov162_020ce114(int param_1, int param_2, int param_3, int param_4) {
    int result;
    if (*(unsigned char *)(param_2 + 2) == 0x5) {
        switch (*(unsigned char *)(param_2 + 3)) {
        case 0:
            if (*(int *)(*(int *)(param_1 + 0x3c4) + 4) == 0) {
                result = func_ov162_020ce600(param_1, *(int *)(*(int *)(param_1 + 0x3c4) + 4),
                                             param_3, param_4);
                *(int *)(*(int *)(param_1 + 0x3c4) + 4) = result;
            }
            result = func_ov107_020cb040(param_1, 0x152, 4, 0,
                                         *(int *)(param_1 + 0x3c0) + 4);
            *(int *)(param_1 + 0x3d0) = result;
            break;
        case 1:
            result = func_ov107_020c08cc(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3c4) + 8),
                                         0x5, 0, 0x1000, param_2 + 5);
            *(int *)(*(int *)(param_1 + 0x3c4) + 0xc) = result;
            break;
        case 2:
            break;
        case 3:
            result = func_ov107_020c08cc(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3c4) + 0x18),
                                         0x5, *(unsigned char *)(param_2 + 4), 0x2000, param_2 + 5);
            *(int *)(*(int *)(param_1 + 0x3c4) + 0x1c) = result;
            func_ov107_020c0b14(param_1, 1);
            break;
        case 4:
            result = func_ov162_020ce414(param_1, *(unsigned char *)(param_2 + 3), param_3, param_4);
            *(int *)(*(int *)(param_1 + 0x3c4) + 0x24) = result;
            result = func_ov107_020c09a0(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3c4) + 0x10),
                                         0x5, param_1 + 0x394, 0, 1);
            *(int *)(*(int *)(param_1 + 0x3c4) + 0x14) = result;
            result = func_ov162_020ce7fc(param_1);
            *(int *)(*(int *)(param_1 + 0x3c4) + 0x2c) = result;
            result = func_ov107_020cb040(param_1, 0x152, 7, 0,
                                         *(int *)(param_1 + 0x3c0) + 4);
            *(int *)(param_1 + 0x3d4) = result;
            break;
        }
    }
    func_ov107_020c7500(param_1, param_2, param_3);
}
