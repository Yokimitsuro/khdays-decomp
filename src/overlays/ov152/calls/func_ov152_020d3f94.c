extern int func_0203c5c0(int obj, int a, int b, void *cb1, void *cb2, int **out);
extern int *func_01fffd70(int p);
extern int *func_01fffd8c(int p);
extern void func_ov152_020d40e4(void);
extern void func_ov152_020d418c(void);
int func_ov152_020d3f94(int param_1, int param_2) {
    int *local_28;
    int iVar1 = func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x48,
                              func_ov152_020d40e4, func_ov152_020d418c, &local_28);
    int iVar5 = 0;
    *local_28 = param_1;
    int iVar4 = *(int *)(*local_28 + 4);
    do {
        int *piVar2;
        int iVar3;
        if (((unsigned short *)param_2)[iVar5] == 0) break;
        piVar2 = func_01fffd70(iVar4 + 0x80);
        iVar3 = (piVar2 == 0) ? 0 : *piVar2;
        if (iVar3 != 0) {
            do {
                unsigned short pv = ((unsigned short *)param_2)[iVar5];
                if (pv == *(unsigned short *)(iVar3 + 2)) {
                    local_28[iVar5 + 2] = iVar3;
                    break;
                }
                piVar2 = func_01fffd8c(iVar4 + 0x80);
                iVar3 = (piVar2 == 0) ? 0 : *piVar2;
            } while (iVar3 != 0);
        }
        iVar5++;
    } while (iVar5 < 0x10);
    return iVar1;
}
