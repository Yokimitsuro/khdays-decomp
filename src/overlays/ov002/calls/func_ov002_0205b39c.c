/*
 * Ov002_DrawPanelRowText - write the text of all eight panel rows into the
 * five 0x3c-byte surfaces the caller hands over.
 *
 * Each row is classified first, and the class decides what is written. Class 0
 * is the fixed six-line block: the first line follows the mission-clear check,
 * the next two read the word at +0x24 of the session walked four bytes at a
 * time, and the last three are numbered from the line index. Class 1 walks six
 * cells of the row and writes the ones that are not 0xff, in the left or right
 * column depending on whether the row is the first. Classes 2 and 3 share a
 * body - class 3 just looks two rows further on - and write six named entries,
 * falling back to the spare string when the lookup finds nothing.
 *
 * The font goes into the block at +0x110 afterwards, and the last surface gets
 * its three fixed lines.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad0000[0x24];
    int nField0024;                     /* +0x024 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;
extern char data_ov002_0207eadc[];
extern char data_ov002_0207eaf4[];
extern int data_ov002_0207eb08[];
extern int data_ov002_0207eb0c[];

extern void func_0202ff58(void *pField, const void *pTable);
extern void func_0202ff7c(void *pField);
extern void func_02030278(void *pSurface, int a, int b, int c, void *pText,
                          int d);
extern int func_ov002_020573f8(void);
extern int func_ov002_020575d0(void);
extern void func_ov002_0205280c(void *pSet, const void *pTable);
extern void func_ov002_02052834(void *pSet);
extern int *func_ov002_02052844(void *pSet, int nIndex);
extern int func_ov002_0205a3f0(int *pOut, int nIndex);
extern void func_ov002_0205b380(void *pSurface, int nFont, void *pBind,
                                int *pText);
extern int *func_ov002_0206d084(int nName);

void func_ov002_0205b39c(char *pDst)
{
    Ov002PanelSession *s;
    Ov002PanelSession *pWalk;
    int *pText;
    int nIndex;
    int nFont;
    int nRow;
    int nCode;
    int nClass;
    int nSelect;
    int nColumn;
    int i;
    int nY;
    int nX;
    u16 nName;
    int aRecords[3];
    int aBind[3];

    s = data_ov002_0207f620;
    func_0202ff58(aBind, data_ov002_0207eadc);
    nFont = func_ov002_020573f8();
    func_ov002_0205280c(aRecords, data_ov002_0207eaf4);

    /* The y cursor is claimed here rather than in the class-2 body: with its
       live range starting before the switch, mwcc gives it the same register
       the ROM does and the whole block's allocation falls into place. */
    nY = 0;
    nIndex = 0;
    nRow = 0;
    do {
        nClass = func_ov002_0205a3f0(&nCode, nIndex);
        switch (nClass) {
        case 0:
            pWalk = s;
            i = 0;
            do {
                switch (i) {
                case 0:
                    if (func_ov002_020575d0() != 0) {
                        nSelect = 7;
                    } else {
                        nSelect = 0;
                    }
                    break;
                case 1:
                case 2:
                    nSelect = pWalk->nField0024 + 5;
                    break;
                case 3:
                case 4:
                case 5:
                    nSelect = i - 2;
                    break;
                }
                pText = func_ov002_02052844(aRecords, nSelect);
                func_ov002_0205b380(pDst, nFont, aBind, pText);
                func_02030278(pDst, 0, (nRow + i * 2) * 8 + 3, 2, pText, 1);
                pWalk = (Ov002PanelSession *)((char *)pWalk + 4);
                i++;
            } while (i < 6);
            break;

        case 1:
            if (nCode < 1) {
                nColumn = 0;
                nY = 0x60;
            } else {
                nColumn = 1;
                nY = (nCode - 1) * 0x60;
            }
            nX = nColumn * 0x3c;
            i = 0;
            do {
                if (i + nCode * 6 < 0xf
                    && *((u8 *)s + (i + nCode * 6) * 2 + 0x32) != 0xff) {
                    pText = func_ov002_02052844((char *)s + 0x5e8,
                                                *((u8 *)s + (i + nCode * 6) * 2 + 0x32));
                    func_ov002_0205b380(pDst + nX, nFont, aBind, pText);
                    func_02030278(pDst + nX, 0, nY + 3, 2, pText, 1);
                }
                i++;
                nY += 0x10;
            } while (i < 6);
            break;

        case 2:
        case 3:
            if (nClass == 3) {
                nCode += 2;
            }
            if (nCode < 2) {
                nColumn = 2;
            } else {
                nColumn = 3;
            }
            nY = nCode % 2 * 0x60;
            nX = nColumn * 0x3c;
            i = 0;
            do {
                nName = *(u16 *)((char *)s + (i + nCode * 6) * 0xc + 0x4b8);
                if (nName != 0) {
                    pText = func_ov002_0206d084((short)nName);
                    func_ov002_0205b380(pDst + nX, nFont, aBind, pText);
                    if (pText == 0) {
                        pText = data_ov002_0207eb08;
                    }
                    func_02030278(pDst + nX, 0, nY + 3, 2, pText, 1);
                }
                i++;
                nY += 0x10;
            } while (i < 6);
            break;
        }
        nRow += 0xc;
        nIndex++;
    } while (nIndex <= 7);

    *(int *)(pDst + 0x110) = nFont;
    func_02030278(pDst + 0xf0, 0, 3, 2, data_ov002_0207eb0c, 1);
    func_02030278(pDst + 0xf0, 0, 0x13, 2, func_ov002_02052844(aRecords, 4), 1);
    func_02030278(pDst + 0xf0, 0, 0x23, 2, func_ov002_02052844(aRecords, 5), 1);
    func_ov002_02052834(aRecords);
    func_0202ff7c(aBind);
}
