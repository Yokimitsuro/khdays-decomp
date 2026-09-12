/* func_ov008_0206ec2c -- Ov008_DrawPageBWidget: draw page-B element nKind with
 * argument nArg while the gate at data_ov008_02090f20 is set.  The nine
 * widget-id pairs of data_ov008_0208f7b0 (0x48 bytes) are copied to the stack;
 * kinds 2, 3, 5, 6, 7, 9, 0xb, 0xc, 0xd map to pairs 0, 1, 2, 3, 4, 6, 8, 5, 7
 * (cases written in pair order so the bodies lie in the ROM's order) and first
 * go through Ov008_SetPairSelection, whose result is handed to the
 * draw (0206d46c) together with a pointer to the trailing arguments (va_start
 * after nArg) and flag 0.
 */
typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

#define PAIR_COUNT 9

typedef struct Ov008WidgetPair {
    int nFirst;
    int nSecond;
} Ov008WidgetPair;

typedef struct Ov008WidgetPairTable {
    Ov008WidgetPair aPair[PAIR_COUNT];
} Ov008WidgetPairTable;

extern const Ov008WidgetPairTable data_ov008_0208f7b0;
extern int data_ov008_02090f20;                                          /* draw gate */
extern void *func_ov008_02050cec(void);                                  /* Ov008_GetPageB */
extern void func_ov008_02050c64(void);                                   /* Ov008_GetCtxBlock4a80 */
extern int  func_ov008_0206e320(void *pPage, Ov008WidgetPair *pPair, int nArg); /* Ov008_SetPairSelection */
extern void func_ov008_0206d46c(void *pPage, int nKind, int nArg, int nSelection, void *pExtra, int nFlag);

void func_ov008_0206ec2c(int nKind, int nArg, ...)
{
    void *pPage;
    int nPair;
    int nSelection;
    Ov008WidgetPairTable pairs;
    va_list ap;

    pPage = func_ov008_02050cec();
    nPair = -1;
    nSelection = 0;
    pairs = data_ov008_0208f7b0;
    if (data_ov008_02090f20 == 0) {
        return;
    }
    func_ov008_02050c64();
    switch (nKind) {
    case 2:   nPair = 0; break;
    case 3:   nPair = 1; break;
    case 5:   nPair = 2; break;
    case 6:   nPair = 3; break;
    case 7:   nPair = 4; break;
    case 0xc: nPair = 5; break;
    case 9:   nPair = 6; break;
    case 0xd: nPair = 7; break;
    case 0xb: nPair = 8; break;
    }
    if (nPair >= 0) {
        nSelection = func_ov008_0206e320(pPage, &pairs.aPair[nPair], nArg);
    }
    va_start(ap, nArg);
    func_ov008_0206d46c(pPage, nKind, nArg, nSelection, ap, 0);
}
