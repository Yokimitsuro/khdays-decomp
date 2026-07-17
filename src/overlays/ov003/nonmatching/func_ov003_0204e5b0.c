/* func_ov003_0204e5b0 -- near-match (4B strength-reduction tie). Byte-exact except the
 * second loop's `iVar4 * -8` store: mwcc strength-reduces it to a running counter where
 * the ROM recomputes `rsb;lsl` each iteration. Unsteerable. Route to nonmatching/. */
extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_020bd7c4(void);
extern void func_0202aa9c(void *p);
extern void func_ov003_0204e4b8(int i, int v);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern int func_ov003_0204e6b8(void);

int func_ov003_0204e5b0(void) {
    unsigned short *root;
    unsigned int uVar3;
    int iVar4;
    unsigned short *puVar5;
    unsigned short *puVar6;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    if (*(int *)(root + 0xf08) == 0) {
        *(int *)(root + 0xf0a) = func_020bd7c4();
    }
    func_0202aa9c(root + 0x84);
    uVar3 = *root;
    iVar4 = 0;
    if (0 < (int)uVar3) {
        puVar5 = root + 0x108;
        puVar6 = root + 0x318;
        do {
            func_ov003_0204e4b8(iVar4, ((int *)root)[iVar4 + 0x5d4]);
            func_0202aa9c(puVar5);
            func_0202aa9c(puVar6);
            uVar3 = *root;
            iVar4 = iVar4 + 1;
            puVar5 = puVar5 + 0x84;
            puVar6 = puVar6 + 0x84;
        } while (iVar4 < (int)uVar3);
    }
    iVar4 = *(int *)(root + 0xbba);
    if (iVar4 < 0x10) {
        *(int *)(root + 0xbba) = iVar4 + 1;
        func_0201e374(iVar4 - 0xf);
        func_0201e3cc(*(int *)(root + 0xbba) - 0x10);
        return 0;
    }
    iVar4 = 0;
    if (0 < (int)uVar3) {
        do {
            ((int *)root)[iVar4 + 0x5df] = iVar4 * -8;
            ((int *)root)[iVar4 + 0x5e3] = 0;
            ((int *)root)[iVar4 + 0x5e7] = 0;
            iVar4 = iVar4 + 1;
        } while (iVar4 < (int)(unsigned int)*root);
    }
    return (int)func_ov003_0204e6b8;
}
