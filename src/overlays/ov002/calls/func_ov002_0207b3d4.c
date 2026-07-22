/* func_ov002_0207b3d4 -- keep a HUD element's "lit" state in sync with its source pair: while the
 * first word is zero and the global mode byte does not have bit 2, the second word decides both
 * the byte at +0x17 and bit 3 of the flags halfword at +0x12. */
extern unsigned char data_0204c240;

void func_ov002_0207b3d4(int obj, int unused, int *src) {
    if (src[0] != 0) {
        return;
    }
    if ((data_0204c240 & 4) != 0) {
        return;
    }
    if (src[1] != 0) {
        *(unsigned char *)(obj + 0x17) = 1;
        *(unsigned short *)(obj + 0x12) |= 8;
        return;
    }
    *(unsigned char *)(obj + 0x17) = 0;
    *(unsigned short *)(obj + 0x12) &= ~8;
}
