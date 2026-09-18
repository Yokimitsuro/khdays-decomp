/* Message handler of the ov284 enemy: a "spawned" message (kind 5) starts one of the +0x3b0
 * slot table's subitems -- sub 1 the +8 one (mode 0xd, at the +0x3a4 item's +4 point, flags
 * (0, 1)) into +0xc, sub 0 the first (mode 5, weight 0x1000, payload) into +4, sub 2 the +0x10
 * one (mode 5, weight 0x1000, payload) into +0x14, sub 6 the +0x18 one (mode 5, at the +0x3a4
 * item's +4 point) into +0x1c; sub 3 runs cd294 on the actor (the original r0 is still live, which is what parks the switch value in r1). The base handler always runs. */
extern int func_ov107_020c08cc(int, int, int, int, int, int);
extern int func_ov107_020c09a0(int, int, int, int, int, int);
extern void func_ov107_020c7500(int, int, int);
extern void func_ov284_020cd294(int);

void func_ov284_020cc400(int param_1, int param_2, int param_3, int param_4) {
    int result;
    if (*(unsigned char *)(param_2 + 2) == 5) {
        switch (*(unsigned char *)(param_2 + 3)) {
        case 1:
            result = func_ov107_020c09a0(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3b0) + 8),
                                         0xd, *(int *)(param_1 + 0x3a4) + 4, 0, 1);
            *(int *)(*(int *)(param_1 + 0x3b0) + 0xc) = result;
            break;
        case 0:
            result = func_ov107_020c08cc(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3b0)),
                                         5, 0, 0x1000, param_2 + 5);
            *(int *)(*(int *)(param_1 + 0x3b0) + 4) = result;
            break;
        case 2:
            result = func_ov107_020c08cc(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3b0) + 0x10),
                                         5, 0, 0x1000, param_2 + 5);
            *(int *)(*(int *)(param_1 + 0x3b0) + 0x14) = result;
            break;
        case 6:
            result = func_ov107_020c09a0(*(int *)(param_1 + 0x3c),
                                         *(int *)(*(int *)(param_1 + 0x3b0) + 0x18),
                                         5, *(int *)(param_1 + 0x3a4) + 4, 0, 0);
            *(int *)(*(int *)(param_1 + 0x3b0) + 0x1c) = result;
            break;
        case 3:
            func_ov284_020cd294(param_1);
            break;
        }
    }
    func_ov107_020c7500(param_1, param_2, param_3);
}
