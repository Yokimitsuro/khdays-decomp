/* Project the 020c5bc4 world position into +0..+0xc of out, halving toward the anchor per mode. */
extern int func_ov025_020884c8();
int *func_ov025_020878dc(int param_1, int *param_2, int param_3) {
    int *v = (int *)func_ov025_020884c8(param_1, param_3);
    param_2[0] = v[0] >> 12;
    param_2[1] = v[1] >> 12;
    param_2[2] = *(unsigned short *)(param_3 + 0x1c);
    param_2[3] = *(unsigned short *)(param_3 + 0x1e);
    switch (*(int *)(param_3 + 0x20)) {
    case 0:
        param_2[0] -= param_2[2] / 2;
        param_2[1] -= param_2[3] / 2;
        break;
    case 2:
        param_2[0] -= param_2[2] / 2;
        break;
    }
    return param_2;
}
