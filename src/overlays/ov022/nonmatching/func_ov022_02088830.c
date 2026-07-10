/*
 * NONMATCHING (base-coalescing / register-swap tie, size-exact byte-diff @0x9).
 * The `*(u64*)puVar1 |= 0x400` 64-bit OR, the `|= 4` byte set, the guarded call
 * loop and the FUN_020acebc arg all match. The divergence: the original keeps
 * iVar4 fixed in r7 (reading the loop-bound byte via [r7,#0x34]) and walks a
 * separate iVar3 in r6; mwcc coalesces iVar4 into the walking register and
 * hoists the invariant address iVar4+0x34 into r4. Same base-coalescing tie as
 * 02093ea8. Byte-equivalent.
 */
extern int data_ov022_020b2e78;
extern void func_ov022_020acebc(int a, int b);

void func_ov022_02088830(void) {
    int iVar4 = *(int *)((int)&data_ov022_020b2e78 + 4);
    int iVar2;
    int iVar3;
    if (iVar4 == 0) {
        return;
    }
    iVar2 = 0;
    *(unsigned char *)(iVar4 + 0x3c) = *(unsigned char *)(iVar4 + 0x3c) | 4;
    if (0 < (int)*(unsigned char *)(iVar4 + 0x34)) {
        iVar3 = iVar4;
        do {
            unsigned int *puVar1 = *(unsigned int **)(*(int *)(iVar3 + 4) + 0x20);
            func_ov022_020acebc((int)puVar1, *(short *)((int)puVar1 + 0x2aba));
            *(unsigned long long *)puVar1 |= 0x400;
            iVar2 = iVar2 + 1;
            iVar3 = iVar3 + 0xc;
        } while (iVar2 < (int)*(unsigned char *)(iVar4 + 0x34));
    }
}
