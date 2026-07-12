/*
 * Look up glyph/tile param_1 (as a byte at offset 1 of a scratch key) in table
 * type 0x13 via func_ov002_0206fb84; return 1 if found (result != 0xffff), else 0.
 */
extern int func_ov002_0206fb84(int type, void *key);

int func_ov002_0206a91c(int param_1) {
    int key;
    *((char *)&key + 1) = (char)param_1;

    return func_ov002_0206fb84(0x13, &key) != 0xffff;
}
