extern int func_ov022_0209c774(int a, int b);
extern void func_ov002_02051d44(int a, int b);
extern void func_ov002_02051cbc(int a);
extern void func_ov022_0209c7dc(int a);

struct bits_0209c9fc {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char rest : 5;
};

void func_ov022_0209c9fc(int param_1) {
    int iVar2;
    int iVar3;
    int iVar4;
    if (((struct bits_0209c9fc *)(param_1 + 0x694))->b2 == 0) {
        return;
    }
    iVar4 = param_1 + 0xda8;
    iVar2 = 0;
    iVar3 = param_1;
    do {
        if (*(char *)(iVar3 + 0xda9) != 0) {
            int iVar1 = func_ov022_0209c774(param_1, iVar2);
            func_ov002_02051d44(iVar4, iVar1);
            func_ov002_02051cbc(iVar4);
        }
        iVar2 = iVar2 + 1;
        iVar3 = iVar3 + 0x164;
        iVar4 = iVar4 + 0x164;
    } while (iVar2 < 2);
    if (*(void (**)(int))(param_1 + 0x674) != 0) {
        (*(void (**)(int))(param_1 + 0x674))(param_1);
        return;
    }
    func_ov022_0209c7dc(param_1);
}
