extern unsigned char data_ov107_020cbb20[];
extern unsigned char data_ov107_020cbb98[][0x2c];
extern void *data_ov107_020cbb08[];
extern void func_ov107_020c0758(int param_1);

/* Teardown pass: for every overlay slot with a registered index (nonzero byte in the
 * 0cbb20 table), end/unload that overlay's info block and clear its handler slot. */
void func_ov107_020c2f40(void) {
    int i;
    unsigned char *slot = data_ov107_020cbb20;
    for (i = 0; i < 0x76; i++, slot++) {
        unsigned char val = *slot;
        if (val != 0) {
            unsigned char idx = val - 1;
            func_ov107_020c0758((int)data_ov107_020cbb98[idx]);
            data_ov107_020cbb08[idx] = 0;
        }
    }
}
