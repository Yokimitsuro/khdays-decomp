/*
 * Ov008_Menu_ChangePage - switch the main-menu page and fire its tag callbacks.
 *
 * Copies the per-page tag table (two 8-entry u16-in-u32 arrays: `a` = the page
 * being left, `b` = the page being entered) onto the stack, switches the visible
 * page (func_ov008_0205ea88), marks the head list object's bit, then looks up and
 * invokes the tag-tracker callback for both the outgoing page (indexed by the
 * ctx's current page at +0x70) and the incoming page (`page`). Finally it records
 * the new page/state (ctx +0x70/+0x74/+0x9c) and refreshes the widgets. Returns
 * whether the ctx's +0x78 slot was non-zero.
 */

typedef struct { unsigned int a[8]; unsigned int b[8]; } PageTags;

extern PageTags data_ov008_0208f2e8;
extern int func_ov008_0205ea88(int ctx, int page);
extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern void func_ov008_0205e7ec(int ctx, int bit);
extern int func_ov008_02050c28(void);
extern int func_ov008_02055808(int tracker, unsigned int tag);
extern void func_ov008_0205589c(int *tracker, int entry);
extern void func_ov008_0205f084(int ctx, int a);
extern void func_ov008_0205f3ec(int ctx, int a, int b, int c);

int func_ov008_02063018(int ctx, int page)
{
    PageTags t = data_ov008_0208f2e8;
    int tracker;
    int entry;
    int ret = 1;
    int *obj;

    func_ov008_0205ea88(ctx, page);
    obj = (int *)NNS_FndGetNextListObject(*(void **)(ctx + 0x300), 0);
    if (obj != 0) {
        func_ov008_0205e7ec(ctx, *(int *)(*obj + 0x14));
    }
    if (*(int *)(ctx + 0x78) == 0) ret = 0;
    tracker = func_ov008_02050c28();
    entry = func_ov008_02055808(tracker, t.a[*(int *)(ctx + 0x70)] & 0xffff);
    func_ov008_0205589c((int *)tracker, entry);
    entry = func_ov008_02055808(tracker, t.b[page] & 0xffff);
    func_ov008_0205589c((int *)tracker, entry);
    *(int *)(ctx + 0x74) = 0;
    *(int *)(ctx + 0x70) = page;
    *(int *)(ctx + 0x9c) = 0;
    func_ov008_0205f084(ctx, 0);
    func_ov008_0205f3ec(ctx, *(int *)(ctx + 0x78), 8, 0x7f);
    return ret;
}
