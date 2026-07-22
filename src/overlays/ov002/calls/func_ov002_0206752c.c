/* Push the page's archive block to the sub screen's BG2 character base at
 * 0x4f40. func_02011988 decodes the block into the standard character header,
 * whose src pointer is word 5 and byte count word 4 (same shape as
 * func_ov002_02067078). The page is released with follow-up 1. */
extern int func_ov002_02052aec(int page);
extern int func_02011988(int block, void *out);
extern void GXS_LoadBG2Char(void *src, unsigned int offset, unsigned int size);
extern void func_ov002_02052af4(int page, int a);

void func_ov002_0206752c(int page) {
    int *chr;

    func_02011988(func_ov002_02052aec(page), &chr);
    GXS_LoadBG2Char((void *)chr[5], 0x4f40, chr[4]);
    func_ov002_02052af4(page, 1);
}
