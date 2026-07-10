extern int func_ov022_0209405c(unsigned char *p);
extern int func_ov022_02094074(unsigned char *p);
extern int func_ov022_020983ec(unsigned int *p, int a);
extern int func_ov022_020a7018(unsigned int *p);

int func_ov022_020a6f9c(unsigned int *param_1) {
    int iVar2 = 0;
    if (func_ov022_0209405c((unsigned char *)(param_1 + 0x723)) != 0 &&
        func_ov022_02094074((unsigned char *)(param_1 + 0x723)) == 0) {
        return iVar2;
    }
    if ((*(unsigned long long *)param_1 & 4) == 0 &&
        (iVar2 = func_ov022_020983ec(param_1, 0)) == 0) {
        iVar2 = func_ov022_020a7018(param_1);
    }
    return iVar2;
}
