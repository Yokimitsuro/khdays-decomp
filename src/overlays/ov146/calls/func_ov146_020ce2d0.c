struct v3 { int x, y, z; };

extern int func_ov146_020ce694(int a, struct v3 v);

int func_ov146_020ce2d0(int param_1, struct v3 param_2) {
    if (*(int *)(param_1 + 0x50) == 1) {
        return func_ov146_020ce694(*(int *)(param_1 + 0x214), param_2);
    }
    return param_1;
}
