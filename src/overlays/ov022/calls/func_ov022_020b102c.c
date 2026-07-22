/* Reset the four banks of three 0x38-byte voices at +0x10 of the root heap.
 * Always reports 0. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_020b10c8(void *voice);

int func_ov022_020b102c(void) {
    int zero;
    int i;
    int j;
    char *bank;
    char *voice;

    bank = (char *)NNSi_FndGetCurrentRootHeap() + 0x10;
    i = 0;
    zero = i;

    for (; i < 4; i++) {
        j = zero;
        voice = bank;

        for (; j < 3; j++) {
            func_ov022_020b10c8(voice);
            voice += 0x38;
        }

        bank += 0xa8;
    }

    return 0;
}
