/* Glyph blit into one 8x8 destination cell, the callee of TileSurface_BlitGlyph.
 *
 * Clips the glyph rectangle to the cell, seeks the compressed glyph bitstream to the
 * first visible pixel, then reads one pixel index at a time and merges the non-zero
 * ones into the destination's packed words. A 4bpp destination keeps one word per
 * row, everything else two -- which is why the second arm walks the destination in
 * 8-byte steps and writes a pair of words per row.
 *
 * The setup block's own scope, and reading dsrc/srcBpp/dstBpp only inside the second
 * one, is what places the spills and the bpp cluster; hoisting them to function scope
 * costs the whole tail of the setup.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef unsigned long long u64;

/* Field order follows the reader itself at 0x02014950: it loads offset 4 with ldrsb and
 * compares it against the requested bit count, so that byte is the SIGNED count of bits
 * still available, and it loads offset 5 with ldrb and shifts it right, so that byte is
 * the unsigned bit buffer. */
typedef struct NNSiG2dBitReader {
    const u8 *src;
    s8 availableBits;
    u8 bits;
} NNSiG2dBitReader;

typedef struct LC_INFO {
    const u8 * dst;
    const u8 * src;
    int ofs_x;
    int ofs_y;
    int width;
    int height;
    int dsrc;
    int srcBpp;
    int dstBpp;
    u32 cl;
} LC_INFO;

extern u32 func_02014950(NNSiG2dBitReader * reader, int nBits);

static inline void NNSi_G2dBitReaderInit(NNSiG2dBitReader *reader, const u8 *src)
{
    reader->src = src;
    reader->availableBits = 0;
    reader->bits = 0;
}

static inline int MATH_IMax(int a, int b)
{
    return (a >= b) ? a : b;
}

static inline int MATH_IMin(int a, int b)
{
    return (a <= b) ? a : b;
}
#define CHARACTER_WIDTH 8
#define CHARACTER_HEIGHT 8

void func_02013a38(LC_INFO * i)
{
    const u8 * pSrc;
    u32 x_st;
    u32 x_ed;
    u32 y_st;
    u32 y_ed;
    u32 offset;

    {
        u32 bit_y_begin;

        x_st = (unsigned int)MATH_IMax(i->ofs_x, 0);
        y_st = (unsigned int)MATH_IMax(i->ofs_y, 0);
        x_ed = (unsigned int)MATH_IMin(CHARACTER_WIDTH, i->ofs_x + i->width);
        y_ed = (unsigned int)MATH_IMin(CHARACTER_HEIGHT, i->ofs_y + i->height);
        bit_y_begin = (unsigned int)-MATH_IMin(i->ofs_y, 0);
        offset = -MATH_IMin(i->ofs_x, 0) * i->srcBpp + bit_y_begin * i->dsrc;

        pSrc = i->src;
    }

    {
        u32 x;
        const int dsrc = i->dsrc;
        const int srcBpp = i->srcBpp;
        const int dstBpp = i->dstBpp;

        x_st *= dstBpp;
        x_ed *= dstBpp;
        if ( dstBpp == 4 ) {
            u32 * pDst = (u32 *)i->dst + y_st;
            u32 * pDstEnd = (u32 *)i->dst + y_ed;
            u32 cl = i->cl;

            for ( ; pDst < pDstEnd; pDst++) {
                NNSiG2dBitReader reader;
                u32 out_line = *pDst;

                NNSi_G2dBitReaderInit(&reader, pSrc + offset / 8);
                (void)func_02014950(&reader, (int)offset % 8);
                for (x = x_st; x < x_ed; x += 4) {
                    u32 bits = func_02014950(&reader, srcBpp);

                    if ( bits != 0 ) {
                        out_line = (out_line & ~(0xF << x)) | ((cl + bits) << x);
                    }
                }

                *pDst = out_line;
                offset += dsrc;
            }
        } else {
            u32 * pDst = (u32 *)((u64 *)i->dst + y_st);
            u32 * const pDstEnd = (u32 *)((u64 *)i->dst + y_ed);
            u32 cl = i->cl;

            for ( ; pDst < pDstEnd; pDst += 2) {
                NNSiG2dBitReader reader;
                u32 out_line_0 = *pDst;
                u32 out_line_1 = *(pDst + 1);
                NNSi_G2dBitReaderInit(&reader, pSrc + offset / 8);
                (void)func_02014950(&reader, (int)offset % 8);

                for (x = x_st; x < x_ed; x += 8) {
                    u32 bits = func_02014950(&reader, srcBpp);
                    if ( bits != 0 ) {
                        if ( x < 32 ) {
                            out_line_0 = (out_line_0 & ~((u32)0xFF << x)) | ((u32)(cl + bits) << x);
                        } else {
                            const u32 x_32 = x - 32;
                            out_line_1 = (out_line_1 & ~((u32)0xFF << x_32)) | ((u32)(cl + bits) << x_32);
                        }
                    }
                }
                *pDst = out_line_0;
                *(pDst + 1) = out_line_1;

                offset += dsrc;
            }
        }
    }
}
