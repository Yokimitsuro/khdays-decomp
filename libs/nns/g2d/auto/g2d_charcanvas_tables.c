/* NitroSystem g2d_CharCanvas.c: the two `const u32 fullbits = ~0` words its OBJ canvas
 * initialisers keep in .rodata, the BG canvas vtable (the OBJ vtables are not linked in) and
 * GetMaxObjectSize's OBJ shape table. */
typedef unsigned char u8;
typedef unsigned int u32;

struct NNSG2dCharCanvas;
struct NNSG2dFont;
struct NNSG2dGlyph;
typedef void (*NNSiG2dDrawGlyphFunc)(const struct NNSG2dCharCanvas *pCC, const struct NNSG2dFont *pFont, int x, int y, int cl, const struct NNSG2dGlyph *pGlyph);
typedef void (*NNSiG2dClearFunc)(const struct NNSG2dCharCanvas *pCC, int cl);
typedef void (*NNSiG2dClearAreaFunc)(const struct NNSG2dCharCanvas *pCC, int cl, int x, int y, int w, int h);

typedef struct NNSiG2dCharCanvasVTable {
    NNSiG2dDrawGlyphFunc pDrawGlyph;
    NNSiG2dClearFunc pClear;
    NNSiG2dClearAreaFunc pClearArea;
} NNSiG2dCharCanvasVTable;

typedef struct ObjectSize {
    u8 widthShift;
    u8 heightShift;
} ObjectSize;

void func_02013c78(const struct NNSG2dCharCanvas *pCC, const struct NNSG2dFont *pFont, int x, int y, int cl, const struct NNSG2dGlyph *pGlyph);   /* DrawGlyphLine */
void func_02013e10(const struct NNSG2dCharCanvas *pCC, int cl);                                                                                 /* ClearContinuous */
void func_02013e60(const struct NNSG2dCharCanvas *pCC, int cl, int x, int y, int w, int h);                                                     /* ClearAreaLine */

/* fullbits (NNS_G2dCharCanvasInitForOBJ1D / ...OBJ2DRect) */
const u32 data_02041a8c[2] = { (u32)~0, (u32)~0 };

/* VTABLE_BG */
const NNSiG2dCharCanvasVTable data_02041a94 = {
    func_02013c78,
    func_02013e10,
    func_02013e60
};

/* GetMaxObjectSize's objs[4][4]: {widthShift, heightShift} by [log2 h][log2 w] */
const ObjectSize data_02041aa0[4][4] = {
    { {0, 0}, {1, 0}, {2, 0}, {2, 0} },
    { {0, 1}, {1, 1}, {2, 1}, {2, 1} },
    { {0, 2}, {1, 2}, {2, 2}, {3, 2} },
    { {0, 2}, {1, 2}, {2, 3}, {3, 3} },
};
