/* Refresh the entry's node, then -- only when the descriptor's flag word says the
 * entry is still live -- run the redraw. Either way the busy bits at +0x1b6 are
 * cleared, keeping only bit 0.
 *
 * func_020235d0 takes TWO arguments: the id halfword at +0x14 and the kind byte
 * at +0x16. */
extern void func_0202ba18(void *node);
extern int func_020235d0(unsigned short id, int kind);
extern void func_ov002_02076bd8(void *self, int a);

void func_ov002_02076e90(char *self) {
    func_0202ba18(self + 0x2c);

    if ((unsigned int)((func_020235d0(*(unsigned short *)(self + 0x14),
                                      *(unsigned char *)(self + 0x16)) & 0xfffe) << 0xf) >> 0x10) {
        func_ov002_02076bd8(self, 0);
    }

    *(unsigned char *)(self + 0x1b6) &= ~0xfe;
}
