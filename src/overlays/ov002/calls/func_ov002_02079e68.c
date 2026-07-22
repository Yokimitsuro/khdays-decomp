/* Retire the widget: while its flag bit 2 is set, stop the sub-node at +0x3c
 * (only when the owner's byte at +0x58 says it was started) and post event 0x5d
 * with the payload at +0xe0. Either way the state byte at +0x1b4 goes to 5 and
 * the word at +0x1b0 is cleared. */
extern void func_ov002_0207c618(void *node, int a, int b);
extern void func_0202af1c(void *node);
extern void func_02033d0c(int a, int event, void *payload, int b);

void func_ov002_02079e68(char *self) {
    char *owner = *(char **)(self + 8);

    if (*(unsigned short *)(self + 0x12) & 4) {
        if (owner[0x58] != 0) {
            func_ov002_0207c618(self + 0x3c, 1, 0);
            func_0202af1c(self + 0x3c);
        }
        func_02033d0c(0, 0x5d, self + 0xe0, 0);
    }

    *(unsigned char *)(self + 0x1b4) = 5;
    *(int *)(self + 0x1b0) = 0;
}
