/* Upload the load request's archive block as tile kind 0x17, then release the
 * request keeping the block (free=0) because the upload consumed it. With no
 * context installed the request is released with free=1 and nothing is
 * uploaded. func_02011988 decodes the block into the standard character header:
 * source pointer word 5, byte count word 4. */
extern void func_ov002_02052af4(void *page, int freeBlock);
extern int func_02011988(int block, void *out);
extern void func_ov002_02053d28(int kind, int a, int src, int size, int block);

extern int data_ov002_0207f9f0;

void func_ov002_02066850(char *page) {
    int *chr;

    if (data_ov002_0207f9f0 == 0) {
        func_ov002_02052af4(page, 1);
        return;
    }

    func_02011988(*(int *)(page + 8), &chr);
    func_ov002_02053d28(0x17, 0, chr[5], chr[4], *(int *)(page + 8));
    func_ov002_02052af4(page, 0);
}
