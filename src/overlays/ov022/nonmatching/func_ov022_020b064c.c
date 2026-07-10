/*
 * NONMATCHING (nested-loop induction-SR tie, +12B). The byte-bitfield clear
 * (bic #1/#2), the `= -1` mvn fill value, and the guarded call-loop all match.
 * The fill loop `*(short*)(param_1 + iVar3*0x10 + iVar2*2 + 0x3e) = -1` is the
 * problem: the original keeps iVar3/iVar2 as pure counters and recomputes the
 * address each iteration via barrel shifts (add r4,lr,lsl#4 / add .,ip,lsl#1,
 * strh #0x3e), while mwcc strength-reduces BOTH levels into walking pointers
 * (row += 0x10, iVar1 += 2). Tried: a per-outer `row` local, inlining iVar2*2.
 * Byte-equivalent.
 */
extern void func_ov022_020b06d8(int a, unsigned int b);

struct bits_020b064c {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char rest : 6;
};

void func_ov022_020b064c(int param_1) {
    int iVar3 = 0;
    int iVar2;
    int iVar1;
    ((struct bits_020b064c *)(param_1 + 0x3c))->b0 = 0;
    ((struct bits_020b064c *)(param_1 + 0x3c))->b1 = 0;
    do {
        int row = param_1 + iVar3 * 0x10;
        iVar2 = 0;
        do {
            iVar1 = iVar2 * 2;
            iVar2 = iVar2 + 1;
            *(short *)(row + iVar1 + 0x3e) = -1;
        } while (iVar2 < 8);
        iVar3 = iVar3 + 1;
    } while (iVar3 < 4);
    iVar3 = 0;
    if (*(short *)(param_1 + 0x30) <= 0) {
        return;
    }
    iVar2 = 0;
    do {
        func_ov022_020b06d8(*(int *)(param_1 + 0x34) + iVar2, *(unsigned char *)(param_1 + 2));
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + 0x48;
    } while (iVar3 < *(short *)(param_1 + 0x30));
}
