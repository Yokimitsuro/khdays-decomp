/* func_ov026_02086438 -- Ov008_ShowFilterRow: flip row nRow of the filter panel
 * between its "off" cell (+0xc374, shown when !bOn) and "on" cell (+0xc388,
 * shown when bOn), then draw the row's label glyph (source cell nLabel in the
 * +0xc39c table) onto the text surface at the row rectangle from the 0208fedc
 * table, shifted 8 px right when on.
 *
 * `const` on the two rect tables lets their loads float above the stack-argument
 * stores (ROM order); the first visibility is `!bOn` (evaluated last, in place).
 */
typedef unsigned char u8;

typedef struct Ov008PanelContext {
    u8 pad_0000[0xbfb0];
    int hSlots;               /* 0xbfb0 */
    u8 pad_bfb4[0xc160 - 0xbfb4];
    u8 textSurface[0xc374 - 0xc160]; /* 0xc160 */
    int aOffCell[5];          /* 0xc374 */
    int aOnCell[5];           /* 0xc388 */
    int aLabelCell[1];        /* 0xc39c */
} Ov008PanelContext;

#define LABEL_X_BASE 0x10
#define LABEL_ON_SHIFT 8
#define LABEL_Y_BASE 2
#define LABEL_COLOUR 4
#define LABEL_FLAGS 8

extern Ov008PanelContext *data_ov026_02091368;
extern const u8 data_ov026_02091134[];                                  /* row rect x (stride 4) */
extern const u8 data_ov026_02091135[];                                  /* row rect y (stride 4) */

extern void func_02032710(int hSlots, int nCell, int bVisible);   /* Slot_SetVisible */
extern void func_ov026_02085bf4(void *pSurface, int nText, int nX, int nY, int nColour, int nFlags); /* Ov008_DrawStringShadowed */

void func_ov026_02086438(int nRow, int nLabel, int bOn)
{
    func_02032710(data_ov026_02091368->hSlots, data_ov026_02091368->aOffCell[nRow], !bOn);
    func_02032710(data_ov026_02091368->hSlots, data_ov026_02091368->aOnCell[nRow], bOn);
    func_ov026_02085bf4(data_ov026_02091368->textSurface, data_ov026_02091368->aLabelCell[nLabel],
                        data_ov026_02091134[nRow * 4] + LABEL_X_BASE + (bOn != 0 ? LABEL_ON_SHIFT : 0),
                        data_ov026_02091135[nRow * 4] + LABEL_Y_BASE, LABEL_COLOUR, LABEL_FLAGS);
}
