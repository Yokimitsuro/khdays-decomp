extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_020bd7c4(void);
extern void func_ov003_0204e91c(void *p);
extern void func_01ff86c8(int a, int b, int c);
extern void func_ov003_0204d55c(void);
extern void func_02013484(int a, void *b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_02011640(int a, int b, void *p, int n);
extern unsigned int func_0202a928(int p, int a);
extern void func_0202accc(int a, int b, int c, int d);
extern void func_0202a818(void *p, int a);
extern int func_ov003_0204f33c(void);
extern int func_ov003_0204f460(void);

int func_ov003_0204f08c(void) {
    unsigned short *root;
    unsigned int uVar3;
    int iVar4;
    int iVar5;
    int iVar9;
    unsigned short *puVar6;
    unsigned short *puVar7;
    unsigned short *puVar8;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    iVar9 = 0;
    if (*(int *)(root + 0xf08) == 0) {
        *(int *)(root + 0xf0a) = func_020bd7c4();
    }
    func_ov003_0204e91c(root);
    if (*(int *)(root + 0xbba) == 0) {
        if (*(int *)(root + 0xbbc) != 0) {
            func_01ff86c8(0, (int)(root + 0xbdc), 0x600);
            func_ov003_0204d55c();
            func_02013484((int)(root + 0xbdc), *(unsigned short **)(root + 0xee6), 0, 0, 3, 5, 0x20, 0x18, 0x1a, 0xe);
            func_02011640(9, 0, root + 0xbdc, 0x600);
            func_02011640(0x19, 0, root + 0xbdc, 0x600);
        }
        *(int *)(root + 0xbd6) = 1;
        *(int *)(root + 0xbd8) = -0xbf;
        *(int *)(root + 0xbda) = 0;
    } else {
        func_02011640(0x19, 0, root + 0xbdc, 0x600);
        iVar5 = *(int *)(root + 0xbd8);
        *(int *)(root + 0xbd8) = iVar5 + 6;
        if (0 < iVar5 + 6) {
            *(int *)(root + 0xbd8) = 0;
            *(int *)(root + 0xbba) = 0;
            iVar9 = (*(int *)(root + 0xbbc) != 0) ? (int)func_ov003_0204f460 : (int)func_ov003_0204f33c;
        }
        iVar5 = *(int *)(root + 0xbda);
        iVar4 = iVar5 + 1;
        *(int *)(root + 0xbda) = iVar4;
        if (0x1f < iVar4) {
            *(int *)(root + 0xbda) = 0x1f;
        }
    }
    if (*(int *)(root + 0x2a) == 1 && (iVar5 = 0, *root != 0)) {
        puVar6 = root + 0x528;
        puVar7 = root + 0xb60;
        puVar8 = root + 0x738;
        do {
            uVar3 = func_0202a928((int)puVar6, 0x1000);
            if ((uVar3 & 1) != 0) {
                if (((int *)root)[iVar5 + 0xb] == 0) {
                    func_0202accc((int)puVar6, 0, (int)puVar7, 2);
                    if (((int *)root)[iVar5 + 0x4a4] != 0) {
                        func_0202accc((int)puVar8, 0, (int)(puVar8 + 0x70), 2);
                    }
                } else {
                    func_0202accc((int)puVar6, 0, (int)puVar7, 5);
                    if (((int *)root)[iVar5 + 0x4a4] != 0) {
                        func_0202accc((int)puVar8, 0, (int)(puVar8 + 0x70), 5);
                    }
                }
            }
            func_0202a818(puVar6, 0x1000);
            if (((int *)root)[iVar5 + 0x4a4] != 0) {
                func_0202a818(puVar8, 0x1000);
            }
            puVar6 = puVar6 + 0x84;
            puVar7 = puVar7 + 0x12;
            puVar8 = puVar8 + 0x84;
            iVar5 = iVar5 + 1;
        } while (iVar5 < (int)(unsigned int)*root);
    }
    if (iVar9 == 0) {
        iVar5 = *(int *)(root + 0xbba) + 1;
    } else {
        iVar5 = 0;
    }
    *(int *)(root + 0xbba) = iVar5;
    return iVar9;
}
