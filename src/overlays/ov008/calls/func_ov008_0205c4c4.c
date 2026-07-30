/* func_ov008_0205c4c4 -- Ov008_DrawMenuPanels (136 B, 9 relocs).
 * Redraws the menu's cell panels. After two refresh hooks (func_ov008_0205bc68 /
 * func_ov008_0205bf5c), it walks the 12 panel surfaces (stride 0x108 starting at ctx+0x590),
 * and for each whose gate entry data_ov008_0208f050[i] is non-negative it binds the surface to
 * the shared resource (*ctx) via func_0202a818 and enqueues it via func_0202aa9c. Finally it
 * binds+enqueues the two fixed surfaces at ctx+0x488 and ctx+0x380 unconditionally. */
extern int  data_ov008_0208f050[];
extern void func_ov008_0205bc68(void *ctx);
extern void func_ov008_0205bf5c(void *ctx);
extern void func_0202a818(void *dst, int val);
extern void func_0202aa9c(void *dst);

void func_ov008_0205c4c4(void *ctx)
{
    int i;
    char *slot;

    func_ov008_0205bc68(ctx);
    func_ov008_0205bf5c(ctx);
    slot = (char *)ctx + 0x590;
    for (i = 0; i < 0xc; i++) {
        if (data_ov008_0208f050[i] >= 0) {
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
