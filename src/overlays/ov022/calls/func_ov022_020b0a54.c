extern unsigned int func_ov022_020b0b10(int a);
extern void func_ov022_020b064c(int a);

struct flags_020b0a54 {
    unsigned int lo3 : 3;
    unsigned int b3 : 1;
    unsigned int b4 : 1;
    unsigned int hi : 27;
};

void func_ov022_020b0a54(unsigned int *param_1) {
    unsigned int v;
    param_1[0x11c] = func_ov022_020b0b10((int)param_1);
    if ((int)(param_1[0x11d] + 1) >= *(int *)(param_1[0x11a] + 0x14)) {
        param_1[0x11d] = 0xffffffff;
    }
    if ((int)param_1[0x11d] >= 0) {
        param_1[0x11d] = param_1[0x11d] + 1;
    }
    func_ov022_020b064c(*(int *)(param_1[0x11c] + 0x14));
    if ((*param_1 & 8) == 0) {
        v = 0;
    } else {
        v = param_1[0x11e] + 1;
    }
    param_1[0x11e] = v;
    ((struct flags_020b0a54 *)param_1)->b3 = 0;
    ((struct flags_020b0a54 *)param_1)->b4 = 0;
}
