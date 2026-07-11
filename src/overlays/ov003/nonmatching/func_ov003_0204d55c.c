extern int data_0204f9a0;
extern int data_0204be18;
extern void func_ov003_0204d264(unsigned short *dst, unsigned int val, int b);
extern void func_ov003_0204d1c0(unsigned short *dst, unsigned int val);

struct Frame { int c; unsigned short buf[4]; };

void func_ov003_0204d55c(void) {
    struct Frame f;
    int *piVar1;
    unsigned int uVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    int iVar9;

    iVar6 = 0;
    f.c = 6;
    f.buf[0] = 0;
    f.buf[1] = 0;
    f.buf[2] = 0;
    f.buf[3] = 0;
    iVar5 = *(int *)(data_0204f9a0 + 0x1dcc) + 0xc;
    do {
        piVar1 = &data_0204be18;
        iVar8 = f.c * 2;
        iVar7 = 0;
        iVar9 = 5;
        do {
            if (iVar7 == 3 || iVar7 < iVar6 + 1) {
                func_ov003_0204d264((unsigned short *)(iVar5 + iVar9 * 0x1a * 2 + iVar8),
                                    (unsigned int)*(unsigned short *)(*piVar1 + iVar6 * 8 + iVar7 * 2 + 0x1974), 10);
                f.buf[iVar7] = f.buf[iVar7] + *(short *)(*piVar1 + iVar6 * 8 + iVar7 * 2 + 0x1974);
            } else {
                iVar3 = iVar5 + iVar9 * 0x1a * 2;
                iVar4 = iVar3 + iVar8;
                *(short *)(iVar4 + 4) = (short)0xb03f;
                *(unsigned short *)(iVar4 + 2) = *(unsigned short *)(iVar4 + 4);
                *(unsigned short *)(iVar3 + iVar8) = *(unsigned short *)(iVar4 + 4);
            }
            iVar7 = iVar7 + 1;
            iVar9 = iVar9 + 2;
        } while (iVar7 < 4);
        iVar6 = iVar6 + 1;
        f.c = f.c + 5;
    } while (iVar6 < 3);
    uVar2 = 0x3e7;
    iVar8 = 0;
    iVar6 = 5;
    do {
        if (uVar2 < f.buf[iVar8]) {
            f.buf[iVar8] = (unsigned short)uVar2;
        }
        func_ov003_0204d1c0((unsigned short *)(iVar5 + iVar6 * 0x1a * 2 + 0x28), (unsigned int)f.buf[iVar8]);
        iVar8 = iVar8 + 1;
        iVar6 = iVar6 + 2;
    } while (iVar8 < 4);
}
