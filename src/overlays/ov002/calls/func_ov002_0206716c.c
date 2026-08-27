/*
 * Refreshes the link page for one step of the list.
 *
 * The step's entry is fetched and its packed descriptor decides which of the
 * page's two bases the artwork comes from; the descriptor's low nine bits and
 * the chosen base, quartered and shifted into place under the top bit, make the
 * word the appender takes.
 *
 * The two arrow cues are cleared and then re-armed from where the step sits in
 * the list: the forward arrow only while a next entry exists, the back arrow
 * only while the index is not the first, and each transition plays its own cue.
 *
 * The rest lays out the page's widgets, six of them, whose kind depends on
 * whether the list holds more than one entry and whether the page carries its
 * extra pair.
 *
 * One thing here is load-bearing rather than style. The widget kind is assigned
 * in both arms of the bias branch, not once after it. Assigned after the branch
 * the compiler folds it into an immediate add and the function comes out one
 * instruction short; assigned in both arms it stays in a register across the
 * calls, which is what the original does.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002LinkWidget {
    char pad000[0x3c];
} Ov002LinkWidget;

typedef struct Ov002LinkPage {
    char pad000[2];
    u16 nIndex;
    int nBase4;
    int nBase8;
    char sub00c[0x18];
    int nArg;
    char pad028[8];
    int bExtra;
    Ov002LinkWidget aWidgets[7];
} Ov002LinkPage;

extern Ov002LinkPage *data_ov002_0207f9fc;

extern u32 func_ov002_02067988(void *pSub, int nStep);
extern void func_ov002_02052a6c(u32 nPacked, void *pHandler, int nArg);
extern int func_ov002_020536bc(int nTag);
extern void func_ov002_02053700(int hEntry);
extern void func_ov002_020536dc(int hEntry, int bArmed);
extern int func_ov002_02053558(int nId);
extern void func_ov002_020535f0(int hSound);
extern int func_ov002_02067980(void *pSub);
extern int func_ov002_02067978(void *pSub);
extern int func_ov002_02067994(void *pSub);
extern int func_ov002_02067150(void);
extern void func_020301c8(void *pWidget, int a, int b, int c, int d, int e);
extern void func_020300f8(void *pWidget);
extern void func_ov002_0205287c(void *pWidget, int a, void *pOut, int b,
                                int c, int d);
extern void func_ov002_02067120(void *pWidget, int a, int b, int c, void *p);
extern void func_ov002_02067078(void);

void func_ov002_0206716c(int nStep, int nArg)
{
    Ov002LinkPage *pCtx;
    u32 nPacked;
    int nCount;
    int nSlot;
    int nKind;
    int nBias;
    char aTmp[0x20];

    pCtx = data_ov002_0207f9fc;
    pCtx->nArg = nArg;
    nPacked = func_ov002_02067988(pCtx->sub00c, nStep);
    if ((nPacked & 0x10000) != 0) {
        func_ov002_02052a6c((((pCtx->nBase8 + 0x8000) & 0xfffffc) << 7)
                            | 0x80000000
                            | (nPacked & 0x1ff),
                            func_ov002_02067078, 0);
    } else {
        func_ov002_02052a6c((((pCtx->nBase4 + 0x8000) & 0xfffffc) << 7)
                            | 0x80000000
                            | (nPacked & 0x1ff),
                            func_ov002_02067078, 0);
    }

    func_ov002_02053700(func_ov002_020536bc(0x16));
    func_ov002_02053700(func_ov002_020536bc(0x15));

    nCount = func_ov002_02067980(pCtx->sub00c);
    if (pCtx->nIndex + 1 < nCount) {
        func_ov002_020535f0(func_ov002_02053558(0x518));
        func_ov002_020536dc(func_ov002_020536bc(0x16), 1);
        func_ov002_020536dc(func_ov002_020536bc(0x17), 0);
    } else {
        func_ov002_020535f0(func_ov002_02053558(0x516));
        func_ov002_020536dc(func_ov002_020536bc(0x16), 0);
        func_ov002_020536dc(func_ov002_020536bc(0x17), 1);
    }

    if (pCtx->nIndex != 0) {
        func_ov002_020536dc(func_ov002_020536bc(0x15), 1);
    } else {
        func_ov002_020535f0(func_ov002_02053558(0x514));
        func_ov002_020536dc(func_ov002_020536bc(0x15), 0);
    }

    func_020301c8(&pCtx->aWidgets[0], 0x54, 6, 2, 0x411,
                  func_ov002_02067978(pCtx->sub00c));
    func_020300f8(&pCtx->aWidgets[0]);

    func_ov002_0205287c(&pCtx->aWidgets[6], 0, aTmp, 0x10, nStep + 1,
                        func_ov002_02067980(pCtx->sub00c));
    func_ov002_02067120(&pCtx->aWidgets[1], 4, 7, 2, aTmp);

    if (pCtx->bExtra != 0) {
        nBias = 5;
        nKind = 2;
    } else {
        nBias = 0;
        nKind = 2;
    }

    nSlot = func_ov002_02067994(pCtx->sub00c);
    func_ov002_02067120(&pCtx->aWidgets[2], 0,
                        (func_ov002_02067150() > 1 ? 0 : 5) + 4, 2,
                        (void *)nSlot);

    nSlot = func_ov002_02067994(pCtx->sub00c);
    func_ov002_02067120(&pCtx->aWidgets[3], nBias,
                        nKind + (func_ov002_02067150() > 1 ? 0 : 5), 2,
                        (void *)nSlot);

    if (pCtx->bExtra != 0) {
        func_ov002_02067120(&pCtx->aWidgets[4], 5, 6, 2,
                            (void *)func_ov002_02067994(pCtx->sub00c));
        func_ov002_02067120(&pCtx->aWidgets[5], 5, 2, 2,
                            (void *)func_ov002_02067994(pCtx->sub00c));
    }
}
