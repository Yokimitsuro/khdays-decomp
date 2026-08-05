/*
 * Ov008_Menu_ChangePage - switch the main-menu page and fire its tag callbacks.
 *
 * Copies the per-page tag table (two 8-entry u16-in-u32 arrays: `a` = the page
 * being left, `b` = the page being entered) onto the stack, switches the visible
 * page (func_ov025_02090ffc), marks the head list object's bit, then looks up and
 * invokes the tag-tracker callback for both the outgoing page (indexed by the
 * ctx's current page at +0x70) and the incoming page (`page`). Finally it records
 * the new page/state (ctx +0x70/+0x74/+0x9c) and refreshes the widgets. Returns
 * whether the ctx's +0x78 slot was non-zero.
 */

typedef struct { unsigned int a[8]; unsigned int b[8]; } PageTags;

extern PageTags data_ov025_020b3e48;
extern int func_ov025_02090ffc(int ctx, int page);
extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern void func_ov025_02090d60(int ctx, int bit);
extern int func_ov025_02084a50(void);
extern int func_ov025_020894b0(int tracker, unsigned int tag);
extern void func_ov025_02089544(int *tracker, int entry);
extern void func_ov025_020915d4(int ctx, int a);
extern void func_ov025_0209193c(int ctx, int a, int b, int c);

int func_ov025_02095544(int ctx, int page)
{
    PageTags t = data_ov025_020b3e48;
    int tracker;
    int entry;
    int ret = 1;
    int *obj;

    func_ov025_02090ffc(ctx, page);
    obj = (int *)NNS_FndGetNextListObject(*(void **)(ctx + 0x300), 0);
    if (obj != 0) {
        func_ov025_02090d60(ctx, *(int *)(*obj + 0x14));
    }
    if (*(int *)(ctx + 0x78) == 0) ret = 0;
    tracker = func_ov025_02084a50();
    entry = func_ov025_020894b0(tracker, t.a[*(int *)(ctx + 0x70)] & 0xffff);
    func_ov025_02089544((int *)tracker, entry);
    entry = func_ov025_020894b0(tracker, t.b[page] & 0xffff);
    func_ov025_02089544((int *)tracker, entry);
    *(int *)(ctx + 0x74) = 0;
    *(int *)(ctx + 0x70) = page;
    *(int *)(ctx + 0x9c) = 0;
    func_ov025_020915d4(ctx, 0);
    func_ov025_0209193c(ctx, *(int *)(ctx + 0x78), 8, 0x7f);
    return ret;
}
