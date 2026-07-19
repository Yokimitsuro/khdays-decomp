extern int func_ov002_0207285c(int slot);
extern void func_0202ba9c(void *dst, unsigned short id, int a, void *b);

/* Rebinds the actor model unless it is hidden or already fading, and always refreshes the cached
 * model id. */
void func_ov015_02081acc(char *self) {
    if ((*(unsigned char *)(self + 0x4a0) & 2) == 0
        && (*(unsigned char *)(self + 0x724) & 0xc0) == 0) {
        func_0202ba9c(self + 0x498,
                      (unsigned short)func_ov002_0207285c((unsigned char)self[0x10]), 0, 0);
    }
    *(short *)(self + 0x6a) = (short)func_ov002_0207285c((unsigned char)self[0x10]);
}
