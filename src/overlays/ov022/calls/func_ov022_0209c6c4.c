/* Commit both 0x164-byte panes -- each pane's dirty byte sits one past the pane
 * body at +0xda8 -- then flush the shared surface at +0x910. */
extern void func_ov002_02051c88(void *pane);
extern void func_ov022_020b07f0(void *surface);

void func_ov022_0209c6c4(char *self) {
    char *row;
    char *pane;
    int i;

    i = 0;
    row = self;
    pane = self + 0xda8;

    for (; i < 2; i++) {
        if (*(signed char *)(row + 0xda9) != 0) {
            func_ov002_02051c88(pane);
        }

        row += 0x164;
        pane += 0x164;
    }

    func_ov022_020b07f0(self + 0x910);
}
