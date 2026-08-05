/*
 * Ov008_Menu_RenderScenePanels - per-frame render and gfx submit of the menu scene's
 * two panel widgets, called from Ov008_Menu_AdvanceIntoPanel.
 *
 * Updates the scene sprite node (obj+0x38) with the current scroll base (obj+0x1b0) and
 * renders it, then for each active panel slot submits its widget:
 *   - slot 1 (valid flag obj+0x140): panel obj+0x1b8, matrix obj+0x150;
 *   - slot 2 (valid flag obj+0x144): panel obj+0x31c, matrix obj+0x180.
 * For each active panel it reads the node's current anim frame, commits the widget scroll
 * (obj+0x480 output), scales the panel matrix to 100.0 (0x64000 in fx32) when the scene is
 * in state 0xd, applies the matrix to the panel object and submits its gfx.
 *
 * Callee arity (Ghidra invents trailing r2/r3 args from the scale block): func_0202aa9c
 * (RenderNode) takes 1 arg, func_ov025_0208c5b8 (SubmitObjectGfx) takes 1 arg. The two
 * scale constants Ghidra threads into SubmitObjectGfx are only live on the state-0xd path.
 */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern void func_0202a818(u16 *node, int scrollBase);
extern void func_0202aa9c(u16 *node);
extern int  func_0202aee0(u16 *node, int a);
extern void func_ov025_0208c7dc(int panel, int out, int scrollBase, int frame);
extern void MTX_ScaleApply43(int *dst, u32 *src, int sx, int sy, int sz);
extern void func_ov025_0208c634(void *panel, void *mtx);
extern void func_ov025_0208c5b8(u8 *panel);

void func_ov025_0208cbc8(int obj)
{
    int frame;
    int scrollBase;

    func_0202a818((u16 *)(obj + 0x38), *(int *)(obj + 0x1b0));
    func_0202aa9c((u16 *)(obj + 0x38));
    if (*(int *)(obj + 0x140) != 0) {
        frame = func_0202aee0((u16 *)(obj + 0x38), 0);
        scrollBase = *(int *)(obj + 0x1b0);
        func_ov025_0208c7dc(obj + 0x1b8, obj + 0x480, scrollBase, frame);
        if (*(int *)(obj + 0x524) == 0xd) {
            MTX_ScaleApply43((int *)(obj + 0x150), (u32 *)(obj + 0x150), 0x64000, 0x64000, 0x64000);
        }
        func_ov025_0208c634((void *)(obj + 0x1b8), (void *)(obj + 0x150));
        func_ov025_0208c5b8((u8 *)(obj + 0x1b8));
    }
    if (*(int *)(obj + 0x144) != 0) {
        frame = func_0202aee0((u16 *)(obj + 0x38), 0);
        scrollBase = *(int *)(obj + 0x1b0);
        func_ov025_0208c7dc(obj + 0x31c, obj + 0x480, scrollBase, frame);
        if (*(int *)(obj + 0x524) == 0xd) {
            MTX_ScaleApply43((int *)(obj + 0x180), (u32 *)(obj + 0x180), 0x64000, 0x64000, 0x64000);
        }
        func_ov025_0208c634((void *)(obj + 0x31c), (void *)(obj + 0x180));
        func_ov025_0208c5b8((u8 *)(obj + 0x31c));
    }
}
