/* func_ov000_0204cc90 -- rebuild the ov000 menu layout for the current page.
 *
 * Called every time the menu changes shape (from the boot/logo re-entry state
 * func_ov000_0204ea68 and from the page-change helpers).  Three passes over the ten
 * menu cells held in the scene heap:
 *
 *   1. reset cells 1..9 -- rewind each one to frame 0, commit it and make it visible;
 *      cell 0 is the cursor and is never reset here;
 *   2. hide the cells that do not belong to the current page.  Page 0 shows either the
 *      long list (cells 5,6,7) or the short one (cells 1,2) depending on
 *      extraOptionAvailable; the sub-page shows either cells 3,4 or the alternate pair
 *      8,9 depending on altLayout, and cell 4 also needs loadAvailable;
 *   3. highlight the row the cursor is on -- forward that cell to frame 1 -- and move
 *      cell 0 (the cursor) to the row's y.  The three rows sit at 6.5, 8.25 and 10.0 in
 *      fx32; x is always 0.5.
 *
 * CODEGEN NOTE -- three shapes are load-bearing.  The row dispatch must be a `switch`,
 * not an if/else-if chain: mwcc emits every `cmp`/`beq` up front for a switch and only
 * then the case bodies, which is what the ROM does, and the chain form comes out 12
 * bytes (one branch per dispatch) short.  Declaring `i` before `extraOptionAvailable`
 * is what colours the loop counter into r7 and the flag into r8.  And the position
 * fields have to be written x-then-y even though the ROM stores y first: mwcc emits
 * this pair of stack stores in reverse source order.
 */

typedef unsigned char u8;
typedef signed char   s8;

typedef struct OverlayVector {
    int x;
    int y;
} OverlayVector;

typedef struct Ov000MenuContext {
    u8  pad_0000[0x1b0];
    u8  objectManager[0x4a54];
    int cells[10];              /* 0x4c04 -- cell 0 is the cursor, 1..9 the options */
    u8  pad_4c2c;
    s8  page;                   /* 0x4c2d -- 0 = root page, >0 = sub-page */
    s8  cursorRow[3];           /* 0x4c2e -- selected row, one per page */
    s8  altLayout;              /* 0x4c31 -- sub-page uses cells 8,9 instead of 3,4 */
    u8  pad_4c32[0x21];
    u8  loadAvailable;          /* 0x4c53 -- keeps cell 4 on the sub-page */
    int extraOptionAvailable;   /* 0x4c54 -- root page has three rows, not two */
} Ov000MenuContext;

extern Ov000MenuContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_020325ec(void *mgr, int cell, int frame);
extern void func_020326cc(void *mgr, int cell);
extern void func_02032710(void *mgr, int cell, int visible);
extern void func_0203257c(void *mgr, int cell, const OverlayVector *position);

