extern int func_ov022_020882e0(int a);
extern int func_ov022_02088474(int a);
extern int func_01fffde0(int a);

int func_ov022_0209ee54(int param_1, int param_2, int param_3, int param_4) {
    int sVar2 = func_ov022_020882e0(param_2);
    int iVar3;
    int iVar4;
    int bVar1;
    if (sVar2 <= 0) {
        return 0;
    }
    iVar3 = func_ov022_02088474(param_2);
    if (param_3 != iVar3) {
        return 0;
    }
    iVar3 = func_01fffde0(param_2);
    if (param_4 == 0) {
        return iVar3;
    }
    bVar1 = 0;
    iVar4 = 0;
    do {
        if ((int)((unsigned int)*(unsigned char *)(iVar3 + 9) * 0x800) ==
            ((short *)param_4)[iVar4]) {
            bVar1 = 1;
            break;
        }
        iVar4 = iVar4 + 1;
    } while (iVar4 < 8);
    if (bVar1 != 0) {
        iVar3 = 0;
    }
    return iVar3;
}
