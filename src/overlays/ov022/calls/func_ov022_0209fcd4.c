extern int func_ov022_0209fc78(int param_1, int arg1);

int func_ov022_0209fcd4(int param_1) {
    int iVar2 = *(int *)(param_1 + 0xc);
    int bVar1 = 0;
    if (iVar2 <= 5) {
        if (iVar2 < 5 && iVar2 != 0) {
            goto done;
        }
        goto set_true;
    }
    switch (iVar2) {
    case 0x10:
        goto set_true;
    case 0x13:
    set_true:
        bVar1 = 1;
        break;
    case 0xe:
        if (func_ov022_0209fc78(param_1, -1) != 0) {
            bVar1 = 1;
        }
        break;
    case 0xb:
        bVar1 = 1;
        break;
    case 0xc:
    case 0xd:
    case 0xf:
    case 0x11:
    case 0x12:
        break;
    }
done:
    return bVar1;
}
