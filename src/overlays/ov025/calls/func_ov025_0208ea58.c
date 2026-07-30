/* func_ov025_0208ea58 -- Ov008_DrawMenuPanels (136 B, 9 relocs).
 * Redraws the menu's cell panels. After two refresh hooks (func_ov025_0208e1fc /
 * func_ov025_0208e4f0), it walks the 12 panel surfaces (stride 0x108 starting at ctx+0x590),
 * and for each whose gate entry data_ov025_020b3bb0[i] is non-negative it binds the surface to
 * the shared resource (*ctx) via func_0202a818 and enqueues it via func_0202aa9c. Finally it
 * binds+enqueues the two fixed surfaces at ctx+0x488 and ctx+0x380 unconditionally. */
extern int  data_ov025_020b3bb0[];
extern void func_ov025_0208e1fc(void *ctx);
extern void func_ov025_0208e4f0(void *ctx);
extern void func_0202a818(void *dst, int val);
extern void func_0202aa9c(void *dst);

void func_ov025_0208ea58(void *ctx)
{
    int i;
    char *slot;

    func_ov025_0208e1fc(ctx);
    func_ov025_0208e4f0(ctx);
    slot = (char *)ctx + 0x590;
    for (i = 0; i < 0xc; i++) {
        if (data_ov025_020b3bb0[i] >= 0) {
            func_0202a818(slot, *(int *)ctx);
            func_0202aa9c(slot);
        }
        slot += 0x108;
    }
    func_0202a818((char *)ctx + 0x488, *(int *)ctx);
    func_0202aa9c((char *)ctx + 0x488);
    func_0202a818((char *)ctx + 0x380, *(int *)ctx);
    func_0202aa9c((char *)ctx + 0x380);
}
