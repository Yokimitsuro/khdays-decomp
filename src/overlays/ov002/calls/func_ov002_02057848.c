/* Draw one 5 x 0xe cell of the short layout table in style 2 with flag 1. The
 * rows are 5 bytes wide, which mwcc reaches as row + row * 4. */
extern void func_ov002_020576d8(int a, int b, int width, int height,
                                int flags, int style, void *row);

typedef struct {
    unsigned char bytes[5];
} Ov002ShortRow;

extern Ov002ShortRow data_ov002_0207ddc0[];

void func_ov002_02057848(int a, int b, int row) {
    func_ov002_020576d8(a, b, 5, 0xe, 1, 2, &data_ov002_0207ddc0[row]);
}
