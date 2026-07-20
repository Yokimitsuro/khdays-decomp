/* Replace the UTF-16 string cached at +0xb4 of the ov002 context: free the old
 * one, and when a new string is given duplicate it into a fresh heap block of
 * (length + 1) * 2 bytes. Either way tell func_ov002_02052a6c to re-run the
 * func_ov002_02061eac pass over data_ov002_0207ed58. */
extern int data_ov002_0207f62c;
extern int data_ov002_0207ed58;

extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern int func_020200c8(unsigned short *s);
extern unsigned short *func_020200e4(unsigned short *dst, unsigned short *src);
extern void func_ov002_02061eac(void);
extern void func_ov002_02052a6c(void *a, void *b, int c);

void func_ov002_02063200(unsigned short *s) {
    char *ctx = (char *)(&data_ov002_0207f62c)[1];
    void *cur = *(void **)(ctx + 0xb4);

    if (cur != 0) {
        if (cur != 0) {
            NNSi_FndFreeFromDefaultHeap(cur);
            *(void **)(ctx + 0xb4) = 0;
        }
    }

    if (s != 0) {
        *(void **)(ctx + 0xb4) =
            NNSi_FndAllocFromDefaultExpHeap((func_020200c8(s) + 1) * 2);
        func_020200e4(*(unsigned short **)(ctx + 0xb4), s);
    }

    func_ov002_02052a6c(&data_ov002_0207ed58, (void *)&func_ov002_02061eac, 0);
}
