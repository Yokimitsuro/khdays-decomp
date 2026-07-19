extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);
extern void func_02029438(void *p, int i, unsigned char v);
extern char data_ov016_02082740;

/* Rebinds the actor model unless it is hidden, starts the idle animation for the owner's resting
 * states, and applies the palette that its state maps to. */
void func_ov016_02081a78(char *self) {
    char *owner = *(char **)(self + 8);
    int state;
    int palette;
    if ((*(unsigned char *)(self + 0x4a0) & 2) == 0) {
        func_0202ba9c(self + 0x498,
                      (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]), 0, 0);
        state = *(unsigned char *)(owner + 0x7c);
        if (state == 0 || state == 2) {
            func_02029438(self + 0x5b4, 1, 3);
        }
    }
    *(short *)(self + 0x6a) = (short)func_ov002_0207285c((unsigned char)self[0x10]);
    palette = *(signed char *)((char *)&data_ov016_02082740
                               + *(unsigned char *)(owner + 0x7c));
    if (palette >= 0) {
        func_02029438(self + 0x5b4, 3, (unsigned char)palette);
    }
}
