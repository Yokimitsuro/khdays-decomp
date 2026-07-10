/*
 * NONMATCHING (multiple codegen-form ties, +32B). The guard chain and the loop
 * logic are correct, but: (1) the `(*(u64*)(p+0x464) & 0x80000000)==0` 64-bit AND
 * loads the high word via an immediate [r0,#0x468] in the orig, mwcc splits it
 * (add #0x64; ldr #0x404); (2) the bit0 test `(byte<<0x1f)>>0x1f` is kept as
 * lsl/lsrs (materialized in r0) by the orig, mwcc folds it to `ands #1` and
 * materializes the cond via movne/moveq (extra callee-saved regs). Byte-equivalent.
 */
extern void func_02033e48(unsigned int a);

void func_ov022_020a46f8(int param_1, int param_2) {
    int iVar2 = *(int *)(param_1 + 0x6bc);
    int iVar3;
    if (iVar2 < 0) {
        return;
    }
    if (iVar2 == param_2 && (*(unsigned long long *)(param_1 + 0x464) & 0x80000000) == 0) {
        return;
    }
    iVar2 = *(int *)(param_1 + iVar2 * 4 + 0x6c0);
    if (iVar2 == 0) {
        return;
    }
    iVar3 = 0;
    if (0 < (int)*(unsigned char *)(iVar2 + 1)) {
        do {
            int iVar4 = *(int *)(*(int *)(iVar2 + 4) + iVar3 * 4);
            unsigned int uVar1 = ((unsigned int)*(unsigned char *)(iVar4 + 4) << 0x1f) >> 0x1f;
            int bVar5 = uVar1 != 0;
            if (bVar5) {
                uVar1 = *(unsigned int *)(iVar4 + 8);
            }
            if (bVar5 && uVar1 != 0) {
                func_02033e48(uVar1);
            }
            *(int *)(iVar4 + 8) = 0;
            iVar3 = iVar3 + 1;
            *(unsigned char *)(iVar4 + 4) = *(unsigned char *)(iVar4 + 4) & 0xfd;
        } while (iVar3 < (int)*(unsigned char *)(iVar2 + 1));
    }
}
