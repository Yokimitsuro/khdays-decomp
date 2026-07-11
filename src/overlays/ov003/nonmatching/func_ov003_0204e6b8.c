extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_020bd7c4(void);
extern void func_0202aa9c(void *p);
extern void func_ov003_0204e4b8(int i, int v);
extern void func_02033b24(int a, int b);
extern unsigned int func_0202a928(int p, int a);
extern void func_0202a818(void *p, int a);
extern void func_020335ec(int a);
extern int func_ov003_0204e9d8(void);

int func_ov003_0204e6b8(void) {
    unsigned short *root;
    unsigned int uVar3;
    int iVar4;
    int iVar10;
    unsigned short *puVar5;
    unsigned short *puVar6;
    unsigned short *puVar7;
    unsigned short *puVar8;
    unsigned short *puVar9;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    if (*(int *)(root + 0xf08) == 0) {
        *(int *)(root + 0xf0a) = func_020bd7c4();
    }
    func_0202aa9c(root + 0x84);
    uVar3 = *root;
    iVar10 = 0;
    if (0 < (int)uVar3) {
        puVar5 = root + 0x108;
        puVar6 = root + 0x318;
        puVar7 = root + 0x950;
        puVar8 = root + 0x528;
        puVar9 = root + 0x738;
        do {
            func_ov003_0204e4b8(iVar10, ((int *)root)[iVar10 + 0x5d4]);
            func_0202aa9c(puVar5);
            func_0202aa9c(puVar6);
            if (((int *)root)[iVar10 + 0x5e3] != 0) {
                func_0202aa9c(puVar7);
            }
            if (((int *)root)[iVar10 + 0x5e7] != 0 && (func_0202aa9c(puVar8), ((int *)root)[iVar10 + 0x4a4] != 0)) {
                func_0202aa9c(puVar9);
            }
            uVar3 = *root;
            iVar10 = iVar10 + 1;
            puVar5 = puVar5 + 0x84;
            puVar6 = puVar6 + 0x84;
            puVar7 = puVar7 + 0x84;
            puVar8 = puVar8 + 0x84;
            puVar9 = puVar9 + 0x84;
        } while (iVar10 < (int)uVar3);
    }
    iVar10 = 0;
    if (*(int *)(root + 0x2a) == 1) {
        iVar10 = 0;
        if (0 < (int)uVar3) {
            puVar5 = root + 0x950;
            puVar6 = root + 0x528;
            puVar7 = root + 0x738;
            do {
                if (((int *)root)[iVar10 + 0x5df] == 0) {
                    ((int *)root)[iVar10 + 0x5e3] = 1;
                    func_02033b24(0x182, 0);
                } else if (((int *)root)[iVar10 + 0x5e3] != 0) {
                    uVar3 = func_0202a928((int)puVar5, 0x1000);
                    if ((uVar3 & 1) == 0) {
                        func_0202a818(puVar5, 0x1000);
                    } else {
                        ((int *)root)[iVar10 + 0x5e3] = 0;
                    }
                }
                if (((int *)root)[iVar10 + 0x5df] == 0x28) {
                    ((int *)root)[iVar10 + 0x5e7] = 1;
                } else if (((int *)root)[iVar10 + 0x5e7] != 0 && (func_0202a818(puVar6, 0x1000), ((int *)root)[iVar10 + 0x4a4] != 0)) {
                    func_0202a818(puVar7, 0x1000);
                }
                puVar5 = puVar5 + 0x84;
                ((int *)root)[iVar10 + 0x5df] = ((int *)root)[iVar10 + 0x5df] + 1;
                puVar6 = puVar6 + 0x84;
                puVar7 = puVar7 + 0x84;
                iVar10 = iVar10 + 1;
                uVar3 = *root;
            } while (iVar10 < (int)uVar3);
        }
        iVar4 = 0;
        iVar10 = (int)func_ov003_0204e9d8;
        if (0 < (int)uVar3) {
            do {
                if (((int *)root)[iVar4 + 0x5e3] != 0) {
                    iVar10 = 0;
                    break;
                }
                iVar4 = iVar4 + 1;
            } while (iVar4 < (int)uVar3);
        }
    }
    if (iVar10 != 0) {
        func_020335ec(4);
    }
    return iVar10;
}
