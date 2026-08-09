typedef unsigned short u16;

extern void func_02014224(u16 *dst, int width, int height, int mapW,
                          int tile, int palette);

void func_02014174(u16 *dst, int width, int height, int x, int y,
                   int mapW, int tile, int palette)
{
    if (mapW <= 32) {
        int offset = mapW * y + x;
        func_02014224(dst + offset,
                      width, height, mapW, tile, palette);
    } else {
        int xEnd = x + width;
        int yEnd = y + height;
        u16 palBits = (u16)(palette << 12);

        for (; y < yEnd; y++) {
            int drawX;
            int rowIndex = y < 32 ? y : y + 32;
            u16 *row = dst + rowIndex * 32;

            for (drawX = x; drawX < xEnd; drawX++) {
                int columnIndex = drawX < 32 ? drawX : drawX + 0x3e0;
                row[columnIndex] = (u16)(tile++ | palBits);
            }
        }
    }
}
