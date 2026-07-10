/*
 * NONMATCHING (DAT/counter register-swap tie, size-exact byte-diff @0x11). The
 * fn-ptr-table dispatch matched via a switch (both cmps first, cases out-of-line),
 * the 3-arg leftover indirect calls (iVar3 in r1), and the loop all match. Only
 * the coloring differs: orig DAT1/DAT2 in r4/r5 and iVar6/iVar7 in r6/r7, mwcc
 * the reverse. Tried hoisting the DAT bases into locals. Byte-equivalent.
 */
extern int data_ov022_020b2b58;
extern int data_ov022_020b2b48;

void func_ov022_02090e2c(int param_1, int param_2) {
    int iVar6 = 0;
    if (0 < (int)*(unsigned char *)(param_1 + 0x19)) {
        int iVar7 = 0;
        do {
            int iVar3 = *(int *)(param_1 + 0xc) + iVar7;
            int iVar4 = *(char *)(iVar3 + 2);
            if (iVar4 != 0) {
                switch (*(int *)(param_1 + 4)) {
                case 1:
                    (*(void (**)(int, int, int))((int)&data_ov022_020b2b48 + iVar4 * 4))(
                        param_1, iVar3, param_2);
                    break;
                case 2:
                    (*(void (**)(int, int, int))((int)&data_ov022_020b2b58 + iVar4 * 4))(
                        param_1, iVar3, param_2);
                    break;
                }
            }
            iVar6 = iVar6 + 1;
            iVar7 = iVar7 + 0x1c8;
        } while (iVar6 < (int)*(unsigned char *)(param_1 + 0x19));
    }
}
