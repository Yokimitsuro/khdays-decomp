/* Set the panel mode at +0x2c, ignoring the call when there is no context or the
 * mode is already the one asked for. Arming the tag-tracker node for tag 0x1a is
 * done BEFORE the field is written, then the panel is relaid out. Switching to
 * mode 0 raises scene event 0x4f; switching to any other mode plays the cancel
 * sound, but only when func_ov002_0206b7a4 reports the panel unlocked. */
typedef struct {
    char pad00[0x2c];
    int nPanelMode;         /* +0x2c */
} Ov002PanelContext;

extern int func_ov002_020536bc(int tag);
extern void func_ov002_020536dc(int node, int armed);
extern void func_ov002_02058898(void);
extern void func_ov002_02053558(int event);
extern void func_ov002_020535a4(void);
extern int func_ov002_0206b7a4(void);
extern void func_02033b24(int a, int id);

extern Ov002PanelContext *data_ov002_0207f618;

void func_ov002_020596c0(int mode) {
    Ov002PanelContext *ctx = data_ov002_0207f618;

    if (ctx == 0 || ctx->nPanelMode == mode) {
        return;
    }

    func_ov002_020536dc(func_ov002_020536bc(0x1a), mode);
    ctx->nPanelMode = mode;
    func_ov002_02058898();

    /* The non-zero arm is written first so it stays inline and the mode-0 arm is
     * emitted out of line at the tail, matching the ROM's forward beq. */
    if (mode != 0) {
        if (func_ov002_0206b7a4() == 0) {
            func_02033b24(0, 0x10);
        }
    } else {
        func_ov002_02053558(0x4f);
        func_ov002_020535a4();
    }
}
