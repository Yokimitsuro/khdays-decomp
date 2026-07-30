/*
 * Ov003_DrawStatGrid - draw a 3-row x 4-column grid of stat values with column totals.
 *
 * For each of the 3 rows, walks 4 columns: a cell is filled (drawn as a 3-digit
 * number via func_ov003_0204d264) when the column is the last one or lies within the
 * row's triangular reveal (col < row + 1); otherwise it is painted with the blank
 * tile 0xb03f. Filled cells accumulate a per-column total in buf[]. Afterwards each
 * column total, clamped to 999, is drawn under the grid as a 4-digit number via
 * func_ov003_0204d1c0. Cell values are u16 stats read from the session global
 * (data_0204be18 + 0x1974 + row*8 + col*2); the tilemap base comes from
 * data_ov003_0204f9a0.
 */

extern int data_ov003_0204f9a0;
extern int data_0204be18;
extern void func_ov003_0204d264(unsigned short *dst, unsigned int val, int b);
extern void func_ov003_0204d1c0(unsigned short *dst, unsigned int val);
#pragma opt_strength_reduction off

void func_ov003_0204d55c(void) {
    int c;
    unsigned int uVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    int iVar9;
    int iVar8;

    iVar6 = 0;
    iVar5 = *(int *)(data_ov003_0204f9a0 + 0x1dcc) + 0xc;
    c = 6;
    unsigned short buf[4] = {0, 0, 0, 0};
    do {
            iVar8 = c * 2;
            iVar7 = 0;
            iVar9 = 5;
            do {
                if (iVar7 == 3 || iVar7 < iVar6 + 1) {
                    iVar3 = iVar9 * 0x1a;
                    iVar4 = iVar5 + iVar3 * 2;
                    func_ov003_0204d264((unsigned short *)(iVar4 + iVar8),
                                        (unsigned int)*(unsigned short *)(data_0204be18 + iVar6 * 8 + iVar7 * 2 + 0x1974), 10);
                    buf[iVar7] = buf[iVar7] +
                        *(unsigned short *)(data_0204be18 + iVar6 * 8 + iVar7 * 2 + 0x1974);
                } else {
                    unsigned short blank;
                    iVar3 = iVar9 * 0x1a;
                    iVar4 = iVar5 + iVar3 * 2;
                    *(unsigned short *)(iVar4 + iVar8 + 4) = 0xb03f;
                    blank = *(unsigned short *)(iVar4 + iVar8 + 4);
                    *(unsigned short *)(iVar4 + iVar8 + 2) = blank;
                    *(unsigned short *)(iVar4 + iVar8) = blank;
                }
                iVar7 = iVar7 + 1;
                iVar9 = iVar9 + 2;
            } while (iVar7 < 4);
            iVar6 = iVar6 + 1;
            c = c + 5;
    } while (iVar6 < 3);
    uVar2 = 0x3e7;
    iVar8 = 0;
    iVar6 = 5;
    do {
            if (uVar2 < buf[iVar8]) {
                buf[iVar8] = (unsigned short)uVar2;
            }
            iVar3 = iVar6 * 0x1a;
            iVar4 = iVar5 + iVar3 * 2;
            func_ov003_0204d1c0((unsigned short *)(iVar4 + 0x28),
                                (unsigned int)buf[iVar8]);
            iVar8 = iVar8 + 1;
            iVar6 = iVar6 + 2;
    } while (iVar8 < 4);
}
