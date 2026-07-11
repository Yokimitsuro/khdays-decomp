extern void func_0202aa9c(void *p);
extern void func_ov003_0204e4b8(int i, int v);
extern void func_ov003_0204e510(int i, int v);

void func_ov003_0204e91c(unsigned short *param_1) {
    int *p1000;
    unsigned short *puVar1;
    unsigned short *puVar2;
    unsigned short *puVar3;
    unsigned short *puVar4;
    int iVar5;

    func_0202aa9c(param_1 + 0x84);
    iVar5 = 0;
    if (0 < (int)(unsigned int)*param_1) {
        puVar1 = param_1 + 0x108;
        puVar2 = param_1 + 0x318;
        puVar3 = param_1 + 0x528;
        puVar4 = param_1 + 0x738;
        p1000 = (int *)((char *)param_1 + 0x1000);
        do {
            func_ov003_0204e4b8(iVar5, ((int *)param_1)[iVar5 + 0x5d4]);
            if (((int *)param_1)[iVar5 + 0xb] == 3) {
                func_ov003_0204e510(iVar5, p1000[0x1d8]);
            }
            func_0202aa9c(puVar1);
            func_0202aa9c(puVar2);
            func_0202aa9c(puVar3);
            if (((int *)param_1)[iVar5 + 0x4a4] != 0) {
                func_0202aa9c(puVar4);
            }
            iVar5 = iVar5 + 1;
            puVar1 = puVar1 + 0x84;
            puVar2 = puVar2 + 0x84;
            puVar3 = puVar3 + 0x84;
            puVar4 = puVar4 + 0x84;
        } while (iVar5 < (int)(unsigned int)*param_1);
    }
}
