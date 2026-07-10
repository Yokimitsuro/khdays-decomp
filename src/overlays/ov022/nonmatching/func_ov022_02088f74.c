/*
 * NONMATCHING (constant-hoist + iVar4/iVar5 register-swap tie, size-exact @0x29).
 * pbVar1 stays fixed (r7), the 6-bit count guard, the calls and field stores all
 * match. mwcc hoists the byte-store 0 into a callee-saved reg and materializes
 * 0x1000 inside the loop; the original hoists 0x1000 and inlines the 0. Plus an
 * iVar4/iVar5 r8<->r9 swap. Tried i-first split-decl, an explicit 0x1000 local.
 * Byte-equivalent; coloring-dominated tier.
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a634(unsigned short *a, unsigned int *b, int c, unsigned int d);
extern void func_ov022_020892f0(unsigned short *a, int b);

void func_ov022_02088f74(unsigned int *param_1) {
    int iVar3;
    unsigned char *pbVar1 = (unsigned char *)NNSi_FndGetCurrentRootHeap();
    iVar3 = 0;
    if (0 < (int)(((unsigned int)*pbVar1 << 0x18) >> 0x1a)) {
        int iVar5 = 0;
        do {
            int iVar2 = *(int *)(pbVar1 + 0xc);
            int iVar4 = iVar2 + iVar5;
            func_0202a634((unsigned short *)(iVar4 + 4), (unsigned int *)*param_1, 1,
                          pbVar1[0x20]);
            *(int *)(iVar4 + 0xbc) = 0x1000;
            *(int *)(iVar4 + 0xb8) = 0x1000;
            *(int *)(iVar4 + 0xb4) = 0x1000;
            func_ov022_020892f0((unsigned short *)(iVar4 + 4), 0);
            *(char *)(iVar2 + iVar5) = 0;
            *(int *)(iVar4 + 0x10c) = 0;
            *(char *)(iVar4 + 0x110) = -1;
            *(char *)(iVar4 + 0x111) = -1;
            iVar3 = iVar3 + 1;
            iVar5 = iVar5 + 0x114;
        } while (iVar3 < (int)(((unsigned int)*pbVar1 << 0x18) >> 0x1a));
    }
}
