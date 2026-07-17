/* func_ov003_0204f33c -- near-match (14B tail register-coloring tie). Everything
 * through the ef68 call is byte-exact; the final predicated `bba = (iVar4==0)?bba+1:0`
 * block colors pbba to r1 (vs the ROM's r0) with the value spread over r0/r2 instead
 * of incremented in-place in r1 -- an unsteerable coalescing choice. Route to nonmatching/. */
extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_020bd7c4(void);
extern void func_ov003_0204e91c(void *p);
extern void func_ov003_0204d6c8(int i, int v);
extern void func_02011640(int a, int b, void *p, int n);
extern void func_ov003_0204ef68(void *p);
extern int func_ov003_0204f460(void);

int func_ov003_0204f33c(void) {
    unsigned short *root;
    unsigned int uVar3;
    int iVar4;
    int iVar5;
    int d;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    iVar4 = 0;
    if (*(int *)(root + 0xf08) == 0) {
        *(int *)(root + 0xf0a) = func_020bd7c4();
    }
    func_ov003_0204e91c(root);
    if (*(int *)(root + 0xbba) == 0) {
        uVar3 = *root;
        iVar5 = 0;
        if (0 < (int)uVar3) {
            do {
                if (((int *)root)[iVar5 + 0xb] < (int)(uVar3 - 1)) {
                    func_ov003_0204d6c8(iVar5, ((int *)root)[iVar5 + 0xb]);
                }
                uVar3 = *root;
                iVar5 = iVar5 + 1;
            } while (iVar5 < (int)uVar3);
        }
        func_02011640(9, 0, root + 0xbdc, 0x600);
        func_02011640(0x19, 0, root + 0xbdc, 0x600);
        *(int *)(root + 0xf06) = 0x10;
    } else {
        func_02011640(0x19, 0, root + 0xbdc, 0x600);
        d = 0x10 - *(int *)(root + 0xbba);
        *(int *)(root + 0xf06) = d;
        if (d <= 0) {
            *(int *)(root + 0xf06) = 0;
            iVar4 = (int)func_ov003_0204f460;
        }
    }
    func_ov003_0204ef68(root);
    {
        int *pbba = (int *)((char *)root + 0x1000);
        iVar5 = (iVar4 == 0) ? pbba[0x1dd] + 1 : 0;
        pbba[0x1dd] = iVar5;
    }
    return iVar4;
}
