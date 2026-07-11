extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_020bd7c4(void);
extern void func_ov003_0204e91c(void *p);
extern void func_0202accc(int a, int b, int c, int d);
extern unsigned int func_0202a928(int p, int a);
extern void func_0202a818(void *p, int a);
extern int func_ov003_0204ed7c(void);
extern int func_ov003_0204f08c(void);

int func_ov003_0204eb84(void) {
    int bVar1;
    unsigned short *root;
    int iVar5;
    unsigned int uVar6;
    int uVar10;
    unsigned short *puVar7;
    unsigned short *puVar8;
    unsigned short *puVar9;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    uVar10 = 0;
    if (*(int *)(root + 0xf08) == 0) {
        *(int *)(root + 0xf0a) = func_020bd7c4();
    }
    func_ov003_0204e91c(root);
    if (*(int *)(root + 0x2a) == 1) {
        iVar5 = *(int *)(root + 0xbba);
        *(int *)(root + 0xbba) = iVar5 + 1;
        if (iVar5 + 1 >= 0x1e) {
            bVar1 = 1;
            iVar5 = 0;
            if (0 < (int)(unsigned int)*root) {
                puVar7 = root + 0xb60;
                puVar8 = root + 0x528;
                puVar9 = root + 0x738;
                do {
                    if (((int *)root)[iVar5 + 0xb] == 0) {
                        func_0202accc((int)puVar8, 0, (int)puVar7, 1);
                        if (((int *)root)[iVar5 + 0x4a4] != 0) {
                            func_0202accc((int)puVar9, 0, (int)(puVar9 + 0x70), 1);
                        }
                        uVar10 = (int)func_ov003_0204ed7c;
                        *(int *)(root + 0xbba) = 0;
                    }
                    if (((int *)root)[iVar5 + 0xb] == 3) {
                        bVar1 = 0;
                    }
                    iVar5 = iVar5 + 1;
                    puVar7 = puVar7 + 0x12;
                    puVar8 = puVar8 + 0x84;
                    puVar9 = puVar9 + 0x84;
                } while (iVar5 < (int)(unsigned int)*root);
            }
            if (bVar1) {
                *(int *)(root + 0xbba) = 0;
                uVar10 = (int)func_ov003_0204f08c;
                *(int *)(root + 0xbbc) = 0;
            }
        }
        iVar5 = 0;
        if (0 < (int)(unsigned int)*root) {
            puVar7 = root + 0x528;
            puVar8 = root + 0xb60;
            puVar9 = root + 0x738;
            do {
                if (((int *)root)[iVar5 + 0xb] != 0 && ((int *)root)[iVar5 + 0xb] != 3
                    && (uVar6 = func_0202a928((int)puVar7, 0x1000), (uVar6 & 1) != 0)
                    && (func_0202accc((int)puVar7, 0, (int)puVar8, 5), ((int *)root)[iVar5 + 0x4a4] != 0)) {
                    func_0202accc((int)puVar9, 0, (int)(puVar9 + 0x70), 5);
                }
                func_0202a818(puVar7, 0x1000);
                if (((int *)root)[iVar5 + 0x4a4] != 0) {
                    func_0202a818(puVar9, 0x1000);
                }
                puVar7 = puVar7 + 0x84;
                puVar8 = puVar8 + 0x12;
                puVar9 = puVar9 + 0x84;
                iVar5 = iVar5 + 1;
            } while (iVar5 < (int)(unsigned int)*root);
        }
    }
    return uVar10;
}
