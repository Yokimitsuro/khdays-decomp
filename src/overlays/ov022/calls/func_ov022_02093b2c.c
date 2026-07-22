/* Tear down the four voice slots -- the 0x108-byte streams from +0x20 and the
 * 0x24-byte mixers from +0x440 -- then clear the loaded flag. The flag is
 * cleared whether or not the slots were live. */
extern void func_0202a7dc(void *stream);
extern void func_0202a440(void *mixer);

void func_ov022_02093b2c(unsigned char *self) {
    char *stream;
    char *mixer;
    int i;

    if ((*self & 1) != 0) {
        i = 0;
        stream = (char *)self + 0x20;
        mixer = (char *)self + 0x440;

        for (; i < 4; i++) {
            func_0202a7dc(stream);
            func_0202a440(mixer);
            stream += 0x108;
            mixer += 0x24;
        }
    }

    *self = 0;
}
