/* Install the panel handlers once, then pass the call on.
 *
 * The four handler addresses go into the context at 0x230 only while the mode word at 0x60 is
 * still zero, so this runs its setup on the first pass and is a plain forward afterwards.
 *
 * The parameter is never used here, and that is not an oversight: it is handed to the routine this
 * one tails into. The original keeps it in r0 from entry to exit and starts its own temporaries at
 * r1, which is the only reason to know it exists.
 *
 * Ghidra carries the slots as aHandlers and the gate as nPanelMode on Ov002PanelContext.
 */

typedef void (*Ov002PanelHandler)(void);

extern char *data_ov002_0207f614;
extern void func_ov002_02054e2c(void);
extern void func_ov002_02055888(void);
extern void func_ov002_02055900(void);
extern void func_ov002_02055934(void);
extern void func_ov002_02062f6c(int a);

void func_ov002_02057684(int a) {
    char *ctx = data_ov002_0207f614;

    if (*(int *)(ctx + 0x60) == 0) {
        *(Ov002PanelHandler *)(ctx + 0x230) = func_ov002_02054e2c;
        *(Ov002PanelHandler *)(ctx + 0x234) = func_ov002_02055888;
        *(Ov002PanelHandler *)(ctx + 0x238) = func_ov002_02055900;
        *(Ov002PanelHandler *)(ctx + 0x23c) = func_ov002_02055934;
    }
    func_ov002_02062f6c(a);
}