void func_ov000_0204cc90(void) {
    Ov000MenuContext *ctx;
    int i;
    int extraOptionAvailable;
    int page;
    int row;
    OverlayVector position;

    ctx = NNSi_FndGetCurrentRootHeap();
    extraOptionAvailable = NNSi_FndGetCurrentRootHeap()->extraOptionAvailable;

    for (i = 0; i < 10; i++) {
        if (i != 0) {
            func_020325ec(ctx->objectManager, ctx->cells[i], 0);
            func_020326cc(ctx->objectManager, ctx->cells[i]);
            func_02032710(ctx->objectManager, ctx->cells[i], 1);
        }
    }

    page = ctx->page;
    if (page == 0) {
        func_02032710(ctx->objectManager, ctx->cells[3], 0);
        func_02032710(ctx->objectManager, ctx->cells[4], 0);
        func_02032710(ctx->objectManager, ctx->cells[8], 0);
        func_02032710(ctx->objectManager, ctx->cells[9], 0);
        if (extraOptionAvailable != 0) {
            func_02032710(ctx->objectManager, ctx->cells[1], 0);
            func_02032710(ctx->objectManager, ctx->cells[2], 0);
        } else {
            func_02032710(ctx->objectManager, ctx->cells[5], 0);
            func_02032710(ctx->objectManager, ctx->cells[6], 0);
            func_02032710(ctx->objectManager, ctx->cells[7], 0);
        }
    } else if (page >= 1) {
        func_02032710(ctx->objectManager, ctx->cells[1], 0);
        func_02032710(ctx->objectManager, ctx->cells[2], 0);
        func_02032710(ctx->objectManager, ctx->cells[5], 0);
        func_02032710(ctx->objectManager, ctx->cells[6], 0);
        func_02032710(ctx->objectManager, ctx->cells[7], 0);
        if (ctx->altLayout == 0) {
            if (ctx->loadAvailable == 0) {
                func_02032710(ctx->objectManager, ctx->cells[4], 0);
            }
            func_02032710(ctx->objectManager, ctx->cells[8], 0);
            func_02032710(ctx->objectManager, ctx->cells[9], 0);
        } else {
            func_02032710(ctx->objectManager, ctx->cells[3], 0);
            func_02032710(ctx->objectManager, ctx->cells[4], 0);
            func_02032710(ctx->objectManager, ctx->cells[8], 1);
            func_02032710(ctx->objectManager, ctx->cells[9], 1);
        }
    }

    page = ctx->page;
    if (page == 0) {
        if (extraOptionAvailable != 0) {
            row = ctx->cursorRow[page];
            switch (row) {
            case 0:
                func_020325ec(ctx->objectManager, ctx->cells[5], 1);
                func_020326cc(ctx->objectManager, ctx->cells[5]);
                position.x = 0x8000;
                position.y = 0x68000;
                func_0203257c(ctx->objectManager, ctx->cells[0], &position);
                break;
            case 1:
                func_020325ec(ctx->objectManager, ctx->cells[6], 1);
                func_020326cc(ctx->objectManager, ctx->cells[6]);
                position.x = 0x8000;
                position.y = 0x84000;
                func_0203257c(ctx->objectManager, ctx->cells[0], &position);
                break;
            case 2:
                func_020325ec(ctx->objectManager, ctx->cells[7], 1);
                func_020326cc(ctx->objectManager, ctx->cells[7]);
                position.x = 0x8000;
                position.y = 0xa0000;
                func_0203257c(ctx->objectManager, ctx->cells[0], &position);
                break;
            }
        } else {
            row = ctx->cursorRow[page];
            switch (row) {
            case 0:
                func_020325ec(ctx->objectManager, ctx->cells[1], 1);
                func_020326cc(ctx->objectManager, ctx->cells[1]);
                position.x = 0x8000;
                position.y = 0x84000;
                func_0203257c(ctx->objectManager, ctx->cells[0], &position);
                break;
            case 1:
                func_020325ec(ctx->objectManager, ctx->cells[2], 1);
                func_020326cc(ctx->objectManager, ctx->cells[2]);
                position.x = 0x8000;
                position.y = 0xa0000;
                func_0203257c(ctx->objectManager, ctx->cells[0], &position);
                break;
            }
        }
    } else if (page >= 1) {
        row = ctx->cursorRow[page];
        switch (row) {
        case 0:
            if (ctx->altLayout == 0) {
                func_020325ec(ctx->objectManager, ctx->cells[3], 1);
                func_020326cc(ctx->objectManager, ctx->cells[3]);
            } else {
                func_020325ec(ctx->objectManager, ctx->cells[8], 1);
                func_020326cc(ctx->objectManager, ctx->cells[8]);
            }
            position.x = 0x8000;
            position.y = 0x84000;
            func_0203257c(ctx->objectManager, ctx->cells[0], &position);
            break;
        case 1:
            if (ctx->altLayout == 0) {
                func_020325ec(ctx->objectManager, ctx->cells[4], 1);
                func_020326cc(ctx->objectManager, ctx->cells[4]);
            } else {
                func_020325ec(ctx->objectManager, ctx->cells[9], 1);
                func_020326cc(ctx->objectManager, ctx->cells[9]);
            }
            position.x = 0x8000;
            position.y = 0xa0000;
            func_0203257c(ctx->objectManager, ctx->cells[0], &position);
            break;
        }
    }
}
