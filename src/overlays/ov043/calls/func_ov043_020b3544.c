/* Mode change of the mission enemy, the handler installed in slot 0 of its table. Against
 * the mission owner's +0x2d38 block: 0x2e binds the block (4860) and clears its +8 latch,
 * 0x2f raises the latch once and runs the 4b20 pass, 0x30 requests sound 0xc4 variant 1,
 * 0x31 runs the 4b44 pass -- each only when the mode actually changes. 0x32 is handed down
 * as mode 1 and then recorded as the current mode (+0x6bc) afterwards. */
extern void func_ov043_020b4860(char *self);
extern void func_ov043_020b4b20(char *self, char *pBlock);
extern void func_ov022_020a4490(char *self, int nSound, int nVariant);
extern void func_ov043_020b4b44(char *self, char *pBlock);
extern void func_ov022_020a384c(char *self, int nState);
extern char *data_ov043_020b58e0;

void func_ov043_020b3544(char *self, int nState)
{
    char *pBlock = data_ov043_020b58e0 + 0x138 + 0x2c00;
    int nRecord = -1;

    switch (nState) {
    case 0x2e:
        if (*(int *)(self + 0x6bc) != nState) {
            func_ov043_020b4860(self);
            *(int *)(pBlock + 8) = 0;
        }
        break;
    case 0x2f:
        if (*(int *)(self + 0x6bc) != nState) {
            if (*(int *)(pBlock + 8) == 0) {
                *(int *)(pBlock + 8) = 1;
                func_ov043_020b4b20(self, pBlock);
            }
        }
        break;
    case 0x30:
        if (*(int *)(self + 0x6bc) != nState) {
            func_ov022_020a4490(self, 0xc4, 1);
        }
        break;
    case 0x31:
        if (*(int *)(self + 0x6bc) != nState) {
            func_ov043_020b4b44(self, pBlock);
        }
        break;
    case 0x32:
        nState = 1;
        nRecord = 0x32;
        break;
    }
    func_ov022_020a384c(self, nState);
    if (nRecord >= 0) {
        *(int *)(self + 0x6bc) = nRecord;
    }
}
