/*
 * NONMATCHING (iVar6/puVar5 register-coloring swap, size-exact byte-diff @0x25).
 * Fully matched otherwise: the 6-bit count field `((*pbVar1 << 0x18) >> 0x1a)`
 * as a signed `> 0` guard (cmp/ble not lsrs), `unsigned char` guard read (ldrb),
 * split iVar4 decl/assign so `mov r7,#0` lands after the NNSi call, hoisted
 * 0x1000/0x1800 constants for the moveq/movne. The only divergence: mwcc puts
 * iVar6 in r9 / puVar5 in r10, the original the reverse (iVar6=r10, puVar5=r9).
 * Tried decl-order swaps. Byte-equivalent.
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_02023c40(void);
extern unsigned int func_0202a818(unsigned short *p, int a);

void func_ov022_02089150(void) {
    int iVar4;
    unsigned char *pbVar1 = (unsigned char *)NNSi_FndGetCurrentRootHeap();
    iVar4 = 0;
    if ((int)(((unsigned int)*pbVar1 << 0x18) >> 0x1a) > 0) {
        int iVar6 = 0;
        do {
            char *puVar5 = (char *)(*(int *)(pbVar1 + 0xc) + iVar6);
            if (*(unsigned char *)(*(int *)(pbVar1 + 0xc) + iVar6) != 0) {
                int iVar2;
                if (func_02023c40() == 1) {
                    iVar2 = 0x1800;
                } else {
                    iVar2 = 0x1000;
                }
                if (func_0202a818((unsigned short *)(puVar5 + 4), iVar2) != 0) {
                    *puVar5 = 0;
                }
            }
            iVar4 = iVar4 + 1;
            iVar6 = iVar6 + 0x114;
        } while (iVar4 < (int)(((unsigned int)*pbVar1 << 0x18) >> 0x1a));
    }
}
