/* Decode the page's archive block into the context's own character header at
 * +0x2c, keeping the block handle at +0x18. With no context installed there is
 * nothing to decode into, so the page is simply released with follow-up 1;
 * otherwise it is released with 0 once the header is in place. */
extern int func_ov002_02052aec(int page);
extern void func_ov002_02052af4(int page, int a);
extern int func_02011988(int block, void *out);

extern int data_ov002_0207f634;

void func_ov002_020638f0(int page) {
    int ctx = data_ov002_0207f634;

    if (ctx == 0) {
        func_ov002_02052af4(page, 1);
        return;
    }

    {
        int block = func_ov002_02052aec(page);

        *(int *)(ctx + 0x18) = block;
        func_02011988(block, (void *)(ctx + 0x2c));
    }
    func_ov002_02052af4(page, 0);
}
