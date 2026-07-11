extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_020bd7c4(void);
extern void func_ov003_0204e91c(void *p);
extern void func_0202accc(int a, int b, int c, int d);
extern unsigned int func_0202a928(int p, int a);
extern void func_0202a818(void *p, int a);
extern int func_ov003_0204f08c(void);

int func_ov003_0204ed7c(void) {
    unsigned short *root;
    unsigned int uVar3;
    int uVar4;
    int iVar8;
    unsigned short *puVar5;
    unsigned short *puVar6;
    unsigned short *puVar7;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    uVar4 = 0;
    if (*(int *)(root + 0xf08) == 0) {
        *(int *)(root + 0xf0a) = func_020bd7c4();
    }
    func_ov003_0204e91c(root);
    if (*(int *)(root + 0x2a) == 1) {
        iVar8 = 0;
        *(int *)(root + 0xbb0) = (*(int *)(root + 0xbb0) + 0x2000) & 0xffff;
        if (0 < (int)(unsigned int)*root) {
            puVar5 = root + 0xb60;
            puVar6 = root + 0x528;
            puVar7 = root + 0x738;
            do {
                if (((int *)root)[iVar8 + 0xb] == 3) {
                    if (0x6400 < ((int *)root)[iVar8 + 0x5d4]) {
                        ((int *)root)[iVar8 + 0x5d4] -= 400;
                    } else if (*(int *)(root + 0xbb0) == 0) {
                        func_0202accc((int)puVar6, 0, (int)puVar5, 4);
                        if (((int *)root)[iVar8 + 0x4a4] != 0) {
                            func_0202accc((int)puVar7, 0, (int)(puVar7 + 0x70), 4);
                        }
                        *(int *)(root + 0xbba) = 0;
                        uVar4 = (int)func_ov003_0204f08c;
                        *(int *)(root + 0xbbc) = 0;
                    }
                }
                if (((int *)root)[iVar8 + 0xb] != 3 && (uVar3 = func_0202a928((int)puVar6, 0x1000), (uVar3 & 1) != 0)) {
                    if (((int *)root)[iVar8 + 0xb] == 0) {
                        func_0202accc((int)puVar6, 0, (int)puVar5, 2);
                        if (((int *)root)[iVar8 + 0x4a4] != 0) {
                            func_0202accc((int)puVar7, 0, (int)(puVar7 + 0x70), 2);
                        }
                    } else {
                        func_0202accc((int)puVar6, 0, (int)puVar5, 5);
                        if (((int *)root)[iVar8 + 0x4a4] != 0) {
                            func_0202accc((int)puVar7, 0, (int)(puVar7 + 0x70), 5);
                        }
                    }
                }
                func_0202a818(puVar6, 0x1000);
                if (((int *)root)[iVar8 + 0x4a4] != 0) {
                    func_0202a818(puVar7, 0x1000);
                }
                puVar5 = puVar5 + 0x12;
                puVar6 = puVar6 + 0x84;
                puVar7 = puVar7 + 0x84;
                iVar8 = iVar8 + 1;
            } while (iVar8 < (int)(unsigned int)*root);
        }
    }
    return uVar4;
}
