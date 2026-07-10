extern int func_ov022_0209405c(unsigned char *p);
extern int func_ov022_02094174(unsigned char *p);

int func_ov022_020940a0(unsigned char *param_1, int param_2) {
    if (func_ov022_0209405c(param_1) == 0) {
        return 0;
    }
    if (param_2 >= 0) {
        if ((*param_1 & 4) == 0) {
            if (*(int *)(param_1 + 0x114) > param_2) {
                return 0;
            }
        } else {
            if (0x6000 < param_2 && *(int *)(param_1 + 0x114) > param_2) {
                return 0;
            }
        }
    }
    if (func_ov022_02094174(param_1) == 0 && 0 < *(int *)(param_1 + 0x10c)) {
        return 0;
    }
    return 1;
}
