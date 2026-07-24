/* func_ov000_0204e5b0 -- the ov000 menu's interactive loop.
 *
 * The state func_ov000_0204e270 hands off to once the fade-in finishes, and the one the
 * page transitions come back to.  Per frame it services input, finishes the cross-fade,
 * redraws, dispatches the selection and watches the idle timer.
 *
 * Input is held off until the transition object at data_0204c18c reports idle; from then
 * on func_ov000_0204d244 advances the cursor row for the current page.  A/Start counts as
 * confirm (key mask 9), B as cancel (mask 2).
 *
 * Confirm on the root page: row 0 arms the sub-page (cursorRow[1] pre-selected when a save
 * exists, altLayout off) and pushes pendingPage; row 1 arms the alternate sub-page layout
 * with pendingPage 2; row 2 only works when extraOptionAvailable is set and leaves for
 * func_ov000_0204f36c.  Confirm on a sub-page leaves for func_ov000_0204f51c or
 * func_ov000_0204ef84 depending on altLayout.  Cancel pops a page -- twice when the page is
 * deeper than 1 -- and returns to the transition state func_ov000_0204e9a4.
 *
 * The idle timer is restarted while the transition object is busy.  Once 0x69 = 105 seconds
 * have passed with nothing pressed it fires func_02033fec(0, 0x1e) and hands off to
 * func_ov000_0204f47c, i.e. the attract sequence.
 *
 * CODEGEN NOTE -- two shapes are load-bearing.  The two pendingPage decrements have to be
 * compound assignments (`-= 1`): a compound assignment evaluates the lvalue address once, so
 * mwcc binds a pointer to the field and loads/stores through it at offset 0, whereas
 * `x = x - 1` recomputes the address on each side and reaches the field through two
 * different bases.  And the idle test has to be written as the POSITIVE guard
 * (`if (elapsed > 0x69) { ...; return next; } return 0;`); with the early-out spelling mwcc
 * schedules the pool load of the next state ahead of the counter store.
 */
typedef unsigned char u8;
typedef signed char   s8;
typedef unsigned int  u32;
typedef void         *StateFn;

typedef struct Ov000MenuContext {
    int       counter;
    u8        pad_0004[8];
    u8        node[0x108];
    u8        scrollBounds[0x9c];
    u8        pad_01b0[0x4a38];
    u8        inputSource[0x1c];
    u8        pad_4c04[0x28];
    s8        pendingPage;
    s8        page;
    s8        cursorRow[3];
    s8        altLayout;
    u8        pad_4c32[0x21];
    u8        loadAvailable;
    int       extraOptionAvailable;
    int       inputReady;
    u8        pad_4c5c[8];
    long long enterTick;
} Ov000MenuContext;

extern unsigned short data_0204c18c;
extern unsigned short data_0204c190;

extern Ov000MenuContext *NNSi_FndGetCurrentRootHeap(void);
extern void      func_ov000_0204d354(void);
extern void      FS_UnloadOverlayImage_0x020362ec(void *image);
extern int       func_ov000_0204d244(void *input, int selection, int group);
extern void      func_0201e3cc(int brightness);
extern void      G2x_SetBlendAlpha_(u32 reg, int a, int b, int c, int d);
extern void      func_ov000_0204cc90(void);
extern void      func_ov000_0204d208(void);
extern void      func_02023d70(void *bounds, int a, int b, int c, int d);
extern void      func_0202aa9c(void *node);
extern void      func_02033b78(int a, int b);
extern long long func_020031d4(void);
extern unsigned long long func_02020368(unsigned long long value, unsigned int divisor,
                                        int arg3);
extern void      func_02033fec(int a, int b);
extern void      func_ov000_0204e9a4(void);
extern void      func_ov000_0204f36c(void);
extern void      func_ov000_0204f51c(void);
extern void      func_ov000_0204ef84(void);
extern void      func_ov000_0204f47c(void);

