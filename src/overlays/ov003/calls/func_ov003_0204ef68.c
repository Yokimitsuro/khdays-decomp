extern unsigned int func_0202a928(int p, int a);
extern void func_0202accc(int a, int b, int c, int d);
extern void func_0202a818(void *p, int a);

void func_ov003_0204ef68(unsigned short *param_1) {
    unsigned int uVar1;
    int iVar2;
    unsigned short *puVar3;
    unsigned short *puVar4;
    unsigned short *puVar5;

    if (*(int *)(param_1 + 0x2a) != 1) {
        return;
    }
    iVar2 = 0;
    if (0 < (int)(unsigned int)*param_1) {
        puVar3 = param_1 + 0x528;
        puVar4 = param_1 + 0xb60;
        puVar5 = param_1 + 0x738;
        do {
            uVar1 = func_0202a928((int)puVar3, 0x1000);
            if ((uVar1 & 1) != 0) {
                if (((int *)param_1)[iVar2 + 0xb] == 0) {
                    func_0202accc((int)puVar3, 0, (int)puVar4, 2);
                    if (((int *)param_1)[iVar2 + 0x4a4] != 0) {
                        func_0202accc((int)puVar5, 0, (int)(puVar5 + 0x70), 2);
                    }
                } else {
                    func_0202accc((int)puVar3, 0, (int)puVar4, 5);
                    if (((int *)param_1)[iVar2 + 0x4a4] != 0) {
                        func_0202accc((int)puVar5, 0, (int)(puVar5 + 0x70), 5);
                    }
                }
            }
            func_0202a818(puVar3, 0x1000);
            if (((int *)param_1)[iVar2 + 0x4a4] != 0) {
                func_0202a818(puVar5, 0x1000);
            }
            puVar3 = puVar3 + 0x84;
            puVar4 = puVar4 + 0x12;
            puVar5 = puVar5 + 0x84;
            iVar2 = iVar2 + 1;
        } while (iVar2 < (int)(unsigned int)*param_1);
    }
}
