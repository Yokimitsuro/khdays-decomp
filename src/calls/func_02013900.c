/* Fill a rectangle inside one 8x8 destination cell with a solid colour.
 *
 * Three paths. A full 8x8 rectangle is the whole cell, so it goes straight to
 * MIi_CpuClearFast over dstBpp*8 bytes. Otherwise the rectangle is a horizontal span
 * repeated down some rows, and the span is written as a masked read-modify-write: build
 * a field mask width*dstBpp bits wide at bit offset ofs_x*dstBpp, then merge the colour
 * through it into every row. A 4bpp destination keeps one word per row, everything else
 * two, and the two-word path has to build each half separately because a span can start
 * or end past bit 32.
 */

typedef unsigned int u32;

extern void MIi_CpuClearFast(unsigned int data, void *dest, unsigned int size);

void func_02013900(u32 *dst, int ofs_x, int ofs_y, int width, int height, u32 cl, int dstBpp)
{
    if (width == 8 && height == 8) {
        MIi_CpuClearFast(cl, dst, dstBpp * 8);
        return;
    }

    if (dstBpp == 4) {
        /* Once lead and trail are derived, width is dead as a width, so the span mask is
         * kept in it. That is not cosmetic: holding the mask in the width parameter's own
         * register is what keeps this branch inside the two callee-saved registers the
         * original uses. The same reuse of ofs_x and width does the job in the other arm. */
        u32 lead = ofs_x * 4;
        u32 trail = 32 - (lead + width * 4);
        u32 *row;
        u32 fill;
        u32 *rowEnd;

        width = (int)(((0xffffffffu >> lead) << (trail + lead)) >> trail);
        row = dst + ofs_y;
        fill = cl & (u32)width;
        rowEnd = row + height;
        width = (int)~(u32)width;
        while (row < rowEnd) {
            *row = fill | (*row & (u32)width);
            row++;
        }
    } else {
        /* ofs_x becomes the span's lead in bits and width becomes its trail, overwriting
         * the parameters they are derived from so they stay in the argument registers
         * instead of taking callee-saved ones. Both comparisons are unsigned. */
        u32 maskLo;
        u32 maskHi;
        u32 fillLo;
        u32 fillHi;
        u32 *row;
        u32 *rowEnd;

        ofs_x = ofs_x * 8;
        width = 64 - (ofs_x + width * 8);

        maskLo = 0xffffffffu >> ofs_x;
        if ((u32)width < 32) {
            maskLo <<= ofs_x;
        } else {
            u32 over = width - 32;
            maskLo = (maskLo << (ofs_x + over)) >> over;
        }

        maskHi = 0xffffffffu << width;
        if ((u32)ofs_x < 32) {
            maskHi >>= width;
        } else {
            u32 over = ofs_x - 32;
            maskHi = (maskHi >> (over + width)) << over;
        }

        row = dst + ofs_y * 2;
        rowEnd = row + height * 2;
        fillLo = cl & maskLo;
        fillHi = cl & maskHi;
        maskLo = ~maskLo;
        maskHi = ~maskHi;
        while (row < rowEnd) {
            row[0] = fillLo | (row[0] & maskLo);
            row[1] = fillHi | (row[1] & maskHi);
            row += 2;
        }
    }
}
