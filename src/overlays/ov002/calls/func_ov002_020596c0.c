/* NOTE: data_ov002_0207f618 is NOT the Ov002PanelContext object -- that layout
 * belongs to data_ov002_0207f614, whose accessor family produced its named
 * fields (+0x3c, +0x48, +0x18c, +0x1b8). f618's own accessors stride by 0x18 at
 * +0x7c and by 4 at +0xce, which do not fit. Two neighbouring globals, two
 * objects; this one is left as its own type until enough of it is known.
 *
 * Set the panel mode at +0x2c, ignoring the call when there is no context or the
 * mode is already the one asked for. Arming the tag-tracker node for tag 0x1a is
 * done BEFORE the field is written, then the panel is relaid out. Switching to
 * mode 0 raises scene event 0x4f; switching to any other mode plays the cancel
 * sound, but only when func_ov002_0206b7a4 reports the panel unlocked. */
typedef struct {
    char pad00[0x2c];
    int nPanelMode;         /* +0x2c */
} Ov002ModeContext;

extern int func_ov002_020536bc(int tag);
extern void func_ov002_020536dc(int node, int armed);
extern void func_ov002_02058898(void);
extern void func_ov002_02053558(int event);
extern void func_ov002_020535a4(void);
extern int func_ov002_0206b7a4(void);
extern void func_02033b24(int a, int id);

extern Ov002ModeContext *data_ov002_0207f618;

void func_ov002_020596c0(int mode) {
    Ov002ModeContext *ctx = data_ov002_0207f618;

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
