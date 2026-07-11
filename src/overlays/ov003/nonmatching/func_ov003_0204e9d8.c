extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_020bd7c4(void);
extern void func_ov003_0204e91c(void *p);
extern void func_0202accc(int a, int b, int c, int d);
extern unsigned int func_0202a928(int p, int a);
extern void func_0202a818(void *p, int a);
extern int data_0204f724[];
extern int func_ov003_0204eb84(void);

int func_ov003_0204e9d8(void) {
    unsigned short *root;
    int *tbl;
    int uVar7;
    int iVar4;
    int iVar6;
    int iVar11;
    unsigned int uVar5;
    unsigned short *puVar8;
    unsigned short *puVar9;
    unsigned short *puVar10;
    int *p;
    int *p1000;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    uVar7 = 0;
    if (*(int *)(root + 0xf08) == 0) {
        *(int *)(root + 0xf0a) = func_020bd7c4();
    }
    func_ov003_0204e91c(root);
    if (*(int *)(root + 0x2a) == 1 && (iVar11 = 0, *root != 0)) {
        tbl = data_0204f724;
        puVar8 = root + 0xb60;
        puVar9 = root + 0x528;
        puVar10 = root + 0x738;
        do {
            p = (int *)root + iVar11;
            p1000 = p + 0x400;
            if (p1000[0x1d9] == 0) {
                iVar4 = p1000[0x1d4];
                p1000[0x1d4] = iVar4 + 300;
                iVar6 = p[0xb];
                if (iVar4 + 300 >= tbl[iVar6]) {
                    if (iVar6 == 0) {
                        p1000[0x1d9] = 1;
                        *(int *)(root + 0xbba) = 0;
                        uVar7 = (int)func_ov003_0204eb84;
                    } else if (iVar6 != 3) {
                        p1000[0x1d9] = 1;
                        func_0202accc((int)puVar9, 0, (int)puVar8, 4);
                        if (p1000[0xa4] != 0) {
                            func_0202accc((int)puVar10, 0, (int)(puVar10 + 0x70), 4);
                        }
                    }
                }
            } else {
                uVar5 = func_0202a928((int)puVar9, 0x1000);
                if ((uVar5 & 1) != 0) {
                    func_0202accc((int)puVar9, 0, (int)puVar8, 5);
                    if (p1000[0xa4] != 0) {
                        func_0202accc((int)puVar10, 0, (int)(puVar10 + 0x70), 5);
                    }
                }
            }
            func_0202a818(puVar9, 0x1000);
            if (p1000[0xa4] != 0) {
                func_0202a818(puVar10, 0x1000);
            }
            puVar8 = puVar8 + 0x12;
            puVar9 = puVar9 + 0x84;
            puVar10 = puVar10 + 0x84;
            iVar11 = iVar11 + 1;
        } while (iVar11 < (int)(unsigned int)*root);
    }
    return uVar7;
}
