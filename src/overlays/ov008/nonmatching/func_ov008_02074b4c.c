/* NOT MATCHING -- 225 of 244 bytes, 42 of 61 instructions aligned.
 *
 * Exact size, exact instruction count and exact relocations. The residue is the
 * colouring of the four callee-saved values: the ROM keeps the panel parameter
 * on top (r7), then the fallback entry (r6), the title (r5) and the width (r4);
 * mwccarm 3.0 build 139 hands the r0 parameter r5 instead, with the title in r6
 * and the fallback in r7, and every instruction follows that rename.
 *
 * Measured on a minimal probe (build/try/micro2): build 139 demotes the r0
 * parameter whenever a call carries stacked arguments of the shape (fresh
 * constant, plain variable) -- here the flags 0xfb and the title pointer of the
 * six-argument draw; (variable, variable), (constant, computed value), seven or
 * more arguments, or a stacked constant shared with a register argument keep
 * the parameter on top. The only source change that reproduces the ROM's
 * colouring is a u16 hItem parameter on the first call's prototype, and build
 * 139 then emits the int -> u16 narrowing pair (lsl/lsr) the ROM does not have;
 * the ROM narrows int -> u16 elsewhere (289 sites), so the retail compiler is
 * not skipping the conversion, it simply colours this shape differently.
 *
 * Swept: declaration / statement orders, explicit parameter copies, const and
 * register hints, a fourth parameter, the C++ lane, inline wrappers for each
 * call, K&R / variadic / narrow / pointer-integer prototypes, joint callee
 * return types (540), argument casts (78), constant provenance of the flags
 * (12), volatile reads (8), struct field types (16), 49 optimisation pragmas,
 * a 3000-cell random cross product over 26 axes, and every mwccarm build in
 * tools/mwccarm (2.0 / 3.0 identical, 1.2 / DSi worse). Left for decomp.me.
 */
/* func_ov008_02074b4c -- Ov008_DrawMissionTitle: draw a mission row's title on
 * the detail surface (+0xc).  Binds the surface to the item at +0x138, sets
 * frame 6, then draws the entry's title (+0x40) at (3, 3) in colour 0xf5 with
 * flags 0xfb -- outside a page transition always; during one only when the
 * title is non-empty, else the fallback entry's title when one is given.  The
 * measured width is stored at +0x144 (0 when nothing was drawn).
 */
typedef unsigned char  u8;
typedef unsigned short u16;

#define TITLE_X      3
#define TITLE_Y      3
#define TITLE_COLOUR 0xf5
#define TITLE_FLAGS  0xfb
#define FRAME_TITLE  6

typedef struct Ov008MissionEntry {
    u8   pad_00[0x40];
    u16 *pTitle;              /* 0x40 */
} Ov008MissionEntry;

typedef struct Ov008DetailPanel {
    u8  pad_000[0xc];
    u8  surface[0x34 - 0xc];  /* 0x00c */
    int nFrame;               /* 0x034 */
    u8  pad_038[0x138 - 0x38];
    int hItem;                /* 0x138 */
    u8  pad_13c[8];
    int nTitleWidth;          /* 0x144 */
} Ov008DetailPanel;

extern void func_02030094(void *pSurface, int hItem, int bUpdate);        /* TileSurface_SetCurrentItem */
extern void func_02030158(void *pSurface, int nFrame);                    /* Obj_InvokeInnerVtable4 */
extern int  func_ov008_02051028(void);                                    /* page transition active */
extern void func_020302ec(void *pSurface, int nX, int nY, int nColour, int nFlags, u16 *pText); /* Obj_ForwardToSub1c */
extern int  func_ov008_02074b10(u16 *pText);                              /* MeasureWideStringHeight */

void func_ov008_02074b4c(Ov008DetailPanel *pPanel, Ov008MissionEntry *pEntry, Ov008MissionEntry *pFallback)
{
    u16 *pTitle = pEntry->pTitle;
    int nWidth = 0;

    func_02030094(pPanel->surface, pPanel->hItem, 0);
    pPanel->nFrame = FRAME_TITLE;
    func_02030158(pPanel->surface, FRAME_TITLE);
    if (func_ov008_02051028() == 0) {
        func_020302ec(pPanel->surface, TITLE_X, TITLE_Y, TITLE_COLOUR, TITLE_FLAGS, pTitle);
        nWidth += func_ov008_02074b10(pTitle);
    } else if (*pTitle != 0) {
        func_020302ec(pPanel->surface, TITLE_X, TITLE_Y, TITLE_COLOUR, TITLE_FLAGS, pTitle);
        nWidth += func_ov008_02074b10(pTitle);
    } else if (pFallback != 0) {
        func_020302ec(pPanel->surface, TITLE_X, TITLE_Y, TITLE_COLOUR, TITLE_FLAGS, pFallback->pTitle);
        nWidth += func_ov008_02074b10(pFallback->pTitle);
    }
    pPanel->nTitleWidth = nWidth;
}
