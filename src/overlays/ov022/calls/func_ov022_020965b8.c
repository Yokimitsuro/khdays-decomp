extern void func_0202afdc(int a, int b);

void func_ov022_020965b8(int param_1) {
    int iVar1;
    int sVar2;
    int iVar3;
    if (*(int *)(param_1 + 0x6c) == 0) {
        return;
    }
    sVar2 = *(unsigned short *)(*(int *)(param_1 + 0x6c) + 0x84);
    if (sVar2 == 0) {
        if (*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x108) != 0) {
            return;
        }
        sVar2 = 0x7fff;
    }
    func_0202afdc(*(int *)(param_1 + 0x20) + 4, sVar2);
    iVar3 = param_1 + 0xdac;
    iVar1 = 0;
    do {
        if (*(char *)(param_1 + 0xda9) != 0) {
            func_0202afdc(iVar3, sVar2);
        }
        iVar1 = iVar1 + 1;
        param_1 = param_1 + 0x164;
        iVar3 = iVar3 + 0x164;
    } while (iVar1 < 2);
}
