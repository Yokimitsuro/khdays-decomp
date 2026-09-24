/* func_0202fb8c -- scroll a text window up by `n` pixels, MAIN. The window keeps its character data
 * (+0x2c, +0x34 bytes) as areaWidth x areaHeight cells (+0x3a/+0x3c) of charSize bytes (+0x3e).
 * Whole character rows (n / 8) move up at once; then inside every row the remaining n % 8 pixel
 * lines move up and each cell's freed bottom lines are refilled from the top of the cell below.
 * The uncovered strip at the bottom is cleared through the char canvas (+0x4, vtable pClearArea). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct NNSG2dCharCanvas;

typedef struct NNSiG2dCharCanvasVTable {
    void (*pDrawGlyph)(void);
    void (*pClear)(const struct NNSG2dCharCanvas *cc, int cl);
    void (*pClearArea)(const struct NNSG2dCharCanvas *cc, int cl, int x, int y, int w, int h);
} NNSiG2dCharCanvasVTable;

typedef struct NNSG2dCharCanvas {
    u8 *charBase;
    int areaWidth;
    int areaHeight;
    u8 dstBpp;
    u8 pad0d[3];
    int pad10;
    const NNSiG2dCharCanvasVTable *vtable;
    u32 param;
} NNSG2dCharCanvas;

typedef struct TextWindow {
    u32 color;                          /* +0x00 */
    NNSG2dCharCanvas cc;                /* +0x04 */
    char pad20[0x2c - 0x20];
    u8 *chars;                          /* +0x2c */
    int pad30;
    u32 size;                           /* +0x34 */
    u16 pad38;
    u16 areaWidth;                      /* +0x3a */
    u16 areaHeight;                     /* +0x3c */
    u8 charSize;                        /* +0x3e */
} TextWindow;

extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);

void func_0202fb8c(TextWindow *win, int n)
{
    int rows = n / 8;
    int lines = n % 8;
    int rowBytes;
    int lineBytes;
    int y;
    int x;
    u8 *cell;

    if (rows > 0) {
        int shift = rows * (win->charSize * win->areaWidth);

        MIi_CpuCopyFast(win->chars + shift, win->chars, win->size - shift);
    }
    rowBytes = win->areaWidth * win->charSize;
    lineBytes = ((u32)win->charSize >> 3) * lines;
    for (y = 0; y < win->areaHeight; y++) {
        cell = win->chars + y * rowBytes;
        MIi_CpuCopyFast(cell + lineBytes, cell, rowBytes - lineBytes);
        cell += rowBytes;
        for (x = 0; x < win->areaWidth; x++) {
            MIi_CpuCopy32(cell, cell - rowBytes + win->charSize - lineBytes, lineBytes);
            cell += win->charSize;
        }
    }
    win->cc.vtable->pClearArea(&win->cc, 0, 0, (win->areaHeight << 3) - n, win->areaWidth << 3, n);
}
