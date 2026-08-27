/*
 * Stamps one mark on the canvas.
 *
 * The shape carries its own width and height, and the mask that goes with it
 * holds one bit per pixel. The mask is expanded into a byte per pixel, opaque
 * or clear, into a scratch buffer the blitter can take, and the buffer is
 * handed back to the heap afterwards.
 *
 * Four things here are load-bearing rather than style.
 *
 * The row offset is written out as the row times the width. Accumulating it by
 * hand into a variable of its own makes it a declared local and moves every
 * loop register; left as a product, the compiler builds the same running total
 * as an induction variable and places its setup past the loop guard.
 *
 * The mask byte is fetched into its own variable before the bit is tested.
 * Written inline the bit position is computed before the load, which costs an
 * instruction and reorders the whole test.
 *
 * The pixel index is signed and is divided and taken modulo by eight rather
 * than shifted and masked. That is what emits the rounding corrections around
 * both the byte lookup and the bit position; a shift and a mask would be two
 * instructions shorter and wrong.
 *
 * The width and height are read again from the shape at the blit rather than
 * reused from the two values read at the top.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002StampShape {
    u32 field000;
    u16 nWidth;
    u16 nHeight;
} Ov002StampShape;

extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_ov002_0206638c(int hCanvas, u16 nX, u16 nY, int nWidth, int nHeight,
                     int nPen, const u8 *pPixels);

void func_ov002_02066634(int hCanvas, int nX, int nY, int nPen,
              const Ov002StampShape *pShape, const u8 *pMask)
{
    u8 *pPixels;
    int nWidth;
    int nHeight;
    int y;
    int x;
    int i;
    u8 nByte;

    nWidth = pShape->nWidth;
    nHeight = pShape->nHeight;
    pPixels = (u8 *)NNSi_FndAllocFromDefaultExpHeap(nWidth * nHeight);

    for (y = 0; y < nHeight; y++) {
        for (x = 0; x < nWidth; x++) {
            i = x + y * nWidth;
            nByte = pMask[i / 8];
            pPixels[i] = (nByte & (1 << (i % 8))) != 0 ? 0xff : 0;
        }
    }

    func_ov002_0206638c(hCanvas, (u16)nX, (u16)nY, pShape->nWidth, pShape->nHeight,
             nPen, pPixels);
    if (pPixels != 0) {
        NNSi_FndFreeFromDefaultHeap(pPixels);
    }
}
