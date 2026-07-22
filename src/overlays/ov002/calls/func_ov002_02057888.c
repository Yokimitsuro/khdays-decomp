/* Draw one 4x0x2e cell of the layout at row `index`, in style 2 with no flags.
 * Thin wrapper: everything but the row is a constant of this call site. */
extern void func_ov002_020576d8(int a, int b, int width, int height,
                                int flags, int style, void *row);

extern int data_ov002_0207dd94[];

void func_ov002_02057888(int a, int b, int index) {
    func_ov002_020576d8(a, b, 4, 0x2e, 0, 2, &data_ov002_0207dd94[index]);
}
