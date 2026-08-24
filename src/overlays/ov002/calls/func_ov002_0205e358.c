/* Ov002_PanelAddSubEntryAndRepaint - add a sub-entry, then repaint what it touched.
 *
 * The entry is added first and its handle kept for the return. The panel's
 * current mode is refreshed, then the classifier is run over the caller's code
 * to decide how much of the screen has to be redrawn: a column move repaints
 * one strip of the list, and a list move first disarms the tag tracker unless
 * something still holds it, then repaints the sub-list group, its strip, and
 * the row the running key falls on.
 *
 * THUMB. Two arguments, not four: the third and fourth registers are never read,
 * and the pushed r3 slot is only ever the classifier's out parameter - the
 * prologue pushes r3 as the cheap way to reserve that word.
 */
typedef unsigned char u8;

typedef struct {
    u8 bKind;                           /* +0x00 */
    u8 bMode;                           /* +0x01 */
    u8 bIndex;                          /* +0x02 */
    u8 bPanelRow;                       /* +0x03 */
    u8 bKey;                            /* +0x04 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_0205cda8(unsigned int nKey, int nTag);
extern void func_ov002_0205cc44(void);
extern int func_ov002_0205a3f0(int *pnCode, int nMode);
extern void func_ov002_0205a924(int nCount, int nRows, int nX, int nY);
extern int func_ov002_020536bc(int nTag);
extern int func_ov002_0205374c(int nEntry);
extern int func_ov002_02053558(int nId);
extern int func_ov002_020535f0(int nHandle);
extern void func_ov002_0205c87c(int nGroup);
extern long long func_02020400(int nNumerator, int nDenominator);
extern void func_ov002_0205b7dc(int nMode, int nKind, int nFlag);

int func_ov002_0205e358(unsigned int nKey, int nTag)
{
    Ov002PanelSession *pSess;
    int nHandle;
    int nBase;
    int nColumn;

    pSess = data_ov002_0207f620;
    nHandle = func_ov002_0205cda8(nKey, nTag);
    func_ov002_0205cc44();

    switch (func_ov002_0205a3f0(&nColumn, pSess->bMode)) {
    case 2:
        func_ov002_0205a924(nColumn + 1,
                            *(u8 *)((u8 *)pSess + 0x4ac) +
                                *(u8 *)((u8 *)pSess + 0x4ad),
                            7, 0xb);
        break;
    case 3:
        if (func_ov002_0205374c(func_ov002_020536bc(0xe)) == 0) {
            func_ov002_020535f0(func_ov002_02053558(0x79));
        }
        func_ov002_0205c87c(nColumn);
        nBase = *(u8 *)((u8 *)pSess + 0x4ac);
        func_ov002_0205a924(nBase + nColumn + 1,
                            nBase + *(u8 *)((u8 *)pSess + 0x4ad),
                            7, 0xb);
        func_ov002_0205b7dc(pSess->bMode,
                            (int)((unsigned long long)func_02020400(pSess->bKey, 6) >> 32),
                            1);
        break;
    }
    return nHandle;
}
