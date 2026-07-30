typedef struct Ov003RootContextView {
    unsigned char pad0000[0x1290];
    int secondaryPresent[4];
    unsigned char pad12a0[0x4b0];
    int layerValue[4];
    unsigned char pad1760[0x1c];
    int layerTicks[4];
    int primaryActive[4];
    int secondaryActive[4];
} Ov003RootContextView;

extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_ov105_020bd7c4(void);
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
    int iVar11;
    int iVar12;
    int iVar10;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    iVar10 = 0;
    if (*(int *)(root + 0xf08) == 0) {
        *(int *)(root + 0xf0a) = func_ov105_020bd7c4();
    }
    func_0202aa9c(root + 0x84);
    uVar3 = *root;
    iVar11 = 0;
    if (0 < (int)uVar3) {
        unsigned short *puVar5 = root + 0x108;
        unsigned short *puVar6 = root + 0x318;
        unsigned short *puVar7 = root + 0x950;
        unsigned short *puVar8 = root + 0x528;
        unsigned short *puVar9 = root + 0x738;

        do {
            func_ov003_0204e4b8(iVar11, ((Ov003RootContextView *)root)->layerValue[iVar11]);
            func_0202aa9c(puVar5);
            func_0202aa9c(puVar6);
            if (((Ov003RootContextView *)root)->primaryActive[iVar11] != 0) {
                func_0202aa9c(puVar7);
            }
            if (((Ov003RootContextView *)root)->secondaryActive[iVar11] != 0 &&
                (func_0202aa9c(puVar8),
                 ((Ov003RootContextView *)root)->secondaryPresent[iVar11] != 0)) {
                func_0202aa9c(puVar9);
            }
            uVar3 = *root;
            iVar11 = iVar11 + 1;
            puVar5 = puVar5 + 0x84;
            puVar6 = puVar6 + 0x84;
            puVar7 = puVar7 + 0x84;
            puVar8 = puVar8 + 0x84;
            puVar9 = puVar9 + 0x84;
        } while (iVar11 < (int)uVar3);
    }
    if (*(int *)(root + 0x2a) == 1) {
        iVar12 = 0;
        if (0 < (int)uVar3) {
            unsigned short *puVar5 = root + 0x950;
            unsigned short *puVar6 = root + 0x528;
            unsigned short *puVar7 = root + 0x738;

            do {
                if (((Ov003RootContextView *)root)->layerTicks[iVar12] == 0) {
                    ((Ov003RootContextView *)root)->primaryActive[iVar12] = 1;
                    func_02033b24(0x182, 0);
                } else if (((Ov003RootContextView *)root)->primaryActive[iVar12] != 0) {
                    uVar3 = func_0202a928((int)puVar5, 0x1000);
                    if ((uVar3 & 1) != 0) {
                        ((Ov003RootContextView *)root)->primaryActive[iVar12] = 0;
                    } else {
                        func_0202a818(puVar5, 0x1000);
                    }
                }
                if (((Ov003RootContextView *)root)->layerTicks[iVar12] == 0x28) {
                    ((Ov003RootContextView *)root)->secondaryActive[iVar12] = 1;
                } else if (((Ov003RootContextView *)root)->secondaryActive[iVar12] != 0 &&
                           (func_0202a818(puVar6, 0x1000),
                            ((Ov003RootContextView *)root)->secondaryPresent[iVar12] != 0)) {
                    func_0202a818(puVar7, 0x1000);
                }
                ((Ov003RootContextView *)root)->layerTicks[iVar12] =
                    ((Ov003RootContextView *)root)->layerTicks[iVar12] + 1;
                puVar5 = puVar5 + 0x84;
                puVar6 = puVar6 + 0x84;
                puVar7 = puVar7 + 0x84;
                iVar12 = iVar12 + 1;
                uVar3 = *root;
            } while (iVar12 < (int)uVar3);
        }
        iVar10 = (int)func_ov003_0204e9d8;
        iVar4 = 0;
        if (0 < (int)uVar3) {
            do {
                if (((Ov003RootContextView *)root)->primaryActive[iVar4] != 0) {
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