StateFn func_ov000_0204e5b0(void) {
    Ov000MenuContext *ctx;
    int confirm;
    int cancel;

    ctx = NNSi_FndGetCurrentRootHeap();
    confirm = 0;
    cancel = 0;
    func_ov000_0204d354();
    if (ctx->inputReady != 0) {
        FS_UnloadOverlayImage_0x020362ec(ctx->inputSource);
        ctx->cursorRow[ctx->page] = func_ov000_0204d244(ctx->inputSource,
                                                        ctx->cursorRow[ctx->page],
                                                        ctx->page);
    } else if (data_0204c18c == 0) {
        ctx->inputReady = 1;
    }

    if (ctx->counter < 0x3c) {
        func_0201e3cc(0x10);
        ctx->counter = ctx->counter + 1;
    } else if (ctx->counter <= 0x5c) {
        func_0201e3cc(0x10 - (ctx->counter - 0x3c) / 2);
        G2x_SetBlendAlpha_(0x04001050, 0x10, 0x22, (ctx->counter - 0x3c) / 2,
                           0x10 - (ctx->counter - 0x3c) / 2);
        ctx->counter = ctx->counter + 1;
    } else {
        func_0201e3cc(0);
        G2x_SetBlendAlpha_(0x04001050, 0x10, 0x22, 0x10, 0);
    }

    func_ov000_0204cc90();
    func_ov000_0204d208();
    if ((data_0204c190 & 9) != 0) {
        confirm = 1;
    } else if ((data_0204c190 & 2) != 0) {
        cancel = 1;
    }
    func_02023d70(ctx->scrollBounds, 0x3b33, -0x3b33, -0x4d9a, 0x4d9a);
    func_0202aa9c(ctx->node);

    if (confirm != 0) {
        if (ctx->page == 0) {
            switch (ctx->cursorRow[ctx->page]) {
            case 0:
                if (ctx->page + 1 != 3) {
                    func_02033b78(0, 1);
                    ctx->counter = 0;
                    if (ctx->loadAvailable != 0) {
                        ctx->cursorRow[1] = 1;
                    }
                    ctx->altLayout = 0;
                    ctx->pendingPage = ctx->pendingPage + 1;
                    return (StateFn)func_ov000_0204e9a4;
                }
                break;
            case 1:
                func_02033b78(0, 1);
                ctx->counter = 0;
                ctx->altLayout = 1;
                ctx->pendingPage = 2;
                return (StateFn)func_ov000_0204e9a4;
            case 2:
                if (NNSi_FndGetCurrentRootHeap()->extraOptionAvailable != 0) {
                    func_02033b78(0, 1);
                    ctx->counter = 0;
                    return (StateFn)func_ov000_0204f36c;
                }
                break;
            }
        } else if (ctx->page >= 1) {
            ctx->counter = 0;
            switch (ctx->cursorRow[ctx->page]) {
            case 0:
                func_02033b78(0, 1);
                if (ctx->altLayout == 0) {
                    return (StateFn)func_ov000_0204f51c;
                }
                return (StateFn)func_ov000_0204ef84;
            case 1:
                func_02033b78(0, 1);
                return (StateFn)func_ov000_0204ef84;
            }
        }
    } else if (cancel != 0 && ctx->page != 0) {
        func_02033b78(0, 3);
        ctx->pendingPage -= 1;
        if (ctx->page > 1) {
            ctx->pendingPage -= 1;
        }
        ctx->counter = 0;
        return (StateFn)func_ov000_0204e9a4;
    }

    if (ctx->inputReady != 0 && data_0204c18c != 0) {
        ctx->enterTick = func_020031d4();
    }
    if (func_02020368((func_020031d4() - ctx->enterTick) << 6, 0x01ff6210, 0) > 0x69) {
        func_02033fec(0, 0x1e);
        ctx->counter = 0;
        return (StateFn)func_ov000_0204f47c;
    }
    return 0;
}
