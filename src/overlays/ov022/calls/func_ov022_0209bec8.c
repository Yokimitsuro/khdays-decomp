extern int func_020307f4(unsigned int a);
extern void func_ov022_0209b250(int a, unsigned int *b, int c);
extern void func_ov022_0209b3c4(int a, unsigned int *b, int c);

struct tbl9_0209bec8 {
    int v[9];
};
extern struct tbl9_0209bec8 data_ov022_020b26d0;

void func_ov022_0209bec8(unsigned int *param_1) {
    unsigned int auStack_34[10];
    struct tbl9_0209bec8 local_58;
    unsigned int uVar2;
    int iVar1;
    uVar2 = 9;
    local_58 = data_ov022_020b26d0;
    if ((*(unsigned long long *)param_1 & 0x1000000000LL) != 0) {
        uVar2 = 8;
    }
    iVar1 = func_020307f4(uVar2);
    auStack_34[5] = local_58.v[iVar1];
    func_ov022_0209b250((int)param_1, auStack_34, 1);
    func_ov022_0209b3c4((int)param_1, auStack_34, 1);
}
